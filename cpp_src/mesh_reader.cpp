#include <mesh_reader.hpp>
#include <stb_image.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tiny_obj_loader.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

void MeshReader::readObjWithTexture(MeshObject &structure, const char *path) {
  std::string warning, error;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  tinyobj::attrib_t attributes;
  std::vector<glm::vec3> vertCoords;

  std::string baseDir(path);
  int lastSlash = baseDir.find_last_of("/\\");

  bool ret =
      tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, path,
                       baseDir.substr(0, lastSlash).c_str(), true, false);
  structure.hasTexture() = (!attributes.texcoords.empty()) ? true : false;
  structure.hasMaterial() = (!materials.empty()) ? true : false;
  structure.hasNormal() = (!attributes.normals.empty()) ? true : false;

  if (structure.hasTexture() && !materials.empty()) {
    structure.getTexture().setTextureFilename(
        baseDir.substr(0, lastSlash + 1).append(materials[0].diffuse_texname));
  } else {
    structure.hasTexture() = false;
  }
  if (structure.hasTexture())
    vertCoords.resize(attributes.texcoords.size() / 2);
  else
    vertCoords.resize(attributes.vertices.size() / 3);

  std::cerr << "Vertices size: " << attributes.vertices.size() / 3
            << "\nTexcoords size " << attributes.texcoords.size() / 2
            << std::endl;
  for (int i = 0; i < attributes.texcoords.size(); i++) {
    structure.addTextureCoordinate(glm::vec2(attributes.texcoords[2 * i + 0],
                                             attributes.texcoords[2 * i + 1]));
  }

  for (auto shape : shapes)
    for (int i = 0; i < shape.mesh.indices.size() / 3; i++) {
      glm::ivec3 face;
      for (int v = 0; v < 3; v++) {
        int vid = shape.mesh.indices[3 * i + v].vertex_index;
        face[v] = vid;
        int texId = vid;
        if (structure.hasTexture()) {
          texId = shape.mesh.indices[3 * i + v].texcoord_index;
          face[v] = texId;
        }
        vertCoords[texId] = glm::vec3(attributes.vertices[3 * vid + 0],
                                      attributes.vertices[3 * vid + 1],
                                      attributes.vertices[3 * vid + 2]);
      }

      structure.addFace(face);
    }

  structure.assignVertices(vertCoords);

  std::cout << "Read " << structure.getVerticesSize() << " vertices and "
            << structure.getFacesSize() << " faces\n";
  //   for (auto vertex : attributes.vertices) {
  // structure.addVertex(glm::vec3(vertex[0], vertex[1], vertex[2]));
  //   }
}

void MeshReader::readObj(MeshObject &structure, const char *path) {
  std::string warning, error;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  tinyobj::attrib_t attributes;

  std::string baseDir(path);
  int lastSlash = baseDir.find_last_of("/\\");

  bool ret =
      tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, path,
                       baseDir.substr(0, lastSlash).c_str(), true, false);
  structure.hasTexture() = (!attributes.texcoords.empty()) ? true : false;
  structure.hasMaterial() = (!materials.empty()) ? true : false;
  structure.hasNormal() = (!attributes.normals.empty()) ? true : false;

  if (structure.hasTexture())
    structure.getTexture().setTextureFilename(
        baseDir.substr(0, lastSlash + 1).append(materials[0].diffuse_texname));

  // Load coordinates to MeshObject
  for (int i = 0; i < attributes.vertices.size() / 3; i++) {
    structure.addVertex(glm::vec3(attributes.vertices[3 * i + 0],
                                  attributes.vertices[3 * i + 1],
                                  attributes.vertices[3 * i + 2]));
    if (structure.hasNormal()) {
      structure.addVertexNormal(i, glm::vec3(attributes.normals[3 * i + 0],
                                             attributes.normals[3 * i + 1],
                                             attributes.normals[3 * i + 2]));
    }
  }
  std::cerr << "Vertices size: " << attributes.vertices.size() / 3
            << "\nTexcoords size " << attributes.texcoords.size() / 2
            << std::endl;
  if (structure.hasTexture()) {
    for (int i = 0; i < attributes.texcoords.size(); i++) {
      structure.addTextureCoordinate(glm::vec2(
          attributes.texcoords[2 * i + 0], attributes.texcoords[2 * i + 1]));
    }
  }
  for (auto shape : shapes)
    for (int i = 0; i < shapes[0].mesh.indices.size() / 3; i++) {
      structure.addFace(glm::ivec3(shape.mesh.indices[3 * i + 0].vertex_index,
                                   shape.mesh.indices[3 * i + 1].vertex_index,
                                   shape.mesh.indices[3 * i + 2].vertex_index));
    }

  std::cout << "Read " << structure.getVerticesSize() << " vertices and "
            << structure.getFacesSize() << " faces\n";
  //   for (auto vertex : attributes.vertices) {
  // structure.addVertex(glm::vec3(vertex[0], vertex[1], vertex[2]));
  //   }
}

bool MeshReader::readTexture(MeshObject &structure, const char *path) {

  int width, height, channels;
  unsigned char *image;
  Texture &texture = structure.getTexture();
  stbi_set_flip_vertically_on_load(true);
  image = stbi_load(path, &width, &height, &channels, 0);
  if (image) {
    texture.setImage(&image, width, height, channels);
    std::cout << "Read texture file: " << path << std::endl;
    std::cout << "Image: " << width << 'x' << height << std::endl;
    return true;
  } else {
    std::cout << "Could not read texture: " << path << std::endl;
    return false;
  }
}
