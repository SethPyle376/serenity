#include "Engine/Renderer/VulkanRenderer.h"
#undef main

int main()
{
	VulkanRenderer *renderer = new VulkanRenderer();
	delete renderer;
	return 0;
}