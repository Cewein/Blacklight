#include "validation.h"

#include <vulkan/vulkan.h>

bool blacklight::validation::checkValidationLayerSupport(const std::vector<const char*> validLayers)
{
    uint32_t layerCount;

    // Query the number of available instance layers
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    // Retrieve the properties of all available instance layers
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    bool layerFound = false;

    // Check if each validation layer in validationLayers is supported
    for (const char* layerName : validLayers)
    {
        for (const VkLayerProperties& layerProperties : availableLayers)
        {
            // Compare the layer names to check for a match
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                // Layer found, mark it as supported and break out of the loop
                layerFound = true;
                break;
            }
        }
    }

    return layerFound;
}
