#pragma once

#include <vulkan/vulkan.h>

namespace blacklight
{

    // @brief Prints the supported Vulkan extensions to the console.
    // 
    // This function queries the Vulkan API to get the list of supported extensions
    // and prints their names to the console. It is useful for debugging and ensuring
    // that the necessary extensions are available on the system.
    void supportedExtensions();
}
