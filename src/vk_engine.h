#pragma once

#include "vk_types.h"

class VulkanEngine {

public:
	bool m_isInitialized{ false }; //Flag to know if engine is initialized.
	int m_frameNumber {0}; //Frame number, can render one frame and work on another for instance.
	bool stop_rendering{ false }; //Boolean to stop rendering when window minimized for example

	VkExtent2D m_windowExtent{ 1700 , 900 }; //Window size
	struct SDL_Window* m_window_ptr{ nullptr }; //Forward declare to have pointer to window without including SDL in the engine header.

	//These variables are required to initialize Vulkan
	VkInstance m_instance; //All information of the vulkan state is stored in the instance. Initializes the Vulkan library.
	VkSurfaceKHR m_surface;//VkSurfaceKHR is an abstract window that we can present images to, to be delivered to the windowing system. Should be created right after the instance.
	VkDebugUtilsMessengerEXT m_debug_messenger;// Vulkan debug output handle
	VkPhysicalDevice m_physicalGPU; //A reference to the GPU and information of it is stored in this handle. Properties such as VRAM can be queried from it.
	VkDevice m_device; //The VkDevice is the driver of the VkPhysicalDevice that we use to communicate with the GPU.
	
	static VulkanEngine& Get(); //Get() function as global singleton pattern. Returns reference to the engine instance.
	void init();	//initializes everything in the engine
	void cleanup();	//shuts down the engine
	void draw();	//draw loop
	void run();	//run main loop

	private:
	//These functions will be contained in the main init() function, and will initialize the parts.
	void init_vulkan();
	void init_swapchain();
	void init_commands();
	void init_sync_structures();


};