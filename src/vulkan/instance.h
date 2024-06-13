#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
    /// 
    /// @brief Struct representing a Vulkan instance.
    /// 
    /// This struct manages the creation and destruction of a Vulkan instance,
    /// which is required for interacting with the Vulkan API.
    /// 
    struct instance
    {
        VkInstance pointer = VK_NULL_HANDLE;  ///Handle to the Vulkan instance.

        /// 
        /// @brief Creates a Vulkan instance.
        /// 
        /// This function sets up the application information, configures the necessary
        /// extensions and validation layers (if enabled), and creates the Vulkan instance.
        /// 
        /// @throws std::runtime_error if the instance creation fails.
        /// 
        void create();

        /// 
        /// @brief Cleans up and destroys the Vulkan instance.
        /// 
        /// This function destroys the Vulkan instance to free up resources.
        /// 
        void clean();
    };
}
