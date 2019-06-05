#include <mesh_object.hpp>
#include <mesh_reader.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

MeshObject::MeshObject() { _hasTexture = _hasMaterial = _hasNormal = false; }

uint MeshObject::addVertex(glm::vec3 vertex) {
  _vertices.emplace_back(vertex);
  return _vertices.size() - 1;
}

uint MeshObject::addFace(glm::ivec3 face) {
  _faces.emplace_back(face);
  return _faces.size() - 1;
}

glm::vec3 MeshObject::getVertex(uint index) { return _vertices[index]; }

glm::ivec3 MeshObject::getFace(uint index) { return _faces[index]; }

uint MeshObject::getVerticesSize() { return _vertices.size(); }

uint MeshObject::getFacesSize() { return _faces.size(); }

glm::vec3 MeshObject::getCentroid() { return _centroid; }

glm::vec3 MeshObject::getBBoxSize() { return _bboxMax - _bboxMin; }

glm::vec3 MeshObject::getBboxCenter() { return (_bboxMax + _bboxMin) / 2.0f; }

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

void MeshObject::initialize() {
  // Initialize buffers and matrices
}

Texture &MeshObject::getTexture() { return _textureImage; }

void MeshObject::loadTexture() {
  if (MeshReader::readTexture(*this, _textureImage.getFilename().c_str())) {
    _hasTexture = true;

    // Load texture buffer
  }
}

void MeshObject::loadObjMesh(const char *objPath) {
  // Read mesh from file
  MeshReader::readObjWithTexture(*this, objPath);
  _computeCentroid();

  // Load obj buffer
}

void MeshObject::centerizeObject() {
  for (int i = 0; i < _instanceCount; i++) {
    glm::vec3 size = getBBoxSize(), boxCenter = getBboxCenter();
    double largerDimension = std::max(std::max(size[0], size[1]), size[2]);
    _modelMatrix[i] =
        glm::scale(_modelMatrix[i], glm::vec3(1.5 / largerDimension));
    _modelMatrix[i] = glm::translate(_modelMatrix[i], -boxCenter);
  }
}

void MeshObject::addTextureCoordinate(glm::vec2 texCoord) {
  _vertexTexture.emplace_back(texCoord);
}

void MeshObject::assignVertices(std::vector<glm::vec3> &vertices) {
  _vertices.assign(vertices.begin(), vertices.end());
}

void MeshObject::removeAllVertices() {
  int nVertices = _vertices.size();
  _vertices.clear();
  std::cout << "Removed " << nVertices << " vertices\n";
}

uint MeshObject::removeDoubles() {}

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

bool &MeshObject::hasTexture() { return _hasTexture; }
bool &MeshObject::hasNormal() { return _hasNormal; }
bool &MeshObject::hasMaterial() { return _hasMaterial; }
