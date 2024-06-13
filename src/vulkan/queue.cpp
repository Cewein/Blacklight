#include "queue.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>

void blacklight::QueueFamily::findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    // Query the number of queue families available on the physical device
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    // Retrieve the properties of all queue families
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    bool findSuitableQueue = false;

    // Iterate through the queue families to find a suitable one for graphics and presentation
    for (int i = 0; i < queueFamilies.size(); i++)
    {
        // Check if the queue family supports graphics commands
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            this->queueFamilyGraphics = i;
        }

        // Check if the queue family supports presenting to the surface
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, this->queueFamilyGraphics, surface, &presentSupport);

        if (presentSupport)
        {
            this->queueFamilyPresent = i;
            findSuitableQueue = true;
        }
    }

    // If no suitable queue family was found, throw an error
    if (!findSuitableQueue) 
        throw std::runtime_error("Failed to find a suitable queue family");
}

// Placeholder for potential future cleanup operations for queues
void blacklight::queue::clean()
{
    // To be implemented if needed
}
