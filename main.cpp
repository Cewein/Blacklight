#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

#include "src/window.h"
#include "src/vulkan/instance.h"

int main()
{
	//Init windows
	blacklight::window win(800, 600);

	//create vulkan instance
	blacklight::instance instance{};
	instance.create();

	//check 
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported\n";

	//main loop
	while (!glfwWindowShouldClose(win.pointer))
	{
		glfwPollEvents();
	}

	//Windows clean up
	win.clean();

	return 0;
}