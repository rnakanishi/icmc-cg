#ifndef __CGICMC_MESH_OBJECT_HPP__
#define __CGICMC_MESH_OBJECT_HPP__

#include <glad/glad.h>
#include <structures/triangle_mesh.h>
#include <shader/shader.hpp>
#include <shader/texture.hpp>
#include <map>

namespace cgicmc {
class MeshObject {
public:
  MeshObject();

  void initialize();

  void draw(Shader shader);

  void loadObjMesh(const char *objPath);

  void loadTexture();

  void addTextureCoordinate(glm::vec2 texCoord);

  uint addVertex(glm::vec3 vertex);

  void addVertexNormal(uint vertexId, glm::vec3 normal);

  glm::vec3 getCentroid();

  glm::vec3 getBboxCenter();

  glm::vec3 getBBoxSize();

  Texture &getTexture();

  bool &hasTexture();
  bool &hasNormal();
  bool &hasMaterial();

  void hasTexture(bool value);
  void hasNormal(bool value);
  void hasMaterial(bool value);

protected:
  void _computeCentroid();

  /**
   * @brief This method do the reading function itself. Using tiny object
   *functions, assign properly the vertices coordinates and faces. If file
   *contains texture coordinates, they are assigned as well
   *
   * @param objPath
   **/
  void _readObj(const char *objPath);
  // TODO: change vbo to accept any size
  unsigned int _vbo[3], _vao, _ebo, _tex;
  std::vector<glm::vec3> _vertexColor;
  std::vector<glm::vec2> _vertexTexture;

  Texture _textureImage;
  glm::vec3 _centroid;
  glm::vec3 _bboxMax, _bboxMin;
  bool _hasTexture, _hasNormal, _hasMaterial;
};

} // namespace cgicmc

#endif