#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "queue.h"

namespace blacklight
{
    /// This class manages the creation and handling of Vulkan physical and logical devices
    class device
    {
    public:
        /// List of required device extensions
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        /// Handle to the Vulkan logical device
        VkDevice pDevice = VK_NULL_HANDLE;

        /// Handle to the Vulkan physical device (GPU)
        VkPhysicalDevice pPhysicDevice = VK_NULL_HANDLE;

        /// Picks a suitable physical device (GPU) that supports Vulkan
        /// @param instance The Vulkan instance
        /// @param surface The Vulkan surface
        void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

        /// Creates a logical device and retrieves the graphics and presentation queue handles
        /// @param graphicsQueue Pointer to store the graphics queue handle
        /// @param presentQueue Pointer to store the presentation queue handle
        /// @param surface The Vulkan surface
        /// @return QueueFamily The queue family indices for graphics and presentation
        QueueFamily createLogicalDevice(VkQueue* graphicsQueue, VkQueue* presentQueue, VkSurfaceKHR surface);

        /// Cleans up and destroys the Vulkan device
        void clean();

        /// Checks if the physical device is suitable for the application
        /// @param physicalDevice The physical device to check
        /// @param surface The Vulkan surface
        /// @return True if the device is suitable, false otherwise
        bool isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

        /// Checks if the physical device supports the required extensions
        /// @param physicalDevice The physical device to check
        /// @return True if all required extensions are supported, false otherwise
        bool checkForExtensionSupport(VkPhysicalDevice physicalDevice);
    };
}
