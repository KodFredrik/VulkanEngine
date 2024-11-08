#include "vk_engine.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

//#include <vk_initializers.h>
#include "vk_types.h"

#include <chrono>
#include <thread>
#include <cassert>
#include <iostream>

//FASTGLTF SAKNAR parser.hpp, kolla när aktuellt
#include <fastgltf/glm_element_traits.hpp>

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