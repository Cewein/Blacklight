#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace blacklight::validation
{	
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	bool checkValidationLayerSupport(const std::vector<const char*> validationLayers);
}