#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace blacklight
{
    /// 
    /// @brief Struct containing details about swapchain support.
    /// 
    /// This struct aggregates Vulkan surface capabilities, supported surface formats,
    /// and presentation modes for determining swapchain configuration.
    /// 
    struct swapchainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities; // Surface capabilities (e.g., min/max image counts).
        std::vector<VkSurfaceFormatKHR> formats; // Supported surface formats (color space, pixel format).
        std::vector<VkPresentModeKHR> presentModes; // Supported presentation modes (e.g., FIFO, immediate).
    };

    /// 
    /// @brief Queries the swapchain support details for a given physical device and surface.
    /// 
    /// This function queries Vulkan for the capabilities, supported formats, and presentation modes
    /// of a swapchain on the specified physical device and surface.
    /// 
    /// @param physicalDevice: Vulkan physical device to query.
    /// @param surface: Vulkan surface to query swapchain support for.
    /// @return swapchainSupportDetails: containing capabilities, formats, and presentation modes.
    /// 
    swapchainSupportDetails querySwapchainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    /// 
    /// @brief Chooses the best surface format from the available formats.
    /// 
    /// This function selects the optimal surface format from the list of available formats
    /// based on criteria such as color space and pixel format preferences.
    /// 
    /// @param availableFormats: List of available surface formats to choose from.
    /// @return VkSurfaceFormatKHR: representing the chosen surface format.
    /// 
    VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    
    /// 
    /// @brief Chooses the best present mode from the possible ones.
    /// 
    /// @param availablePresentMode: List of available present modes to choose from.
    /// @return VkPresentModeKHR: representing the chosen surface format.
    /// 
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
}
