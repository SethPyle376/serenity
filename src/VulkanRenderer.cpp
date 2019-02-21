#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer() {
    this->init();
}

VulkanRenderer::~VulkanRenderer() {
    if (enableValidationLayers) {
        vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);
    SDL_DestroyWindow(window);
}

bool VulkanRenderer::init() {
    initWindow();
    volkInitialize();
    initInstance();
    volkLoadInstance(instance);
    initDebugMessenger();
    initSurface();
    pickPhysicalDevice();
    initLogicalDevice();
    return true;
}

bool VulkanRenderer::checkValidationLayerSupport() {
    std::cout << "ENGINE: VERIFYING VALIDATION LAYER SUPPORT" << std::endl;
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
    std::cout << "ENGINE: VALIDATION LAYER SUPPORT VERIFIED" << std::endl;
    return true;
}

bool VulkanRenderer::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }
    
    return requiredExtensions.empty();
}

bool VulkanRenderer::isDeviceSuitable(VkPhysicalDevice device) {
        std::cout << "ENGINE: CHECKING IF DEVICE IS SUITABLE" << std::endl;
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        QueueFamilyIndices indices = findQueueFamilies(device);

        std::cout << "ENGINE: " << deviceProperties.deviceName << std::endl;

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && 
            deviceFeatures.geometryShader && indices.isComplete() && checkDeviceExtensionSupport(device);
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

    std::cout << "ENGINE: REQUIRED EXTENSIONS: " << std::endl;

    for (const char* extension : extensions) {
        std::cout << "ENGINE: EXTENSION: " << extension << std::endl;
    }

    return extensions;
}

QueueFamilyIndices VulkanRenderer::findQueueFamilies(VkPhysicalDevice hDevice) {
    std::cout << "ENGINE: FINDING QUEUE FAMILIES" << std::endl;
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(hDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(hDevice, &queueFamilyCount, queueFamilies.data());

    VkBool32 presentSupport = false;
    int i = 0;
    for (const auto& queueFamily: queueFamilies) {
        vkGetPhysicalDeviceSurfaceSupportKHR(hDevice, i, surface, &presentSupport);
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (queueFamily.queueCount > 0 && presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }
        i++;
    }
    if (indices.isComplete()) {
        std::cout << "ENGINE: QUEUE FAMILIES FOUND" << std::endl;
    }
    return indices;
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

void VulkanRenderer::pickPhysicalDevice()
{
    std::cout << "ENGINE: PICKING PHYSICAL DEVICE" << std::endl;
    //TODO: Consider scoring system to get best gpu.
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("ERROR: FAILED TO FIND GPUS WITH VULKAN SUPPORT");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("ERROR: FAILED TO FIND SUITABLE GPU");
    } else {
        std::cout << "ENGINE: PHYSICAL DEVICE SELECTED" << std::endl;
    }
}

void VulkanRenderer::initLogicalDevice() {
    std::cout << "ENGINE: INITIALIZING VULKAN LOGICAL DEVICE" << std::endl;

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pEnabledFeatures = &deviceFeatures;

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("ERROR: COULD NOT INITIALIZE VULKAN LOGICAL DEVICE");
    } else {
        std::cout << "ENGINE: INITIALIZED VULKAN LOGICAL DEVICE" << std::endl;
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void VulkanRenderer::initSurface() {
    std::cout << "ENGINE: CREATING VULKAN SURFACE" << std::endl;
    if (SDL_Vulkan_CreateSurface(window, instance, &surface) != SDL_TRUE) {
        throw std::runtime_error("ERROR: COULD NOT INITIALIZE VULKAN SURFACE");
    } else {
        std::cout << "ENGINE: VULKAN SURFACE INITIALIZED" << std::endl;
    }
}