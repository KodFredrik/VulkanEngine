cmake_minimum_required(VERSION 3.8)
project(Vulkanen)
find_package(Vulkan REQUIRED)
add_executable(${CMAKE_PROJECT_NAME})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
add_subdirectory(third_party)
target_link_libraries(${CMAKE_PROJECT_NAME} 
PRIVATE
vk-bootstrap::vk-bootstrap
GPUOpen::VulkanMemoryAllocator
SDL3::SDL3
)
add_subdirectory(src)