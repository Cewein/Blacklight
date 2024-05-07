# CMakeList.txt : CMake project for Ectoplasme, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)
project(Blacklight VERSION 0.1.0 LANGUAGES CXX C)

include(FetchContent)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project ("Blacklight")

# Set source files for the executable.
add_executable(Blacklight "main.cpp")

set_target_properties(Blacklight PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  COMPILE_WARNING_AS_ERROR OFF
)

# Compiler-specific options
if(MSVC)
  target_compile_options(Blacklight PRIVATE /W4)
else()
  target_compile_options(Blacklight PRIVATE -Wall -Wextra -pedantic)
endif()

#include vulkan in the project
message(STATUS "Using module to find Vulkan")

# Find Vulkan Path using CMake's Vulkan Module
# It is mandatory since we need both the headers and SDK
# Reference to the instalation guide if needed
find_package(Vulkan REQUIRED)

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

find_package(OpenUSD REQUIRED HINTS ${USD_PATH} NAMES pxr)
if (OpenUSD_FOUND)
    message(STATUS "Find OpenUSD version: ${PXR_VERSION} at ${PXR_INCLUDE_DIRS}")
	target_include_directories(Blacklight PUBLIC ${PXR_INCLUDE_DIRS})
endif()

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  GIT_TAG master
) 
FetchContent_MakeAvailable(glfw)

# Include Vulkan as a targeted lib
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)