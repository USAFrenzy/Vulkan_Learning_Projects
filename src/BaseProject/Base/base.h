#ifndef BASE_H
#define BASE_H

#include "Window/window.h"

class BaseApplication
{
      public:
		const int windowWidth {480}, windowLength {640};
		std::string windowTitle {"Base Application"};

      public:
		BaseApplication( );
		~BaseApplication( );
		void Run( );
		void createInstance( );
      private:
		Window windowContext {windowWidth, windowLength, windowTitle};
		void applicationLoop( );
		void vulkanInit( );
		void vulkanFree( );
		VkInstance instance;
     
};



#endif // !BASE.H