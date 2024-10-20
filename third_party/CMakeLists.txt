add_library(vk-bootstrap STATIC)
add_subdirectory(vk-bootstrap/src)
target_sources(vk-bootstrap PRIVATE 
  vk-bootstrap/src/VkBootstrap.h
  vk-bootstrap/src/VkBootstrap.cpp
  )
