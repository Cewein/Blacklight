#include "queue.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>

void blacklight::QueueFamily::findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	bool findSuitableQueue = false;

	for (int i = 0; i < queueFamilies.size(); i++)
	{
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			this->queueFamilyGraphics = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, this->queueFamilyGraphics, surface, &presentSupport);

		if (presentSupport) {
			this->queueFamilyPresent = i;
			findSuitableQueue = true;
		}
	}

	if(!findSuitableQueue)
		throw std::runtime_error("Failed to find a suitable queue family");
}

void blacklight::queue::clean()
{
	//todo ?
}
