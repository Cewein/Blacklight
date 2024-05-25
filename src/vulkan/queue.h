#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
	struct QueueFamily
	{
		// Index of the queue family that this queue belongs to
		uint32_t queueFamilyGraphics;

		// Index of the queue family that supports presenting (displaying images to the screen)
		uint32_t queueFamilyPresent;

		void findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	};

	class queue
	{
	public:

		VkQueue pointer;

		QueueFamily family;

		void clean();
	};
}