#include "instance.h"
#include "validation.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

void blacklight::instance::create()
{
#if !defined(NDEBUG)
	//if validation enable check if supported
	if (!validation::checkValidationLayerSupport(validation::validationLayers))
		throw std::runtime_error("Validation requested but not fine.");
#endif

	//Set the app information
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "blacklight renderer";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Blacklight vulkan";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	//define the Instance information
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	//get the information of glfw
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;


#ifdef NDEBUG
	createInfo.enabledLayerCount = 0;
#else
	createInfo.enabledLayerCount = (uint32_t)(validation::validationLayers.size());
	createInfo.ppEnabledLayerNames = validation::validationLayers.data();
#endif

	//create the instance
	VkResult result = vkCreateInstance(&createInfo, nullptr, &this->pointer);

	//check if it was successful
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Fail to create an instance");
	}
}

void blacklight::instance::clean()
{
	vkDestroyInstance(this->pointer, nullptr);
}
