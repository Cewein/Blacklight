#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

#include "extension.h"

void blacklight::supportedExtensions()
{
	//check the extension availble
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	std::cout << extensionCount << " extensions supported" << std::endl;

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "Available extensions:" << std::endl;
	for (VkExtensionProperties& extension : extensions)
	{
		std::cout << "\t" << extension.extensionName << std::endl;
	}
}