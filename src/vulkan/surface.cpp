#include "surface.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN64
#include <GLFW/glfw3native.h>

#include <stdexcept>

void blacklight::surface::create(GLFWwindow* window, VkInstance instnace)
{
	if (glfwCreateWindowSurface(instnace, window, NULL, &this->vkSurface) != VK_SUCCESS)
	{
		throw std::runtime_error("GLFW did not create a surface");
	}
}

void blacklight::surface::clean(VkInstance instance)
{
	vkDestroySurfaceKHR(instance, this->vkSurface, nullptr);
}
