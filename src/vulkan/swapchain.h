#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace blacklight
{
	struct swapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	//check if the there is enough support for the swapchain
	swapchainSupportDetails querySwapchainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	
	//get the different formats for the swapchain
	VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
} 