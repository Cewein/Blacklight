#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "src/window.h"
#include "src/vulkan/instance.h"
#include "src/vulkan/extension.h"
#include "src/vulkan/device.h"
#include "src/vulkan/surface.h"

int main()
{
	//Init windows
	blacklight::window win(800, 600);

	//create vulkan instance
	blacklight::instance instance{};
	instance.create();

	//create surface
	blacklight::surface surface{};
	surface.create(win.pointer, instance.pInstance);
	
	//pick the physical device
	blacklight::device device{};
	device.pick(instance.pInstance);

	//check the extension availble
	blacklight::supportedExtensions();

	//main loop
	while (!glfwWindowShouldClose(win.pointer))
	{
		glfwPollEvents();
	}

	//clean up
	device.clean();
	surface.clean(instance.pInstance);
	instance.clean();
	win.clean();

	return 0;
}