#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

#include "extension.h"

void blacklight::supportedExtensions()
{
    // Query the number of available instance extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // Allocate a vector to hold the extension properties
    std::vector<VkExtensionProperties> extensions(extensionCount);

    // Print the number of supported extensions
    std::cout << extensionCount << " extensions supported" << std::endl;

    // Retrieve the properties of all available extensions
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // Print the names of all available extensions
    std::cout << "Available extensions:" << std::endl;
    for (VkExtensionProperties& extension : extensions)
    {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
}
