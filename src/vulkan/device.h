#pragma once

#include <vulkan/vulkan.h>
#include "queue.h"

namespace blacklight
{ 
	//Get a physical and logical device
	class device
	{
	public:
		VkDevice pDevice = VK_NULL_HANDLE;
		VkPhysicalDevice pPhysicDevice = VK_NULL_HANDLE;

		//creation
		void pickPhysicalDevice(VkInstance instance);
		QueueFamily createLogicalDevice(VkQueue * graphicsQueue, VkQueue * presentQueue, VkSurfaceKHR surface);

		//cleaning
		void clean();

		//Check if the physical device is ok
		bool isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice);
	};
}