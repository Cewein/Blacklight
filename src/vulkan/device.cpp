#include "device.h"
#include "queue.h"

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>

void blacklight::device::pickPhysicalDevice(VkInstance instance)
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

void blacklight::device::createLogicalDevice(VkQueue graphicsQueue, VkQueue presentQueue, VkSurfaceKHR surface)
{
	QueueFamily queueFamily = { 0, 0 };

	queueFamily.findQueueFamilies(this->pPhysicDevice, surface);

	if (queueFamily.queueFamilyGraphics < 0 && queueFamily.queueFamilyPresent)
		throw std::runtime_error("did not find a suitable graphic queue.");

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	float queuePriority = 1.0f;

	//get the info for create the device and the queue
	VkDeviceQueueCreateInfo queueCreateInfoGraphics{};
	queueCreateInfoGraphics.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfoGraphics.queueFamilyIndex = queueFamily.queueFamilyGraphics;
	queueCreateInfoGraphics.queueCount = 1;
	queueCreateInfoGraphics.pQueuePriorities = &queuePriority;
	queueCreateInfos.push_back(queueCreateInfoGraphics);

	//get the info for the presentaiton queue family (display image on screen)
	VkDeviceQueueCreateInfo queueCreateInfoPresentation{};
	queueCreateInfoPresentation.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfoPresentation.queueFamilyIndex = queueFamily.queueFamilyPresent;
	queueCreateInfoPresentation.queueCount = 1;
	queueCreateInfoPresentation.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures physicaldeviceFeatures{};
	queueCreateInfos.push_back(queueCreateInfoPresentation);

	//create the device
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
	createInfo.pEnabledFeatures = &physicaldeviceFeatures;

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
	vkGetDeviceQueue(this->pDevice, queueFamily.queueFamilyGraphics, 0, &graphicsQueue);
	vkGetDeviceQueue(this->pDevice, queueFamily.queueFamilyPresent, 0, &presentQueue);

}

void blacklight::device::clean()
{
	vkDestroyDevice(this->pDevice, nullptr);
}

bool blacklight::device::isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice, QueueFamily & family, VkSurfaceKHR surface)
{
	//check if the physical device is a GPU
	VkPhysicalDeviceProperties physicalDeviceProperties;
	VkPhysicalDeviceFeatures physicalDeviceFeatures;

	vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

	bool isGPU = physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

	//check if the gpu as suitable graphic queue;
	family.findQueueFamilies(physicalDevice, surface);
	
	return isGPU;
}
