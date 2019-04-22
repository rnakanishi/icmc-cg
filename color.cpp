#include <cg_window.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ColorDemo : public cgicmc::Window {
public:
  ColorDemo() : cgicmc::Window() {}

  void run() override {
    while (!glfwWindowShouldClose(_window)) {
      // Comandos de entrada
      processInput();

      // Comandos de renderizacao vao aqui
      glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      // etc...

      _shader.useShader();

      // float green = (std::cos(glfwGetTime()) / 2) + 0.5;
      // int colorLoc = glGetUniformLocation(_shader.getId(), "vertexColor");
      // glUniform4f(colorLoc, 0.0, green, 0.0, 1.0);

      glBindVertexArray(_VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // Controla eventos e troca os buffers para renderizacao
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
  }
  /*
    // Codigo alternativo:
    // Os buffers podem ser construidos separadamente
    void loadScene() {
      _shader.loadVertexShader("./assets/shaders/color.vert");
      _shader.loadFragmentShader("./assets/shaders/color.frag");

      _vertices.emplace_back(glm::vec3(-0.5f, -0.286f, 0.0f));
      _vertices.emplace_back(glm::vec3(0.5f, -0.286f, 0.0f));
      _vertices.emplace_back(glm::vec3(0.0f, 0.574f, 0.0f));

      _color.emplace_back(glm::vec3(1.0, 0.0, 0.0));
      _color.emplace_back(glm::vec3(0.0, 1.0, 0.0));
      _color.emplace_back(glm::vec3(0.0, 0.0, 1.0));

      glGenVertexArrays(1, &_VAO);
      glGenBuffers(1, &_vertexVBO);
      glGenBuffers(1, &_colorVBO);

      glBindVertexArray(_VAO);

      // Buffer das coordenadas
      glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _vertices.size(),
                   _vertices.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
      glEnableVertexAttribArray(0);

      // Buffer das cores
      glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _color.size(),
                   _color.data(), GL_STATIC_DRAW);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
      glEnableVertexAttribArray(1);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
    */

  void loadScene() {
    _shader.loadVertexShader("./assets/shaders/color.vert");
    _shader.loadFragmentShader("./assets/shaders/color.frag");

    _vertices.emplace_back(glm::vec3(-0.5f, -0.286f, 0.0f));
    _vertices.emplace_back(glm::vec3(1.0, 0.0, 0.0)); // Cor
    _vertices.emplace_back(glm::vec3(0.5f, -0.286f, 0.0f));
    _vertices.emplace_back(glm::vec3(0.0, 1.0, 0.0)); // Cor
    _vertices.emplace_back(glm::vec3(0.0f, 0.574f, 0.0f));
    _vertices.emplace_back(glm::vec3(0.0, 0.0, 1.0)); // Cor

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_vertexVBO);

    glBindVertexArray(_VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _vertices.size(),
                 _vertices.data(), GL_STATIC_DRAW);

    // Posicao das coordendas
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Posicao das cores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3),
                          (void *)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    // Liberando os buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

protected:
  cgicmc::Shader _shader;
  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _color;
  unsigned int _vertexVBO, _colorVBO, _VAO;
};

int main(int argc, char const *argv[]) {
  ColorDemo window;

  window.createWindow();
  window.loadScene();
  window.run();

  return 0;
}