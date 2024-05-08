#include "validation.h"

#include <vulkan/vulkan.h>

bool blacklight::validation::checkValidationLayerSupport(const std::vector<const char*> validationLayers)
{
	uint32_t layerCount;

	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availbleLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availbleLayers.data());


	bool layerFound = false;

	for (const char* layerName : validationLayers)
	{
		for (VkLayerProperties& layerProperties : availbleLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}
	}

	return layerFound;
}
