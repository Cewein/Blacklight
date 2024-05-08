#include "device.h"

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>

void blacklight::device::create(VkInstance instance)
{
	this->pPhysicDevice = VK_NULL_HANDLE;
	
	//get the number of availible GPUs
	uint32_t physicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

	if (physicalDeviceCount == 0)
		throw std::runtime_error("Failed to find GPU with vulkan support.");

	//get the list of all the gpus
	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());

	//select the first availible gpu
	for (VkPhysicalDevice& physicalDevice : physicalDevices)
	{
		if (isPhysicalDeviceSuitable(physicalDevice))
		{
			this->pPhysicDevice = physicalDevice;
			break;
		}
	}

	if(this->pPhysicDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a good GPU.");

}

bool blacklight::device::isPhysicalDeviceSuitable(VkPhysicalDevice device)
{
	return true;
}
