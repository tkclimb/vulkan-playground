#include <iostream>
#include <cstdlib>
#include <vulkan/vulkan.hpp>

void selectPhysicalDevice(VkInstance &m_instance)
{
  uint32_t devCount = 0;
  vkEnumeratePhysicalDevices(m_instance, &devCount, nullptr);
  std::vector<VkPhysicalDevice> physicalDevs(devCount);
  assert(vkEnumeratePhysicalDevices(m_instance, &devCount, physicalDevs.data()) == VK_SUCCESS);
}

int main(int argc, char *argv[])
{

  const char *appName = "hello_vulkan";
  const char *layers[] = {"VK_LAYER_LUNARG_standard_validation"};
  std::vector<const char *> extensions;

  // initialize the VkApplicationInfo structure
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pNext = nullptr;
  appInfo.pApplicationName = appName;
  appInfo.pEngineName = appName;
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_2;
  // appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

  // initialize the VkInstanceCreateInfo structure
  VkInstanceCreateInfo instInfo = {};
  instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  // instInfo.pNext = nullptr;
  instInfo.flags = 0;
  instInfo.pApplicationInfo = &appInfo;
  instInfo.enabledExtensionCount = extensions.size();
  instInfo.ppEnabledExtensionNames = extensions.data();
  instInfo.enabledLayerCount = 0;
  instInfo.ppEnabledLayerNames = nullptr;

  VkInstance inst;
  VkResult res;

  res = vkCreateInstance(&instInfo, nullptr, &inst);
  if (res == VK_ERROR_INCOMPATIBLE_DRIVER)
  {
    std::cout << "cannot find a compatible Vulkan ICD\n";
    exit(-1);
  }
  else if (res)
  {
    std::cout << "unknown error\n";
    exit(-1);
  }

  vkDestroyInstance(inst, NULL);

  return 0;
}