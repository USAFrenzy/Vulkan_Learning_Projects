#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>
#include "Window/window.h"
#include <optional>

// below macro is just for internal toggles -> 0 Being "OFF"
#define INTERNAL_DEBUG             1
#define PRINT_INTERNAL_DB_MESSAGES 1

// Just A  Couple Of Versioning Macros
#define VERSION_STRING_FORMAT(major, minor, revision) #major "." #minor "." #revision
#define VERSION_NUMBER(maj, min, rev)                 VERSION_STRING_FORMAT(maj, min, rev)
#define VULKAN_API_USED                               VK_API_VERSION_1_2
#define GLFW_API_USED                                 340

#if INTERNAL_DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	bool isComplete( )
	{
		return graphicsFamily.has_value( );
	}
};

class BaseApplication
{
      public:
	BaseApplication(const int windowWidth, const int windowLength, const char* wind);
	~BaseApplication( );
	void Run( );
	void CreateInstance( );
	std::vector<VkExtensionProperties> QueryAvailableVulkanExtensions( );
	// Would Like To Abstract Away If I Decide To Not Use GLFW In The Future
	std::vector<const char*> QueryRequiredExtensions( );
	void AddValidationLayer(const char* layerName);
	bool const CheckValidationLayerSupport( );

	void DebugMessengerInit( );
	void DebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
						  VkDebugUtilsMessengerEXT debugMessenger,
						  const VkAllocationCallbacks* pAllocator);
	void QueryPhysicalDevices( );
	int WeighDeviceSuitability(VkPhysicalDevice device);
	QueueFamilyIndices QueryForQueueFamilies(VkPhysicalDevice device);
	void CreateLogicalDevice( );


	// Temporary/Basic Debugging Functions
	void const PrintAvailableVulkanExtensions(std::vector<VkExtensionProperties> supportedExtensionsList);
	void const PrintValidationLayerCheck( );
	void const PrintRequiredGLFWExtensions( );
	void PrintVulkanVersion( );
	void PrintGLFWVersion( );

      private:
	const int windowWidth   = 480;
	const int windowHeight  = 640;
	const char* windowTitle = "Base Application";
	VkInstance instance     = VK_NULL_HANDLE;
	std::vector<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice         = VK_NULL_HANDLE;
	VkDevice logicalDevice                  = VK_NULL_HANDLE;
	VkQueue graphicsQueue                   = VK_NULL_HANDLE;

      private:
	void ApplicationLoop( );
	void VulkanInit( );
	void VulkanFree( );
	Window windowContext {windowWidth, windowHeight, windowTitle};
};
/*
	Proxy Function Used To Look Up The Address of vkCreateDebugUtilsMessengerEXT extension function and
	create that object or returns with a failure code
*/
// disabling the unscoped enum warning as it's not this code base causing it but Vulkan
#pragma warning(push)
#pragma warning(disable : 26812)
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
#pragma warning(pop)


#if PRINT_INTERNAL_DB_MESSAGES
/*
	This was supposed to be a starter to a stop-gap to logging by wrapping printf() in a define without
	affecting solo printf()'s but unfortunately, the way it is now, it can't print the version strings when
	formatted. Variadic templates are a new thing to me so I might be using them wrong when implementing them
	and it could even be that function scope in the Get...Str() functions is actually my issue here
*/
template <typename... Args> void dbPrint(const char* message, Args... args)
{
	printf(message, args...);
}
#endif // PRINT_INTERNAL_DB_MESSAGES

#endif // !BASE.H
