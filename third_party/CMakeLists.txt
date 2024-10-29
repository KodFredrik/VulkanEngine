add_subdirectory(vk-bootstrap)
add_subdirectory(VulkanMemoryAllocator)
add_subdirectory(SDL)
add_subdirectory(glm)
add_subdirectory(fmt)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb_image)