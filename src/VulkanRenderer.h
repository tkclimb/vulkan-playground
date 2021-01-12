#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

typedef struct
{
  VkPhysicalDevice physicalDevce;
  VkDevice logicalDevce;
} MainDevice;

class VulkanRenderer
{
public:
  VulkanRenderer() {}
  ~VulkanRenderer() {}

  int init(GLFWwindow *newWindow)
  {
    window_ = newWindow;

    try
    {
      crateInstance();
    }
    catch (const std::runtime_error &e)
    {
      printf("Error: %s\n", e.what());
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  void cleanup()
  {
    vkDestroyInstance(instance_, nullptr);
  }

  void getPhysicalDevice()
  {
    uint32_t numDevice = 0;
    vkEnumeratePhysicalDevices(instance_, &numDevice, nullptr);
    if (numDevice == 0)
    {
      throw std::runtime_error("Can't find any physical device");
    }

    std::vector<VkPhysicalDevice> deviceList(numDevice);
    vkEnumeratePhysicalDevices(instance_, &numDevice, deviceList.data());
  }

private:
  void crateInstance()
  {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char *> instanceExtensions;
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
      instanceExtensions.push_back(glfwExtensions[i]);
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();

    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    VkResult res = vkCreateInstance(&createInfo, nullptr, &instance_);

    if (res != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create a Vulkan instance");
    }
  }

  bool checkInstanceExtensionSupport(std::vector<const char *> &checkExtensions)
  {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    for (const auto &checkExtension : checkExtensions)
    {
      bool hasExtension = false;
      for (const auto &ext : extensions)
      {
        if (strcmp(checkExtension, ext.extensionName))
        {
          hasExtension = true;
          break;
        }
      }

      if (!hasExtension)
      {
        return false;
      }
    }

    return true;
  }

  bool checkPhysicalDevice(VkPhysicalDevice &device)
  {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    return true;
  }

  GLFWwindow *window_;
  VkInstance instance_;
  MainDevice device_;
};
