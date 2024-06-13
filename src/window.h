#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace blacklight
{
    /**
     * @brief Struct representing a window managed with GLFW.
     */
    struct window
    {
        int width;          // Width of the window.
        int height;         // Height of the window.

        GLFWwindow* pointer; // Pointer to the GLFW window.

        /**
         * @brief Constructor to create a window with specified dimensions and title.
         *
         * @param width Width of the window.
         * @param height Height of the window.
         * @param title Title of the window (default is "Blacklight renderer").
         */
        window(int width, int height, const char* title = "Blacklight renderer");

        /**
         * @brief Method to clean up resources associated with the window.
         */
        void clean();
    };
}
