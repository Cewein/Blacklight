#include "device.h"
#include "queue.h"

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>

void blacklight::device::pick(VkInstance instance)
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

void blacklight::device::create(VkQueue graphicsQueue)
{
	int queueIndices = queue::findQueueFamilies(this->pPhysicDevice);

	if (queueIndices < 0)
		throw std::runtime_error("did not find a suitable graphic queue.");

	//get the info for create the deive and the queue
	VkDeviceQueueCreateInfo queueCreateInfo{};

	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = queueIndices;
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};
	
	//create the device
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

#ifdef NDEBUG
	createInfo.enabledLayerCount = 0;
#else
	createInfo.enabledLayerCount = (uint32_t)(validation::validationLayers.size());
	createInfo.ppEnabledLayerNames = validation::validationLayers.data();
#endif
	//create the instance
	VkResult result = vkCreateDevice(this->pPhysicDevice,&createInfo, nullptr,&this->pDevice);

	if (result == VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create logical device");
	}

	//get the queue handle for a specific device
	vkGetDeviceQueue(this->pDevice, queueIndices, 0, &graphicsQueue);

}

void blacklight::device::clean()
{
	vkDestroyDevice(this->pDevice, nullptr);
}

bool blacklight::device::isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice)
{
	//check if the physical device is a GPU
	VkPhysicalDeviceProperties physicalDeviceProperties;
	VkPhysicalDeviceFeatures physicalDeviceFeatures;

	vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

	bool isGPU = physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

	//check if the gpu as graphic queue;
	int queueIndices = queue::findQueueFamilies(physicalDevice);
	
	return isGPU && (queueIndices >= 0);
}
