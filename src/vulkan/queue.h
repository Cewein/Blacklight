#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
	class queue
	{
	public:

		VkQueue pointer;
		uint32_t queueFamilyIndices;


		static uint32_t findQueueFamilies(VkPhysicalDevice physicalDevice);
	};
}