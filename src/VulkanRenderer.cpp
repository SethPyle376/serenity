#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer() {
    this->init();
}

VulkanRenderer::~VulkanRenderer() {
    // if (enableValidationLayers) {
    //     vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    // }
    vkDestroyInstance(instance, nullptr);
    SDL_DestroyWindow(window);
}

bool VulkanRenderer::checkValidationLayerSupport() {
    std::cout << "VERIFYING VALIDATION LAYER SUPPORT" << std::endl;
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound)
            return false;
    }
    std::cout << "VALIDATION LAYER SUPPORT VERIFIED" << std::endl;
    return true;
}

std::vector<const char*> VulkanRenderer::getRequiredExtensions() {
    uint32_t count;
    bool success = SDL_Vulkan_GetInstanceExtensions(window, &count, NULL);
    std::vector<const char*> extensions = std::vector<const char*>();
    extensions.resize(count);
    SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data());

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    std::cout << "REQUIRED EXTENSIONS: " << std::endl;

    for (const char* extension : extensions) {
        std::cout << "EXTENSION: " << extension << std::endl;
    }

    return extensions;
}

void VulkanRenderer::initDebugMessenger() {
    if (!enableValidationLayers)
        return;
    
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr;
    if (vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("ERROR: FAILED TO INITIALIZE DEBUG MESSENGER");
    }
}

bool VulkanRenderer::init() {
    initWindow();
    initVolk();
    initDebugMessenger();
    return true;
}

void VulkanRenderer::initWindow() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Serenity",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN
	);
}

void VulkanRenderer::initInstance() {
    std::cout << "INITIALIZING VULKAN INSTANCE" << std::endl;

    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("ERROR: VALIDATION LAYER NOT AVAILABLE");
    }

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Serenity";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Serenity";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> requiredExtensions = getRequiredExtensions();

    createInfo.enabledExtensionCount = requiredExtensions.size();
    //TODO: Check if extensions are supported
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("ERROR: FAILED TO CREATE VULKAN INSTANCE");
    }
    std::cout << "VULKAN INSTANCE INITIALIZED" << std::endl;
}

void VulkanRenderer::initVolk() {
    volkInitialize();
    initInstance();
    volkLoadInstance(instance);
}