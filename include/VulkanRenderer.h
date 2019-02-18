#include <iostream>
#include <vector>
#include <optional>

#include "Renderer.h"

#include "SDL.h"
#include "SDL_vulkan.h"
#include "volk.h"

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    
    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class VulkanRenderer : public Renderer {
private:
    SDL_Window *window;

    VkInstance instance;
    VkPhysicalDevice physicalDevice;

    VkDebugUtilsMessengerEXT debugMessenger;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    bool init();
    void initWindow();
    void initVolk();
    void initInstance();
    void initDebugMessenger();
    void pickPhysicalDevice();

    bool checkValidationLayerSupport();
    std::vector<const char *> getRequiredExtensions();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {
            std::cerr << "VALIDATION LAYER: " << pCallbackData->pMessage << std::endl;
            return VK_FALSE;
    };

public:
    VulkanRenderer();
    ~VulkanRenderer();
};