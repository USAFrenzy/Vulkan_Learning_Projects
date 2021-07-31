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

      public:
	BaseApplication( );
	~BaseApplication( );
	void Run( );
	void CreateInstance( );
	std::vector<VkExtensionProperties> QueryAvailableVulkanExtensions( );
	void PrintAvailableVulkanExtensions(std::vector<VkExtensionProperties> supportedExtensionsList);


      private:
	Window windowContext {windowWidth, windowLength, windowTitle};
	void ApplicationLoop( );
	void VulkanInit( );
	void VulkanFree( );
};


#endif // !BASE.H