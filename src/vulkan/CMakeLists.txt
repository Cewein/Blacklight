set(
    BLACKLIGHT_VULKAN_SOURCE
    ${CMAKE_SOURCE_DIR}/src/vulkan/device.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/device.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/extension.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/extension.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/instance.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/instance.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/validation.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/validation.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/queue.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/queue.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/surface.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/surface.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/swapchain.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/swapchain.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/image.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/image.cpp
    ${CMAKE_SOURCE_DIR}/src/vulkan/shader.h
    ${CMAKE_SOURCE_DIR}/src/vulkan/shader.cpp
    PARENT_SCOPE
)