#ifndef __CG_WINDOW_H__
#define __CG_WINDOW_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// Controla o comportamento da aplicacao quando uma tecla eh pressionada
/// ou solta
/// \param window
void processInput(GLFWwindow *window);

void initializeGLFW();

GLFWwindow *createWindow(int width, int height);

void run(GLFWwindow *window);

#endif