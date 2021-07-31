#include "base.h"

#include <iostream>

// All manual print messages are just temporary "debug" type at the moment (still working on a homebrew logger in a
// separate project) below macro is just for internal toggles -> 0 Being "OFF"
#define INTERNAL_DEBUG 1;

BaseApplication::BaseApplication( )
{
	std::cout << "Base Application Object Created\n";
}

BaseApplication::~BaseApplication( )
{
	std::cout << "Base Application Object Destroyed\n";
}

void BaseApplication::Run( )
{
	VulkanInit( );
	ApplicationLoop( );
	VulkanFree( );
}

void BaseApplication::ApplicationLoop( )
{
	std::cout << "This Is From The Application Loop Function\n";
	std::cout << "Polling Window Events\n";
	// NOTE: Temporary Code To Allow Window Closing Until Custom Event Handler Is Implemented
	while(!windowContext.Close( )) {
		glfwPollEvents( );
	}
	std::cout << "Window Closing\n";
}

void BaseApplication::VulkanInit( )
{
	std::cout << "This is From The Vulkan Init Funtion\n";
	CreateInstance( );
	std::cout << "Vulkan Instance Created\n";
}

void BaseApplication::VulkanFree( )
{
	std::cout << "This Is From The Vulkan Free Function\n";
	// Second Parameter would be the custom allocator callback
	vkDestroyInstance(instance, nullptr);
	std::cout << "Vulkan Instance Destroyed\n";
}

void BaseApplication::CreateInstance( )
{
#if INTERNAL_DEBUG 
	PrintAvailableVulkanExtensions(QueryAvailableVulkanExtensions( ));
#endif
	// Populating The App info and instance info structs (first struct is technically optional, second is
	// required)
	VkApplicationInfo appInfo { };
	appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName   = "Base Application Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName        = "No Engine";
	appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion         = VK_API_VERSION_1_0;
	appInfo.pNext              = nullptr; // pointer to an extension structure
	VkInstanceCreateInfo appCreateInfo { };
	appCreateInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	appCreateInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount(0), i(0);
	const char** glfwExtensionNames;
	glfwExtensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
#if INTERNAL_DEBUG 
	std::cout << "GLFW Extensions Supported By Vulkan:\n";
	for(i; i < glfwExtensionCount; ++i) {
		std::cout << '\t' << glfwExtensionNames [i] << "\n";
	}
#endif
	appCreateInfo.enabledExtensionCount   = glfwExtensionCount;
	appCreateInfo.ppEnabledExtensionNames = glfwExtensionNames;
	appCreateInfo.enabledLayerCount       = 0; // Later On - Used For Global Validation
	if(vkCreateInstance(&appCreateInfo, nullptr, &instance) != VK_SUCCESS) // second parameter is for a pointer
									       // to custom allocator callback
	{
		throw std::runtime_error("Unable To Create Vulkan Instance");
	}
}

std::vector<VkExtensionProperties> BaseApplication::QueryAvailableVulkanExtensions( )
{
	// Finds The Available Extensions Supported(For future me - both calls to
	// vkEnumerateInstance...() are needed for the list population
	uint32_t extensionCount {0};
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); // Gets The Number Of Extensions
	std::vector<VkExtensionProperties> supportedExtensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr,
					       &extensionCount,
					       supportedExtensions.data( )); // Populates The Buffer Data
	return supportedExtensions;
}

void BaseApplication::PrintAvailableVulkanExtensions(std::vector<VkExtensionProperties> supportedExtensionsList)
{
	std::cout << "Extensions That Are Available From Vulkan:\n";
	for(auto& extension : supportedExtensionsList) {
		std::cout << '\t' << extension.extensionName << "\n";
	}
}
