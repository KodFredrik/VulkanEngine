#include "vk_engine.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

//#include <vk_initializers.h>
#include "vk_types.h"

#include <chrono>
#include <thread>
#include <cassert>
#include <iostream>

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
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);

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
    SDL_Event e;
    bool bQuit = false;
    
    //SDL_Event testevent;
    //testevent.type = SDL_EVENT_WINDOW_MINIMIZED;

    // main loop
    while (!bQuit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) 
        {
            //std::cout << e.type << std::endl;
            printf("%d\n", e.type);
            // close the window when user alt-f4s or clicks the X button
            if (e.type == SDL_EVENT_QUIT)
            {
                printf("quit");
                bQuit = true;
            }
            if (e.window.type == SDL_EVENT_WINDOW_MINIMIZED) 
            {
                printf("minimized");
                stop_rendering = true;
            }
            if (e.window.type == SDL_EVENT_WINDOW_RESTORED) 
            {
                printf("restored");
                stop_rendering = false;
            }
            //SDL_PushEvent(&testevent);
        }
        // do not draw if we are minimized
        if (stop_rendering) 
        {
            // throttle the speed to avoid the endless spinning
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        else
        {
            draw();
        }
    }
}

void VulkanEngine::draw()
{

}