#include <cg_window.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.hpp>

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
      glBindTexture(GL_TEXTURE_2D, _textureBuffer);
      glBindVertexArray(_VAO);
      glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

      // Controla eventos e troca os buffers para renderizacao
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
  }

  void loadScene() {
    _shader.loadVertexShader("./assets/shaders/texture.vert");
    _shader.loadFragmentShader("./assets/shaders/texture.frag");
    /*
        _vertices.emplace_back(glm::vec3(-0.75f, -0.75f, 0.0f));
        _vertices.emplace_back(glm::vec3(0.75f, -0.75f, 0.0f));
        _vertices.emplace_back(glm::vec3(-0.75f, 0.75f, 0.0f));

        _vertices.emplace_back(glm::vec3(0.75f, -0.75f, 0.0f));
        _vertices.emplace_back(glm::vec3(0.75f, 0.75f, 0.0f));
        _vertices.emplace_back(glm::vec3(-0.75f, 0.75f, 0.0f)); */
    /*
        _vertexTexture.emplace_back(glm::vec2(-1.0f, -1.0f));
        _vertexTexture.emplace_back(glm::vec2(2.0f, -1.0f));
        _vertexTexture.emplace_back(glm::vec2(-1.0f, 2.0f));

        _vertexTexture.emplace_back(glm::vec2(2.0f, -1.0f));
        _vertexTexture.emplace_back(glm::vec2(2.0f, 2.0f));
        _vertexTexture.emplace_back(glm::vec2(-1.0f, 2.0f)); */

    /* _vertexTexture.emplace_back(glm::vec2(0.0f, 0.0f));
    _vertexTexture.emplace_back(glm::vec2(1.0f, 0.0f));
    _vertexTexture.emplace_back(glm::vec2(0.0f, 1.0f));

    _vertexTexture.emplace_back(glm::vec2(1.0f, 0.0f));
    _vertexTexture.emplace_back(glm::vec2(1.0f, 1.0f));
    _vertexTexture.emplace_back(glm::vec2(0.0f, 1.0f)); */

    _vertices.emplace_back(glm::vec3(-0.5f, -0.286f, 0.0f));
    _vertices.emplace_back(glm::vec3(0.5f, -0.286f, 0.0f));
    _vertices.emplace_back(glm::vec3(0.0f, 0.574f, 0.0f));
    _vertexTexture.emplace_back(glm::vec2(0.0f, 0.0f));
    _vertexTexture.emplace_back(glm::vec2(1.0f, 0.0f));
    _vertexTexture.emplace_back(glm::vec2(0.5f, 1.0f));

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_vertexVBO);
    glGenBuffers(1, &_texCoordVBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _vertices.size(),
                 _vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // // Buffer das coordenadas de texture
    glBindBuffer(GL_ARRAY_BUFFER, _texCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * _vertexTexture.size(),
                 _vertexTexture.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
                          (void *)0);
    glEnableVertexAttribArray(2);

    // Parametros da textura
    glGenTextures(1, &_textureBuffer);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    float borderColor[] = {0.3, 0.45, 0.18, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Image de textura
    int width, height, channels;
    unsigned char *image;
    char path[] = "./assets/textures/brick.jpg";

    stbi_set_flip_vertically_on_load(true);
    image = stbi_load(path, &width, &height, &channels, 0);
    if (image) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, image);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(image);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

protected:
  cgicmc::Shader _shader;
  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _color;
  std::vector<glm::vec2> _vertexTexture;
  unsigned int _VBO, _vertexVBO, _colorVBO, _textureVBO, _texCoordVBO,
      _textureBuffer, _VAO;
};

int main(int argc, char const *argv[]) {
  ColorDemo window;

  window.createWindow();
  window.loadScene();
  window.run();

  return 0;
}