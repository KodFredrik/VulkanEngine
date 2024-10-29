cmake_minimum_required(VERSION 3.8)
project(Vulkanen)
find_package(Vulkan REQUIRED)

add_executable(${CMAKE_PROJECT_NAME})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_subdirectory(third_party)
add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME} 
PUBLIC
    SDL3::SDL3
    vk-bootstrap::vk-bootstrap
    GPUOpen::VulkanMemoryAllocator
    glm::glm
    fmt::fmt
    stb_image
)
