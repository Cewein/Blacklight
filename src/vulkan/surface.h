#pragma once

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace blacklight
{
	class surface
	{
	public:

		VkSurfaceKHR vkSurface;

		void create(GLFWwindow* window, VkInstance instnace);
		void clean(VkInstance instance);
	};
}