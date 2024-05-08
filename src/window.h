#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace blacklight
{
	struct window
	{
		//variable
		int width;
		int heigh;

		GLFWwindow* pointer;

		//creation
		window(int width, int heigh, const char * title = "Blackligth renderer");
		
		//clean up
		void clean();
	};
}