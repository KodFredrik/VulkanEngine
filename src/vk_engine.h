#pragma once

#include "vk_types.h"

class VulkanEngine {
public:

	bool m_isInitialized{ false }; //Flag to know if engine is initialized.
	int m_frameNumber {0}; //Frame number, can render one frame and work on another for instance.
	bool stop_rendering{ false }; //Boolean to stop rendering when window minimized for example.
	VkExtent2D m_windowExtent{ 1700 , 900 }; //Window size

	struct SDL_Window* m_window_ptr{ nullptr }; //Forward declare to have pointer to window without including SDL in the engine header.

	static VulkanEngine& Get(); //Get() function as global singleton pattern. Returns reference to the engine instance.

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();
};