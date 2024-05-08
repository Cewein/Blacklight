#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{ 

	class device
	{
	public:
		VkDevice pDevice;
		VkPhysicalDevice pPhysicDevice;

		void create(VkInstance instance);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device);
	};
}