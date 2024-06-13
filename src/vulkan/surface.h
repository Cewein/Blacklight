#pragma once

#include <vulkan/vulkan.h> 
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>    

namespace blacklight
{
    /**
     * @brief Class representing a Vulkan surface.
     *
     * This class manages a Vulkan surface, which is used for presenting
     * rendered images to windows or displays.
     */
    class surface
    {
    public:
        VkSurfaceKHR pointer = VK_NULL_HANDLE;  ///Handle to the Vulkan surface.

        /**
         * @brief Creates a Vulkan surface for a given GLFW window.
         *
         * This function creates a Vulkan surface using GLFW for the specified window
         * and Vulkan instance.
         *
         * @param window Pointer to the GLFW window for which the surface is created.
         * @param instance Vulkan instance used to create the surface.
         * @throws std::runtime_error if surface creation fails.
         */
        void create(GLFWwindow* window, VkInstance instance);

        /**
         * @brief Cleans up and destroys the Vulkan surface.
         *
         * This function destroys the Vulkan surface to free up resources.
         *
         * @param instance Vulkan instance that owns the surface to be destroyed.
         */
        void clean(VkInstance instance);
    };
}
