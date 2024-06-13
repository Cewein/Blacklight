#include "device.h"
#include "queue.h"
#include "validation.h"
#include "swapchain.h"

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <set>

// Picks a physical device (GPU) that supports Vulkan and is suitable for the application
void blacklight::device::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
{
    // Initialize the physical device handle to null
    this->pPhysicDevice = VK_NULL_HANDLE;

    // Get the number of available GPUs
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

    // Throw an error if no GPU supports Vulkan
    if (physicalDeviceCount == 0)
        throw std::runtime_error("Failed to find GPU with Vulkan support.");

    // Get the list of all available GPUs
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());

    // Select the first suitable GPU
    for (VkPhysicalDevice& physicalDevice : physicalDevices)
    {
        if (isPhysicalDeviceSuitable(physicalDevice, surface))
        {
            this->pPhysicDevice = physicalDevice;
            break;
        }
    }

    // Throw an error if no suitable GPU was found
    if (this->pPhysicDevice == VK_NULL_HANDLE)
        throw std::runtime_error("Failed to find a suitable GPU.");
}

// Creates a logical device and retrieves the graphics and presentation queue handles
blacklight::QueueFamily blacklight::device::createLogicalDevice(VkQueue* graphicsQueue, VkQueue* presentQueue, VkSurfaceKHR surface)
{
    QueueFamily queueFamily = { 0, 0 };

    // Find queue families that support the required operations
    queueFamily.findQueueFamilies(this->pPhysicDevice, surface);

    // Store queue creation information for each required queue family
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    float queuePriority = 1.0f;

    // Graphics queue creation info
    VkDeviceQueueCreateInfo queueCreateInfoGraphics{};
    queueCreateInfoGraphics.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfoGraphics.queueFamilyIndex = queueFamily.queueFamilyGraphics;
    queueCreateInfoGraphics.queueCount = 1;
    queueCreateInfoGraphics.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfoGraphics);

    // Presentation queue creation info
    VkDeviceQueueCreateInfo queueCreateInfoPresentation{};
    queueCreateInfoPresentation.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfoPresentation.queueFamilyIndex = queueFamily.queueFamilyPresent;
    queueCreateInfoPresentation.queueCount = 1;
    queueCreateInfoPresentation.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfoPresentation);

    // Create the logical device
    VkPhysicalDeviceFeatures physicaldeviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pEnabledFeatures = &physicaldeviceFeatures;

    // Enable required device extensions
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    // Enable validation layers if not in release mode
#ifdef NDEBUG
    createInfo.enabledLayerCount = 0;
#else
    createInfo.enabledLayerCount = static_cast<uint32_t>(validation::validationLayers.size());
    createInfo.ppEnabledLayerNames = validation::validationLayers.data();
#endif

    // Create the Vulkan device
    VkResult result = vkCreateDevice(this->pPhysicDevice, &createInfo, nullptr, &this->pDevice);

    // Throw an error if device creation failed
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create logical device");
    }

    // Retrieve the handles for the graphics and presentation queues
    vkGetDeviceQueue(this->pDevice, queueFamily.queueFamilyGraphics, 0, graphicsQueue);
    vkGetDeviceQueue(this->pDevice, queueFamily.queueFamilyPresent, 0, presentQueue);

    return queueFamily;
}

// Cleans up and destroys the Vulkan device
void blacklight::device::clean()
{
    vkDestroyDevice(this->pDevice, nullptr);
}

// Checks if a physical device (GPU) is suitable for the application
bool blacklight::device::isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    // Get properties and features of the physical device
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

    // Check if the device is a discrete GPU
    bool isGPU = physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

    // Check if required extensions are supported
    bool extensionSupported = checkForExtensionSupport(physicalDevice);

    // Check if the swap chain is adequate
    bool swapChainAdequate = false;
    if (extensionSupported)
    {
        swapchainSupportDetails swapChainSupport = querySwapchainSupport(physicalDevice, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return isGPU && extensionSupported && swapChainAdequate;
}

// Checks if a physical device supports the required extensions
bool blacklight::device::checkForExtensionSupport(VkPhysicalDevice physicalDevice)
{
    // Get the number of supported extensions
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

    // Get the list of supported extensions
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    // Check if all required extensions are supported
    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    for (const VkExtensionProperties& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}