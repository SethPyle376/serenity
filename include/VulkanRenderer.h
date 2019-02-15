#include <iostream>
#include <vector>

#include "Renderer.h"

#include "SDL.h"
#include "SDL_vulkan.h"
#include "volk.h"

class VulkanRenderer : public Renderer {
private:
    SDL_Window *window;

    VkInstance instance;

    bool init();
    void initWindow();
    void initVolk();
    void initInstance();
public:
    VulkanRenderer();
};