#include "instance.h"
#include "validation.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

void blacklight::instance::create()
{
#if !defined(NDEBUG)
    // If validation layers are enabled, check if they are supported
    // if (!validation::checkValidationLayerSupport(validation::validationLayers))
    //     throw std::runtime_error("Validation requested but not supported.");
#endif

    // Set the application information
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "blacklight renderer";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "Blacklight vulkan";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Define the instance creation information
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Get the required GLFW extensions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

#ifdef NDEBUG
    createInfo.enabledLayerCount = 0;
#else
    createInfo.enabledLayerCount = static_cast<uint32_t>(validation::validationLayers.size());
    createInfo.ppEnabledLayerNames = validation::validationLayers.data();
#endif

    // Create the Vulkan instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &this->pointer);

    // Check if the instance creation was successful
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
}

// Cleans up and destroys the Vulkan instance
void blacklight::instance::clean()
{
    vkDestroyInstance(this->pointer, nullptr);
}
