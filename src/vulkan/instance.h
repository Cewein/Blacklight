#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{
	struct instance
	{
		VkInstance pInstance;

		void create();
		void clean();
	};
}