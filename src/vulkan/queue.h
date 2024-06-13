#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
    /**
     * @brief Struct representing the queue families for a Vulkan device.
     *
     * This struct is used to find and store the indices of queue families
     * that support graphics and presentation operations.
     */
    struct QueueFamily
    {
        uint32_t queueFamilyGraphics; ///Index of the queue family that supports graphics operations.
        uint32_t queueFamilyPresent;  ///Index of the queue family that supports presenting images to the screen.

        /**
         * @brief Finds the queue families that support graphics and presentation.
         *
         * This function queries the physical device to find queue families that
         * support graphics operations and presentation to a given surface.
         *
         * @param physicalDevice: The physical device to query.
         * @param surface: The surface to check for presentation support.
         * @throws std::runtime_error if no suitable queue families are found.
         */
        void findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    };

    /**
     * @brief Class representing a Vulkan queue.
     *
     * This class manages a Vulkan queue, which is used to submit command buffers
     * for execution on the device.
     */
    class queue
    {
    public:
        VkQueue pointer = VK_NULL_HANDLE; ///Handle to the Vulkan queue.

        /**
         * @brief Cleans up and destroys the Vulkan queue.
         *
         * This function is a placeholder for any potential cleanup operations
         * needed for the queue. Currently, it does not perform any operations.
         */
        void clean();
    };
}
