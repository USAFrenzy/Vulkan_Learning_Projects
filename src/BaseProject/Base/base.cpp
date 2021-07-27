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
        std::cout << "This is From The Vulkan Init Funtion\n";
    }

    void BaseApplication::vulkanFree()
    {
        std::cout << "This Is From The Vulkan Free Function\n";
    }

