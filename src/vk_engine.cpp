#include "vk_engine.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <VkBootstrap.h>

//#include <vk_initializers.h>
#include "vk_types.h"

#include <chrono>
#include <thread>
#include <cassert>
#include <iostream>

//FASTGLTF SAKNAR parser.hpp, kolla när aktuellt
#include <fastgltf/glm_element_traits.hpp>

//Decide if validation layers should be used.
constexpr bool bUseValidationLayers = false;

//Initialize pointer to the engine instance. For the VulkanEngine::Get() function.
VulkanEngine* loadedEngine = nullptr;

//Getter function that returns a reference so the loaded instance.
VulkanEngine& VulkanEngine::Get() 
{
    return *loadedEngine;
}

void VulkanEngine::init()
{
    //An assert statement is a "hard if", if the loaded engine is not null, crash. 
    //Make sure no engine is loaded, then assign the this pointer. 
    //Note "this" is only accessible to nonstatic member functions.
    assert(loadedEngine == nullptr);
    loadedEngine = this;

    // We initialize SDL and create a window with it.
    SDL_Init(SDL_INIT_VIDEO);
    //set flags for what we want to use in SDL. These include windowing and mouse and keyboard input. 
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

    m_window_ptr = SDL_CreateWindow(
        "Vulkan Engine",
        m_windowExtent.width,
        m_windowExtent.height,
        window_flags);

    init_vulkan();
	init_swapchain();
	init_commands();
	init_sync_structures();

    // everything went fine
    m_isInitialized = true;
}

void VulkanEngine::cleanup()
{
    //Check if engine is initialized, then destroy window.
    if(m_isInitialized)
    {
        SDL_DestroyWindow(m_window_ptr);
    }
    //Null instance pointer!
    loadedEngine = nullptr;
}

void VulkanEngine::run()
{
    SDL_Event event;
    bool Quit = false;
    
    // main loop
    while (!Quit) 
    {
        // Handle events on queue
        while (SDL_PollEvent(&event) != 0) 
        {
            //Quit loop when user clicks X on window or alt+f4. Stop rendering if window is not in focus on screen.
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    Quit = true;
                    break;
                case SDL_EVENT_WINDOW_FOCUS_LOST:
                    stop_rendering = true;
                    break;
                case SDL_EVENT_WINDOW_FOCUS_GAINED:
                    stop_rendering = false;
                    break;
            }
        }
            // do not draw if we are out of focus
            switch (stop_rendering)
            {
                case true:
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    break;
                case false:
                    draw();
                    break;
            }
    }
}

void VulkanEngine::draw()
{

}

void VulkanEngine::init_vulkan()
{
    // ~~~~~~~~~~Initialize VkInstance~~~~~~~~~~~~~~
    //Use vk-bootstrap to initialize the VkInstance.
    vkb::InstanceBuilder builder;

    //make the vulkan instance, with basic debug features
	auto inst_ret = builder.set_app_name("Vulkanutbrott")
		.request_validation_layers(bUseValidationLayers)
		.use_default_debug_messenger()
		.require_api_version(1, 3, 0)
		.build();

	vkb::Instance vkb_inst = inst_ret.value();

	//Set the member variables VkInstance and VkDebugUtilsMessengerEXT
	m_instance = vkb_inst.instance;
	m_debug_messenger = vkb_inst.debug_messenger;

    //~~~~~~~~~~~Initialize VkDevice, choose VkPhysicalDevice (GPU) and create abstract surface VkSurfaceKHR.
    SDL_Vulkan_CreateSurface(m_window_ptr, m_instance, NULL, &m_surface); //The NULL argument is a VKAllocatorCallback struct, unclear what part it plays. 

    //vulkan 1.3 features, Dynamic rendering and synchronization2
	VkPhysicalDeviceVulkan13Features features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
	features.dynamicRendering = true;
	features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
	features12.bufferDeviceAddress = true; //Lets us use GPU pointers without binding buffers
	features12.descriptorIndexing = true; //Gives us bindless textures

    //use vkbootstrap to select a gpu. 
	//We want a gpu that can write to the SDL surface and supports vulkan 1.3 with the correct features (Selected above. Dynamic rendering etc.)
	vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 3)
		.set_required_features_13(features)
		.set_required_features_12(features12)
		.set_surface(m_surface)
		.select()
		.value();

	//create the final vulkan device
	vkb::DeviceBuilder deviceBuilder{ physicalDevice };
	vkb::Device vkbDevice = deviceBuilder.build().value();

	// Get the VkDevice handle used in the rest of a vulkan application
	m_device = vkbDevice.device;
	m_physicalGPU = physicalDevice.physical_device;
}
void VulkanEngine::init_swapchain()
{

}
void VulkanEngine::init_commands()
{

}
void VulkanEngine::init_sync_structures()
{

}