#include <shader.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace cgicmc {

Shader::Shader() {}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
  _vertexShader = loadShader(vertexShaderPath, GL_VERTEX_SHADER);
  _fragmentShader = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
  _linkProgram();
}

void Shader::_linkProgram() {
  _programId = glCreateProgram();
  glAttachShader(_programId, _vertexShader);
  glAttachShader(_programId, _fragmentShader);
  glLinkProgram(_programId);

  int success;
  glGetProgramiv(_programId, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(_programId, 512, NULL, infoLog);
    std::cerr << "Shader::_linkProgram: " << infoLog << std::endl;
  }
  glDeleteShader(_vertexShader);
  glDeleteShader(_fragmentShader);
}

unsigned int Shader::loadShader(const char *shaderPath,
                                unsigned int shaderType) {
  std::string code;
  const char *shaderCode;
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(shaderPath);
    if (file.is_open()) {
      std::stringstream stream;
      stream << file.rdbuf();
      file.close();
      code = stream.str();
    } else
      std::cerr << "File not found\n";
  } catch (std::ifstream::failure err) {
    std::cerr << "Shader::loadShader: could not read " << shaderPath
              << std::endl;
  }
  shaderCode = code.c_str();

  unsigned int shader = -1;
  shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderCode, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "Shader::loadShader: shader compilation failed:\n\t" << infoLog
              << std::endl;
  }

  _needsLink = true;
  return shader;
}

void Shader::useShader() {
  if (_needsLink) {
    _linkProgram();
    _needsLink = false;
  }
  glUseProgram(_programId);
}

unsigned int Shader::getId() { return _programId; }

void Shader::loadVertexShader(const char *vertexShaderPath) {
  _vertexShader = loadShader(vertexShaderPath, GL_VERTEX_SHADER);
}

void Shader::loadFragmentShader(const char *fragmentShaderPath) {
  _fragmentShader = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
}

void Shader::loadGeometryShader(const char *geometryShaderPath) {
  loadShader(geometryShaderPath, GL_GEOMETRY_SHADER);
}

} // namespace cgicmc
