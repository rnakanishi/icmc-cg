#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cg_window.h>

int main(int argc, char const *argv[]) {

  GLFWwindow *window;

  initializeGLFW();
  window = createWindow(800, 600);
  run(window);

  // Encerra aplicacao
  glfwTerminate();
  return 0;
}