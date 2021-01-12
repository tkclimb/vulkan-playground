#include <iostream>
#include <cassert>
// #include <vulkan/vulkan.hpp>

#include "VulkanRenderer.h"

// #define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
// #include <glm/glm.hpp>
// #include <glm/mat4x4.hpp>

#define P(X) std::cout << #X << ": " << X << std::endl;

GLFWwindow *window;
VulkanRenderer renderer;

void initWindow(const std::string wName, const int width, const int height)
{
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main(int argc, char const *argv[])
{
  initWindow("Test Window", 800, 600);

  if (renderer.init(window) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  // glfwInit();
  // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  // GLFWwindow *window = glfwCreateWindow(800, 600, "test window", nullptr, nullptr);

  // uint32_t numExtensions = 0;
  // vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr);

  // std::cout << "num extension: " << numExtensions << std::endl;

  // glm::mat4 testMatrix(1.0f);
  // glm::vec4 testVector(1.0f);
  // auto testResult = testMatrix * testVector;

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  std::cout << "done!!" << std::endl;
  return 0;
}
