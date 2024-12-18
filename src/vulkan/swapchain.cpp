#include <GLFW/glfw3.h>
#include <algorithm>

#include "swapchain.h"
#include "queue.h"
#include <stdexcept>

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

VkExtent2D blacklight::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,  const blacklight::window& win)
{
    //if not UINT32_MAX is almost mean that current extent is already set
    if(capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    
    VkExtent2D actualExtent = 
    {
        (uint32_t)win.width,
        (uint32_t)win.height
    };

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}

void blacklight::swapchain::createSwapChain(const blacklight::window &win, VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface)
{
    swapchainSupportDetails swapChainSupport = querySwapchainSupport(physicalDevice, surface);

    VkSurfaceFormatKHR surfaceFormat = chooseSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, win);

    //get the number of image availible in the swapchain
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if(swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamily family;
    family.findQueueFamilies(physicalDevice,surface);
    uint32_t queueFamilyIndices[] = {family.queueFamilyGraphics,family.queueFamilyPresent};

    //get the sharing mode, see vk doc for more info
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if(family.queueFamilyGraphics != family.queueFamilyPresent)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    //validate the creation of the swap chain
    if(vkCreateSwapchainKHR(device,&createInfo,nullptr,&this->pointer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create swap chain !");
    }

    vkGetSwapchainImagesKHR(device, this->pointer, &imageCount, nullptr);
    this->swapChainImage.resize(imageCount);
    vkGetSwapchainImagesKHR(device, this->pointer, &imageCount, swapChainImage.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainImageExtent = extent;

}

void blacklight::swapchain::clean(VkDevice device)
{
    vkDestroySwapchainKHR(device, this->pointer,nullptr);
}
