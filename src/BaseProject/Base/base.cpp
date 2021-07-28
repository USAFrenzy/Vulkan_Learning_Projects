#include "base.h"
#include <iostream>

    BaseApplication::BaseApplication() 
    {
        std::cout << "Base Application Object Created\n";

    }

    BaseApplication::~BaseApplication()
    {
        std::cout << "Base Application Object Destroyed\n";
    }

    void BaseApplication::Run()
    {
        vulkanInit();
        applicationLoop();
        vulkanFree();
        // NOTE: Temporary Code To Allow Window Closing Until Custom Event Handler Is Implemented
	    std::cout << "Polling Window Events\n";
        while(!windowContext.Close()) 
        {
		    glfwPollEvents( );
        }
    }  

    void BaseApplication::applicationLoop() 
    {
        std::cout << "This Is From The Application Loop Function\n";
    }

    void BaseApplication::vulkanInit()
    {
	    createInstance( );
        std::cout << "This is From The Vulkan Init Funtion\n";
    }

    void BaseApplication::vulkanFree()
    {
        std::cout << "This Is From The Vulkan Free Function\n";
    }

    void BaseApplication::createInstance( )
    {
	    VkApplicationInfo appInfo { };
	        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	        appInfo.pApplicationName   = "Base Application Triangle";
	        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	        appInfo.pEngineName        = "No Engine";
	        appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
	        appInfo.apiVersion         = VK_API_VERSION_1_0;
	        appInfo.pNext              = nullptr; // technically don't need to be explicit here due to appInfo = {} initialization 
        VkInstanceCreateInfo appCreateInfo { };
	        appCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            // Would Like To Know If This Is Being Passed By Reference For 
            // Less Copying Or If The Struct Is Passed Via A Pointer.
            // Tutorial Doesn't say
	        appCreateInfo.pApplicationInfo = &appInfo; 
        uint32_t glfwExtensionCount = 0;
	    const char** glfwExtensionNames; 
            glfwExtensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	            appCreateInfo.enabledExtensionCount = glfwExtensionCount;
	            appCreateInfo.ppEnabledExtensionNames = glfwExtensionNames;
		        appCreateInfo.enabledLayerCount       = 0; // Later On - Used For Global Validation
        if(vkCreateInstance(&appCreateInfo, nullptr, &instance) != VK_SUCCESS) 
        {
		    throw std::runtime_error("Unable To Create Vulkan Instance");
        }
    }