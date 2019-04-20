#include <graphics/mesh_object.hpp>
#include <utils/mesh_reader.hpp>
#include <glm/vec2.hpp>
#include <iostream>

namespace cgicmc {
MeshObject::MeshObject() { _hasTexture = _hasMaterial = _hasNormal = false; }

void MeshObject::initialize() {
  glGenVertexArrays(1, &_vao);
  glGenBuffers(3, _vbo);
  glGenBuffers(1, &_ebo);
}

Texture &MeshObject::getTexture() { return _textureImage; }

void MeshObject::loadTexture() {
  if (MeshReader::readTexture(*this, _textureImage.getFilename().c_str())) {
    _hasTexture = true;
    glBindVertexArray(_vao);

    // Bind texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * _vertexTexture.size(),
                 _vertexTexture.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(glm::vec2) * _vertexTexture.size(), (void *)0);
    glEnableVertexAttribArray(1);

    // bind Texture image
    glGenTextures(1, &_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::cout << "image: " << _textureImage.getWidth() << ' '
              << _textureImage.getHeight() << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureImage.getWidth(),
                 _textureImage.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 _textureImage.getImageData());
    glGenerateMipmap(GL_TEXTURE_2D);
  }
}

void MeshObject::loadObjMesh(const char *objPath) {
  // Read mesh from file
  MeshReader::readObj(*this, objPath);
  _computeCentroid();

  glBindVertexArray(_vao);
  // Assign vertex position buffer
  glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * getVerticesSize(),
               _vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
  glEnableVertexAttribArray(0);

  // Assign vertices indices to triangles
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * getFacesSize(),
               _faces.data(), GL_STATIC_DRAW);

  // Assign normal to each vertex
  glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * getVerticesSize(),
               _vertexNormal.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
  glEnableVertexAttribArray(1);

  // Ensure no buffer is binded
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void MeshObject::draw(Shader shader) {
  shader.useShader();
  glBindTexture(GL_TEXTURE_2D, _tex);
  glBindVertexArray(_vao);
  // glDrawArrays(GL_TRIANGLES, 0, 3 * getVerticesSize());
  glDrawElements(GL_TRIANGLES, 3 * getFacesSize(), GL_UNSIGNED_INT, 0);
}

void MeshObject::addTextureCoordinate(glm::vec2 texCoord) {
  _vertexTexture.emplace_back(texCoord);
}

uint MeshObject::addVertex(glm::vec3 vertex) {
  _vertices.emplace_back(vertex);
  return _vertices.size() - 1;
}

void MeshObject::addVertexNormal(uint id, glm::vec3 normal) {
  if (id >= _vertices.size()) {
    std::cerr << "MeshObject::addVertexNormal: vertexId out of range.\n";
    return;
  }
  if (id == _vertexNormal.size())
    _vertexNormal.emplace_back(normal);
  else if (id > _vertexNormal.size())
    _vertexNormal.resize(id + 1);
  else
    _vertexNormal[id] = normal;
}

glm::vec3 MeshObject::getCentroid() { return _centroid; }

glm::vec3 MeshObject::getBBoxSize() { return _bboxMax - _bboxMin; }

glm::vec3 MeshObject::getBboxCenter() { return (_bboxMax + _bboxMin) / 2.0f; }

bool &MeshObject::hasTexture() { return _hasTexture; }
bool &MeshObject::hasNormal() { return _hasNormal; }
bool &MeshObject::hasMaterial() { return _hasMaterial; }

void MeshObject::_computeCentroid() {
  _centroid = glm::vec3(0.0);
  _bboxMax = glm::vec3(-1e8);
  _bboxMin = glm::vec3(1e8);
  for (auto vertex : _vertices) {
    _centroid += vertex;

    if (_bboxMax[0] < vertex[0])
      _bboxMax[0] = vertex[0];
    if (_bboxMax[1] < vertex[1])
      _bboxMax[1] = vertex[1];
    if (_bboxMax[2] < vertex[2])
      _bboxMax[2] = vertex[2];

    if (_bboxMin[0] > vertex[0])
      _bboxMin[0] = vertex[0];
    if (_bboxMin[1] > vertex[1])
      _bboxMin[1] = vertex[1];
    if (_bboxMin[2] > vertex[2])
      _bboxMin[2] = vertex[2];
  }
  _centroid /= (float)_vertices.size();
}

} // namespace cgicmc