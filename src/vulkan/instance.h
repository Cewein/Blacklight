#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
	struct instance
	{
		VkInstance pointer = VK_NULL_HANDLE;

		void create();
		void clean();
	};
}