#include "volk.h"

int main()
{
	volkInitialize();
	
	VkInstance instance;
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "volk test";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "no engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	createInfo.enabledExtensionCount = 0;
	createInfo.ppEnabledExtensionNames = NULL;
	createInfo.enabledLayerCount = 0;

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	volkLoadInstance(instance);
	int i = 0;
}