#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
	struct instance
	{
		VkInstance pointer;

		void create();
		void clean();
	};
}