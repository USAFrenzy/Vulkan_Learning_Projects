#ifndef BASE_H
#define BASE_H

#include <vector>
#include "Window/window.h"

class BaseApplication
{
      public:
	const int windowWidth {480}, windowLength {640};
	std::string windowTitle {"Base Application"};

      private:
	VkInstance instance = { };
	VkDebugUtilsMessengerEXT debugMessenger;
	std::vector<const char*> validationLayers;

      public:
	BaseApplication( );
	~BaseApplication( );
	void Run( );
	void CreateInstance( );
	std::vector<VkExtensionProperties> QueryAvailableVulkanExtensions( );
	void AddValidationLayer(const char* layerName);
	bool CheckValidationLayerSupport( );

	/*void DebugMessengerInit( );
	void DebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);*/

	// Would Like To Abstract Away If I Decide To Not Use GLFW In The Future
	std::vector<const char*> QueryRequiredExtensions( );

	/*static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
						  VkDebugUtilsMessengerEXT debugMessenger,
						  const VkAllocationCallbacks* pAllocator);*/

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


#endif // !BASE.H