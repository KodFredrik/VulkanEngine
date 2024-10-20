cmake_minimum_required(VERSION 3.8)
project("Vulkanen")
find_package(Vulkan REQUIRED)
add_subdirectory(src)
add_subdirectory(third_party)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

target_link_libraries(engine PRIVATE vk-bootstrap::vk-bootstrap)
