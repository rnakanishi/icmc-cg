#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mesh_object.hpp>
#include <mesh_reader.hpp>
#include <iostream>
#include <shader.hpp>

int main(int argc, char const *argv[]) {

  MeshObject object;

  object.loadObjMesh("./assets/3d_models/newdog.obj");
  object.loadTexture();

  std::cout << "Vertices:\n";
  for (int i = 0; i < object.getVerticesSize(); i++) {
    glm::vec3 vertex = object.getVertex(i);
    std::cout << vertex[0] << " " << vertex[1] << " " << vertex[2] << std::endl;
  }

  std::cout << "Faces (indices dos vertices): \n";
  for (int f = 0; f < object.getFacesSize(); f++) {
    glm::ivec3 face = object.getFace(f);
    std::cout << face[0] << " " << face[1] << " " << face[2] << std::endl;
  }

  return 0;
}