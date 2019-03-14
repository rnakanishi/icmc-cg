#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

/// Controla o comportamento da aplicacao quando uma tecla eh pressionada
/// ou solta
/// \param window
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main(int argc, char const *argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Se estiver em ambiente MAC, descomente a seguinte linha:
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Cria janela
  GLFWwindow *window = glfwCreateWindow(800, 600, "CG 2019", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -2;
  }
  glViewport(0, 0, 800, 600);

  while (!glfwWindowShouldClose(window)) {

    // Comandos de entrada
    processInput(window);

    // Comandos de renderizacao vao aqui
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // etc...

    // Controla eventos e troca os buffers para renderizacao
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Encerra aplicacao
  glfwTerminate();
  return 0;
}