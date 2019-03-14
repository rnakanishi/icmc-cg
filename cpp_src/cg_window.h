#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace cg2019 {

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
}