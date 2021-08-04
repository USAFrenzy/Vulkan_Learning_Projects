#include "base.h"
#include <iostream>
#include <map>

// All manual print messages are just temporary "debug" type at the moment (still working on a homebrew logger in a
// separate project)

BaseApplication::BaseApplication(const int width, const int height, const char* title)
  : windowWidth(width), windowHeight(height), windowTitle(title)
{
	dbPrint("Base Application Object Created\n");
}

BaseApplication::~BaseApplication( )
{
	dbPrint("Base Application Object Destroyed\n");
}

void BaseApplication::Run( )
{
	VulkanInit( );
	ApplicationLoop( );
	VulkanFree( );
}

void BaseApplication::ApplicationLoop( )
{
	dbPrint("This Is From The Application Loop Function\n");
	dbPrint("Polling Window Events\n");
	// NOTE: Temporary Code To Allow Window Closing Until Custom Event Handler Is Implemented
	while(!windowContext.Close( )) {
		glfwPollEvents( );
	}
	dbPrint("Window Closing\n");
}

void BaseApplication::VulkanInit( )
{
	dbPrint("This is From The Vulkan Init Funtion\n");
	CreateInstance( );
	DebugMessengerInit( );
	QueryPhysicalDevices( );
	dbPrint("Vulkan Instance Created\n");
}

void BaseApplication::VulkanFree( )
{
	dbPrint("This Is From The Vulkan Free Function\n");
	if(enableValidationLayers) {
		// Third Parameter would be the custom allocator callback
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}
	// Second Parameter would be the custom allocator callback
	vkDestroyInstance(instance, nullptr);
	dbPrint("Vulkan Instance Destroyed\n");
}

void BaseApplication::CreateInstance( )
{
#if INTERNAL_DEBUG
	#if PRINT_INTERNAL_DB_MESSAGES
	std::cout << "Vulkan Version: " << GetVulkanVersionStr( ) << "\n";
	std::cout << "GLFW Version: " << GetGLFWVersionStr( ) << "\n";
	#endif
	PrintAvailableVulkanExtensions(QueryAvailableVulkanExtensions( ));
	if(enableValidationLayers && !CheckValidationLayerSupport( )) {
		throw std::runtime_error("ERROR: Validation Layers Were Requested But Are Not Available\n");
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
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
	if(enableValidationLayers) {
		appCreateInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size( ));
		appCreateInfo.ppEnabledLayerNames = validationLayers.data( );
		DebugMessengerCreateInfo(debugCreateInfo);
		appCreateInfo.pNext = ( VkDebugUtilsMessengerCreateInfoEXT* ) &debugCreateInfo;
	} else {
		appCreateInfo.enabledLayerCount = 0;
		appCreateInfo.pNext             = nullptr;
	}
	// second parameter is for a pointer to custom allocator callback
	if(vkCreateInstance(&appCreateInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("Unable To Create Vulkan Instance\n");
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

void const
  BaseApplication::PrintAvailableVulkanExtensions(std::vector<VkExtensionProperties> supportedExtensionsList)
{
	printf("Extensions That Are Available From Vulkan: \n");
	for(auto& extension : supportedExtensionsList) {
		printf("\t %s \n", extension.extensionName);
	}
}

void BaseApplication::AddValidationLayer(const char* layerName)
{
	validationLayers.emplace_back(layerName);
}

bool const BaseApplication::CheckValidationLayerSupport( )
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

void const BaseApplication::PrintValidationLayerCheck( )
{
	printf("Available Validation Layers \n");
	for(auto& layer : validationLayers) {
		if(CheckValidationLayerSupport( )) {
			printf("\tSupported Validation Layer(s): \n\t- %s \n", layer);
		} else {
			printf("\tUnsupported Validation Layer(s): \n\t- %s \n", layer);
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

void const BaseApplication::PrintRequiredGLFWExtensions( )
{
	auto extensionList = QueryRequiredExtensions( );
	printf("Required Extensions For GLFW And Vulkan:\n");
	for(auto& extension : extensionList) {
		printf("\t %s \n", extension);
	}
}

std::string const BaseApplication::GetVulkanVersionStr( )
{
	uint32_t instanceVersion = VULKAN_API_USED;
	std::string major, minor, patch;
	auto FN_vkEnumerateInstanceVersion =
	  PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
	vkEnumerateInstanceVersion(&instanceVersion);
	major = std::to_string(VK_API_VERSION_MAJOR(instanceVersion));
	minor = std::to_string(VK_API_VERSION_MINOR(instanceVersion));
	patch = std::to_string(VK_API_VERSION_PATCH(instanceVersion));
	return (major + "." + minor + "." + patch);
}

std::string const BaseApplication::GetGLFWVersionStr( )
{
	return (std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." +
		std::to_string(GLFW_VERSION_REVISION))
	  .c_str( );
}

// disabling the unscoped enum warning as it's not this code base causing it but Vulkan
#pragma warning(push)
#pragma warning(disable : 26812)
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
						    VkDebugUtilsMessageTypeFlagsEXT messageType,
						    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
						    void* pUserData)
{
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}
#pragma warning(pop)

void BaseApplication::DebugMessengerInit( )
{
	if(!enableValidationLayers) {
		return;
	}
	// NOTE TO SELF - Either need to be explicit here with the pnext field being null or calling the default
	// initialization for the struct
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = { };
	DebugMessengerCreateInfo(debugCreateInfo);
	if(CreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("Unable To Setup The Debug Messenger\n");
	}
}


void BaseApplication::DestroyDebugUtilsMessengerEXT(VkInstance instance,
						    VkDebugUtilsMessengerEXT debugMessenger,
						    const VkAllocationCallbacks* pAllocator)
{
	PFN_vkDestroyDebugUtilsMessengerEXT func =
	  ( PFN_vkDestroyDebugUtilsMessengerEXT ) vkGetInstanceProcAddr(instance,
									"vkDestroyDebugUtilsMessengerEXT");
	if(func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

void BaseApplication::DebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo                 = { };
	createInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData       = nullptr; // this would be used as a hook to another struct via a ptr
	createInfo.flags           = 0;
}

void BaseApplication::QueryPhysicalDevices( )
{
	uint32_t deviceCount {0};
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if(deviceCount == 0) {
		throw std::runtime_error("Unable To Find A Vulkan Supported GPU\n");
	}
	std::vector<VkPhysicalDevice> deviceFamily(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, deviceFamily.data( ));

	std::multimap<int, VkPhysicalDevice> deviceWeight;
	for(const auto& device : deviceFamily) {
		int weight = WeighDeviceSuitability(device);
		deviceWeight.insert(std::make_pair(weight, device));
	}

	for(const auto& device : deviceFamily) {
		if(deviceWeight.rbegin( )->first > 0) {
			physicalDevice = device;
			break;
		}
	}
	if(physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("Unable To Find A Suitable GPU\n");
	}
}

/*
	At the moment, this is only testing for a dedicated graphics card that supports geometry shaders, but this
	function can be molded to perform whatever checks are needed for the application
*/
int BaseApplication::WeighDeviceSuitability(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int weightFactor {0};
	if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		weightFactor += 5000;
	}
	weightFactor += deviceProperties.limits.maxImageDimension2D;
	if(!deviceFeatures.geometryShader) {
		return 0;
	}

	return weightFactor;
}
