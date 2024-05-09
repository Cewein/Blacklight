#include "queue.h"

#include <vulkan/vulkan.h>
#include <vector>

uint32_t blacklight::queue::findQueueFamilies(VkPhysicalDevice physicalDevice)
{
	int queueFamilyIndices = -1;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	for (int i = 0; i < queueFamilies.size(); i++)
	{
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndices = i;
		}
	}

	return queueFamilyIndices;
}
