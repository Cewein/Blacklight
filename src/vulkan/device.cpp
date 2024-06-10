#include "device.h"
#include "queue.h"
#include "validation.h"
#include "swapchain.h"

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <set>

void blacklight::device::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
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
		if (isPhysicalDeviceSuitable(physicalDevice, surface))
		{
			this->pPhysicDevice = physicalDevice;
			break;
		}
	}

	if(this->pPhysicDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a good GPU.");

}

blacklight::QueueFamily blacklight::device::createLogicalDevice(VkQueue * graphicsQueue, VkQueue * presentQueue, VkSurfaceKHR surface)
{
	QueueFamily queueFamily = { 0, 0 };

	//check if we can find a family, if not throw (see function)
	queueFamily.findQueueFamilies(this->pPhysicDevice, surface);

	//we can have multiple families, so vector of queue creation info
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
	queueCreateInfos.push_back(queueCreateInfoPresentation);


	//create the logical device
	VkPhysicalDeviceFeatures physicaldeviceFeatures{};
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
	createInfo.pEnabledFeatures = &physicaldeviceFeatures;

	createInfo.enabledExtensionCount = (uint32_t)(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

#ifdef NDEBUG
	createInfo.enabledLayerCount = 0;
#else
	createInfo.enabledLayerCount = (uint32_t)(validation::validationLayers.size());
	createInfo.ppEnabledLayerNames = validation::validationLayers.data();
#endif
	//create the instance
	VkResult result = vkCreateDevice(this->pPhysicDevice,&createInfo, nullptr,&this->pDevice);

	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create logical device");
	}

	//get the queue handle for a specific device
	vkGetDeviceQueue(this->pDevice, queueFamily.queueFamilyGraphics, 0, graphicsQueue);
	vkGetDeviceQueue(this->pDevice, queueFamily.queueFamilyPresent, 0, presentQueue);

	return queueFamily;
}

void blacklight::device::clean()
{
	vkDestroyDevice(this->pDevice, nullptr);
}

bool blacklight::device::isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
	//check if the physical device is a GPU
	VkPhysicalDeviceProperties physicalDeviceProperties;
	VkPhysicalDeviceFeatures physicalDeviceFeatures;

	vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

	bool isGPU = physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

	bool extensionSupported = checkForExtensionSupport(physicalDevice);

	bool swapChainAdequate = false;
	if (extensionSupported)
	{
		swapchainSupportDetails swapChainSupport = querySwapchainSupport(physicalDevice, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	
	return isGPU && extensionSupported && swapChainAdequate;
}

bool blacklight::device::checkForExtensionSupport(VkPhysicalDevice physicalDevice)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const VkExtensionProperties& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}


	return requiredExtensions.empty();
}
