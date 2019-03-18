#ifndef __CG_WINDOW_HPP__
#define __CG_WINDOW_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace cgicmc {

class Window {
public:
  ///
  /// Instantiates glfw environment
  Window();

  ///
  /// Finalizes glfw environment
  ~Window();

  ///
  /// Create single window of 800x600 size
  void createWindow();

  ///
  /// Run the application in a loop.
  void run();

protected:
  void processInput(GLFWwindow *window);

  int _viewPortSize;
  GLFWwindow *_window;
};
} // namespace cgicmc

#endif