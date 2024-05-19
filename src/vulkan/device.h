#pragma once

#include <vulkan/vulkan.h>
#include "queue.h"

namespace blacklight
{ 
	//Get a physical and logical device
	class device
	{
	public:
		VkDevice pDevice;
		VkPhysicalDevice pPhysicDevice;

		//creation
		void pick(VkInstance instance);
		void create(VkQueue graphicsQueue);

		//cleaning
		void clean();

		//Check if the physical device is ok
		bool isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice, QueueFamily& family, VkSurfaceKHR surface);
	};
}