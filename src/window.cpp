#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

blacklight::window::window(int width, int heigh, const char* title)
{
	//Init windows
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	this->pointer = glfwCreateWindow(width, heigh, title, nullptr, nullptr);
	this->heigh = heigh;
	this->width = width;
}

void blacklight::window::clean()
{
	glfwDestroyWindow(this->pointer);
	glfwTerminate();
}
