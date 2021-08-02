#ifndef BASE_H
#define BASE_H

#include <vector>
#include "Window/window.h"

// below macro is just for internal toggles -> 0 Being "OFF"
#define INTERNAL_DEBUG  1
#define VULKAN_API_USED VK_API_VERSION_1_2
#define GLFW_API_USED   340

#if INTERNAL_DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

class BaseApplication
{
      public:
	const int windowWidth {480}, windowLength {640};
	std::string windowTitle {"Base Application"};

      private:
	VkInstance instance = VK_NULL_HANDLE;
	std::vector<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger;

      public:
	BaseApplication( );
	~BaseApplication( );
	void Run( );
	void CreateInstance( );
	std::vector<VkExtensionProperties> QueryAvailableVulkanExtensions( );
	// Would Like To Abstract Away If I Decide To Not Use GLFW In The Future
	std::vector<const char*> QueryRequiredExtensions( );
	void AddValidationLayer(const char* layerName);
	bool CheckValidationLayerSupport( );

	void DebugMessengerInit( );
	void DebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
						  VkDebugUtilsMessengerEXT debugMessenger,
						  const VkAllocationCallbacks* pAllocator);

	// Temporary/Basic Debugging Functions
	void PrintAvailableVulkanExtensions(std::vector<VkExtensionProperties> supportedExtensionsList);
	void PrintValidationLayerCheck( );
	void PrintRequiredGLFWExtensions( );
	std::string GetVulkanVersionStr( );
	std::string GetGLFWVersionStr( );

      private:
	Window windowContext {windowWidth, windowLength, windowTitle};
	void ApplicationLoop( );
	void VulkanInit( );
	void VulkanFree( );
};
// Proxy Function Used To Look Up The Address of vkCreateDebugUtilsMessengerEXT extension function and
// create that object or returns with a failure code
static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
					     const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
					     const VkAllocationCallbacks* pAllocator,
					     VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = ( PFN_vkCreateDebugUtilsMessengerEXT ) vkGetInstanceProcAddr(instance,
										 "vkCreateDebugUtilsMessen"
										 "gerEXT");
	if(func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

#endif // !BASE.H
