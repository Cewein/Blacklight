#include "surface.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN64
#include <GLFW/glfw3native.h>

#include <stdexcept>

void blacklight::surface::create(GLFWwindow* window, VkInstance instance)
{
    // Create a Vulkan surface for the given window using GLFW
    if (glfwCreateWindowSurface(instance, window, nullptr, &this->pointer) != VK_SUCCESS)
    {
        // Throw an error if the surface creation fails
        throw std::runtime_error("GLFW failed to create a surface");
    }
}

void blacklight::surface::clean(VkInstance instance)
{
    // Destroy the Vulkan surface
    vkDestroySurfaceKHR(instance, this->pointer, nullptr);
}
