#include "swapchain.h"

blacklight::swapchainSupportDetails blacklight::querySwapchainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    blacklight::swapchainSupportDetails details;

    // Query surface capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

    // Query surface formats count
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, VK_NULL_HANDLE);

    if (formatCount != 0)
    {
        // Resize and retrieve surface formats
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
    }

    // Query present modes count
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        // Resize and retrieve present modes
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
    }

    // Return the collected details
    return details;
}

VkSurfaceFormatKHR blacklight::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    // Placeholder implementation, replace with actual logic
    return VkSurfaceFormatKHR();
}

