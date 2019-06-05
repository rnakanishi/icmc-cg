#ifndef __ICMCCG_TRIANGLE_MESH_HPP__
#define __ICMCCG_TRIANGLE_MESH_HPP__

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <shader.hpp>
#include <texture.hpp>
#include <vector>

class MeshObject {
public:
  MeshObject();

  /**
   * @brief Creates vbo, vao and ebo buffers.
   *
   **/
  void initialize();

  /**
   * @brief Load an obj mesh and assemble buffers created before.
   *
   **/
  void loadObjMesh(const char *objPath);

  void centerizeObject();

  void loadTexture();

  void addTextureCoordinate(glm::vec2 texCoord);

  uint addVertex(glm::vec3 vertex);

  uint addFace(glm::ivec3 face);

  void assignVertices(std::vector<glm::vec3> &vertices);

  void removeAllVertices();

  uint removeDoubles();

  void addVertexNormal(uint vertexId, glm::vec3 normal);

  Texture &getTexture();

  bool &hasTexture();
  bool &hasNormal();
  bool &hasMaterial();

  void hasTexture(bool value);
  void hasNormal(bool value);
  void hasMaterial(bool value);

  /**
   * @brief Get the Vertices Size value
   *
   * @return uint
   **/
  uint getVerticesSize();

  /**
   * @brief Get the Faces Size
   *
   * @return uint
   **/
  uint getFacesSize();

  /**
   * @brief Get the vertex object corresponding to index
   *
   * @param index of the desired vertex
   * @return glm::vec3
   **/
  glm::vec3 getVertex(uint index);

  /**
   * @brief Get the Face object corresponding to index
   *
   * @param index of the desired face
   * @return glm::ivec3
   **/
  glm::ivec3 getFace(uint index);

  glm::vec3 getCentroid();

  glm::vec3 getBboxCenter();

  glm::vec3 getBBoxSize();

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

  glm::vec3 _centroid;
  glm::vec3 _bboxMax, _bboxMin;

  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _vertexNormal;
  std::vector<glm::ivec3> _faces; //!< Face composed by three vertices

  unsigned int _vbo[3], _vao, _ebo, _tex;
  std::vector<glm::vec3> _vertexColor;
  std::vector<glm::vec2> _vertexTexture;

  Texture _textureImage;
  std::vector<glm::mat4> _modelMatrix;
  int _instanceCount;
  bool _hasTexture, _hasNormal, _hasMaterial;
};

#endif