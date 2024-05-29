#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "queue.h"

namespace blacklight
{ 
	//Get a physical and logical device
	class device
	{
	public:

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VkDevice pDevice = VK_NULL_HANDLE;
		VkPhysicalDevice pPhysicDevice = VK_NULL_HANDLE;

		//creation
		void pickPhysicalDevice(VkInstance instance);
		QueueFamily createLogicalDevice(VkQueue * graphicsQueue, VkQueue * presentQueue, VkSurfaceKHR surface);

		//cleaning
		void clean();

		//Check if the physical device is ok
		bool isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice);
		bool checkForExtensionSupport(VkPhysicalDevice physicalDevice);
	};
}