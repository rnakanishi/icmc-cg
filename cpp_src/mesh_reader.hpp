#ifndef __ICMCCG_MESH_READER_HPP__
#define __ICMCCG_MESH_READER_HPP__

#include <mesh_object.hpp>

class MeshReader {
public:
  void readVertices(void *data, float x, float y, float z, float w);

  static void readObj(MeshObject &structure, const char *path);

  static void readObjWithTexture(MeshObject &structure, const char *path);

  static bool readTexture(MeshObject &structure, const char *path);
};

#endif