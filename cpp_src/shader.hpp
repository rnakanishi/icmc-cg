#ifndef __CG_SHADER_HPP__
#define __CG_SHADER_HPP__

#include <glad/glad.h>

namespace cgicmc {
class Shader {

public:
  Shader();
  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

  // Configura a OpenGL para utilizar o shader
  void useShader();

  // Carrega o arquivo do shader dependendo do tipo
  unsigned int loadShader(const char *shaderPath, unsigned int shaderType);

  void loadVertexShader(const char *geometryShaderPath);

  void loadGeometryShader(const char *geometryShaderPath);

  void loadFragmentShader(const char *fragmentShaderPath);

  // Retorna o identificador criado pela OpenGL
  unsigned int getId();

protected:
  void _linkProgram();

  unsigned int _programId, _vertexShader, _fragmentShader;
  bool _needsLink;
};

} // namespace cgicmc

#endif