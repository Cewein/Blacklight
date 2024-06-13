#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace blacklight::validation
{
    // Array of validation layers to enable
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    /**
     * @brief Checks if the specified validation layers are supported by the Vulkan instance.
     *
     * @param validationLayers: The vector containing validation layer names to check for support.
     * @return true if all validation layers are supported, false otherwise.
     */
    bool checkValidationLayerSupport(const std::vector<const char*> validLayers);
}