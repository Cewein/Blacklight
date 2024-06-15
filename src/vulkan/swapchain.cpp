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
    // Look for a specific formats, if found return it
    for (VkSurfaceFormatKHR availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    // Else return the first available format
    return availableFormats[0];
}

VkPresentModeKHR blacklight::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    // Look for a specific presentation mode (mailbox mode), if found return it
    for (VkPresentModeKHR availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    // Else retrun first in, first out mode
    return VK_PRESENT_MODE_FIFO_KHR;
}

