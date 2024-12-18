#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace blacklight
{
	class image
	{
	public:
		//image handle by the swapchain
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;

		//information about the swap chain
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainImageExtent;

		//gestion of the image view for the swapchain
		void createImageView(VkDevice device);
		void clear(VkDevice device);
	};
}