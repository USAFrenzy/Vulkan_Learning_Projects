#include "base.h"

#include <iostream>

// All manual print messages are just temporary "debug" type at the moment (still working on a homebrew logger in a
// separate project) below macro is just for internal toggles -> 0 Being "OFF"
#define INTERNAL_DEBUG  1
#define VULKAN_API_USED VK_API_VERSION_1_2

#define GLFW_API_USED 340


#if INTERNAL_DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif


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
	//DebugMessengerInit( );
	std::cout << "Vulkan Instance Created\n";
}

void BaseApplication::VulkanFree( )
{
	std::cout << "This Is From The Vulkan Free Function\n";
	if(enableValidationLayers) {
		// Third Parameter would be the custom allocator callback
		//DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}
	// Second Parameter would be the custom allocator callback
	vkDestroyInstance(instance, nullptr);
	std::cout << "Vulkan Instance Destroyed\n";
}

void BaseApplication::CreateInstance( )
{
#if INTERNAL_DEBUG
	std::cout << "Vulkan Version: " << GetVulkanVersionStr( ) + '\n';
	std::cout << "GLFW Version: " << GetGLFWVersionStr( ) + '\n';
	PrintAvailableVulkanExtensions(QueryAvailableVulkanExtensions( ));
	if(enableValidationLayers && !CheckValidationLayerSupport( )) {
		throw std::runtime_error("ERROR: Validation Layers Were Requested But Are Not Available");
	}
	PrintValidationLayerCheck( );
#endif
	// Populating The App info and instance info structs (first struct is technically optional, second is
	// required)
	VkApplicationInfo appInfo { };
	appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName   = "Base Application Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName        = "No Engine";
	appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion         = VULKAN_API_USED;
	appInfo.pNext              = nullptr; // pointer to an extension structure
	VkInstanceCreateInfo appCreateInfo { };
	appCreateInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	appCreateInfo.pApplicationInfo = &appInfo;
	// In The Future, could abstract away this explicit functionality with GLFW if wanting a different way
	// other than GLFW of interfacing with vulkan (The Whole Current Implementation of
	// QueryRequiredExtensions() And PrintRequiredGLFWExtensions() that is)
	auto extensions                       = QueryRequiredExtensions( );
	appCreateInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size( ));
	appCreateInfo.ppEnabledExtensionNames = extensions.data( );
	// When More Layers Are Added - ABSOLUTELY NEED to ensure proper ordering (only one layer at the moment)
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = { };
	if(enableValidationLayers) {
		appCreateInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size( ));
		appCreateInfo.ppEnabledLayerNames = validationLayers.data( );
		//DebugMessengerCreateInfo(debugCreateInfo);
		appCreateInfo.pNext = ( VkDebugUtilsMessengerCreateInfoEXT* ) &debugCreateInfo;
	} else {
		appCreateInfo.enabledLayerCount = 0;
		appCreateInfo.pNext = nullptr;
	}
	// second parameter is for a pointer to custom allocator callback
	if(vkCreateInstance(&appCreateInfo, nullptr, &instance) != VK_SUCCESS) {
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

void BaseApplication::AddValidationLayer(const char* layerName)
{
	validationLayers.emplace_back(layerName);
}

bool BaseApplication::CheckValidationLayerSupport( )
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data( ));
	for(const char* layerName : validationLayers) {
		bool layerFound = false;
		for(const auto& layerProperties : availableLayers) {
			if(strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if(!layerFound) {
			return false;
		}
	}
	return true;
}

void BaseApplication::PrintValidationLayerCheck( )
{
	std::cout << "Available Validation Layers\n";
	for(auto& layer : validationLayers) {
		if(CheckValidationLayerSupport( )) {
			std::cout << '\t' << "Supported Validation Layer: " << layer << '\n';
		} else {
			std::cout << '\t' << "Unsupported Validation Layer: " << layer << '\n';
		}
	}
}

std::vector<const char*> BaseApplication::QueryRequiredExtensions( )
{
	uint32_t glfwExtensionCount(0), i(0);
	const char** glfwExtensionNames;
	glfwExtensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char*> extensions {glfwExtensionNames, glfwExtensionNames + glfwExtensionCount};
	if(enableValidationLayers) {
		extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	return extensions;
}

void BaseApplication::PrintRequiredGLFWExtensions( )
{
	auto extensionList = QueryRequiredExtensions( );
	std::cout << "Required Extensions For GLFW And Vulkan:\n";
	for(auto extension : extensionList) {
		std::cout << '\t' << extension << '\n';
	}
}

std::string BaseApplication::GetVulkanVersionStr( )
{
	uint32_t instanceVersion = VULKAN_API_USED;
	std::string major, minor, patch;
	auto FN_vkEnumerateInstanceVersion =
	  PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
	if(vkEnumerateInstanceVersion) {
		vkEnumerateInstanceVersion(&instanceVersion);
	}
	major = std::to_string(VK_API_VERSION_MAJOR(instanceVersion));
	minor = std::to_string(VK_API_VERSION_MINOR(instanceVersion));
	patch = std::to_string(VK_API_VERSION_PATCH(instanceVersion));

	return major + "." + minor + "." + patch;
}

std::string BaseApplication::GetGLFWVersionStr( )
{
	return std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." +
	       std::to_string(GLFW_VERSION_REVISION);
}

//static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
//						    VkDebugUtilsMessageTypeFlagsEXT messageType,
//						    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
//						    void* pUserData)
//{
//	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
//	return VK_FALSE;
//}
//
//void BaseApplication::DebugMessengerInit( )
//{
//	if(!enableValidationLayers) {
//		return;
//	}
//	VkDebugUtilsMessengerCreateInfoEXT createInfo;
//	DebugMessengerCreateInfo(createInfo);
//	if(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
//		throw std::runtime_error("Unable To Setup The Debug Messenger");
//	}
//}
//
//// Proxy Function Used To Look Up The Address of vkCreateDebugUtilsMessengerEXT extension function and create that
//// object or returns with a failure code
//static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
//						       const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
//						       const VkAllocationCallbacks* pAllocator,
//						       VkDebugUtilsMessengerEXT* pDebugMessenger)
//{
//	auto func =
//	  ( PFN_vkCreateDebugUtilsMessengerEXT ) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//	if(func != nullptr) {
//		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//	} else {
//		return VK_ERROR_EXTENSION_NOT_PRESENT;
//	}
//}
//
//void BaseApplication::DestroyDebugUtilsMessengerEXT(VkInstance instance,
//						    VkDebugUtilsMessengerEXT debugMessenger,
//						    const VkAllocationCallbacks* pAllocator)
//{
//	PFN_vkDestroyDebugUtilsMessengerEXT func =
//	  ( PFN_vkDestroyDebugUtilsMessengerEXT ) vkGetInstanceProcAddr(instance,
//									"vkDestroyDebugUtilsMessengerEXT");
//	if(func != nullptr) {
//		func(instance, debugMessenger, pAllocator);
//	}
//}
//
//void BaseApplication::DebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
//{
//	createInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
//	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//				     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
//				     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
//	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
//				 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
//				 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
//	createInfo.pfnUserCallback = debugCallback;
//	createInfo.pUserData       = nullptr; // this would be used as a hook to another struct via a ptr
//}