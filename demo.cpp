#include <cg_window.hpp>
#include <vector>

class Demo : public cgicmc::Window {
public:
  Demo() : cgicmc::Window() {}

  void run() override {
    while (!glfwWindowShouldClose(_window)) {

      // Comandos de entrada
      processInput();

      // Comandos de renderizacao vao aqui
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      // etc...

      glUseProgram(_shaderProgram);
      glBindVertexArray(_VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // Controla eventos e troca os buffers para renderizacao
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
  }

  void prepare() {
    float array[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.36f, 0.0f};
    _vertices.insert(_vertices.begin(), array, array + 9);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(),
                 _vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  unsigned int loadVertexShader() {
    _vertexShader = "#version 330 core\n"
                    "layout (location = 0) in vec3 aPos;\n"
                    "void main()\n"
                    "{\n"
                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                    "}\0";

    unsigned int vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &_vertexShader, NULL);
    glCompileShader(vertexShaderId);

    int succes;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &succes);
    if (!succes) {
      char infoLog[512];
      glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
      std::cerr << "Vertex shader error: " << infoLog << std::endl;
    }
    return vertexShaderId;
  }

  unsigned int loadFragmentShader() {
    const char *shaderSource = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main()\n"
                               "{\n"
                               "   FragColor = vec4(0.8f, 0.5f, 0.2f, 1.0f);\n"
                               "}\n\0";
    unsigned int fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &shaderSource, NULL);
    glCompileShader(fragmentShaderId);

    int success = 0;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
      std::cout << "Shader source: " << shaderSource << std::endl;
      std::cerr << "Fragment shader error: " << infoLog << std::endl;
    }
    return fragmentShaderId;
  }

  void loadShaders() {
    unsigned int vshader, fshader;
    vshader = loadVertexShader();
    fshader = loadFragmentShader();

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, fshader);
    glAttachShader(_shaderProgram, vshader);
    glLinkProgram(_shaderProgram);

    int success;
    glGetShaderiv(_shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(_shaderProgram, 512, NULL, infoLog);
      std::cerr << "Shaders: " << vshader << " " << fshader << std::endl;
      std::cerr << "Program shader error: " << infoLog << std::endl;
    }

    glDeleteShader(vshader);
    glDeleteShader(fshader);
  }

protected:
  std::vector<float> _vertices;
  const char *_vertexShader;
  int _shaderProgram;
  unsigned int _VBO, _VAO;
};

int main(int argc, char const *argv[]) {
  Demo window;
  window.createWindow();
  window.loadShaders();
  window.prepare();
  window.run();
}