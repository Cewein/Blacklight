#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "src/window.h"
#include "src/vulkan/instance.h"
#include "src/vulkan/extension.h"

int main()
{
	//Init windows
	blacklight::window win(800, 600);

	//create vulkan instance
	blacklight::instance instance{};
	instance.create();

	//check the extension availble
	blacklight::supportedExtensions();

	//main loop
	while (!glfwWindowShouldClose(win.pointer))
	{
		glfwPollEvents();
	}

	//Windows clean up
	instance.clean();
	win.clean();

	return 0;
}