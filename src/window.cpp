#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

blacklight::window::window(int width, int height, const char* title)
{
    // Initialize GLFW library
    glfwInit();

    // Set GLFW window hints
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Specify that GLFW will not create an OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);   // Disable window resizing

    // Create GLFW window
    this->pointer = glfwCreateWindow(width, height, title, nullptr, nullptr);

    // Store window dimensions
    this->width = width;
    this->height = height;
}

void blacklight::window::clean()
{
    // Destroy GLFW window
    glfwDestroyWindow(this->pointer);

    // Terminate GLFW library
    glfwTerminate();
}
