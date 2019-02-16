#include "SDL.h"
#include "VulkanRenderer.h"
#undef main

int main()
{
	VulkanRenderer *renderer = new VulkanRenderer();
	delete renderer;
	return 0;
}