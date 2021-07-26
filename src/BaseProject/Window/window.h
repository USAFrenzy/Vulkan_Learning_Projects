#ifndef WINDOW_H
#define WINDOW_H

/*  
    Probably uneccessary at this point in time and in this file but using the 
    defines as a way to determine how to draw to the window will be useful I think
*/
#define VK_GRAPHICS // So As A Placeholder -> Just Going To Force Define VK_GRAPHICS

#ifdef VK_GRAPHICS
	#define	GLFW_INCLUDE_VULKAN
#else
	#define DX_GRAPHICS
#endif

#include <GLFW/glfw3.h>
#include <string>

class Window
{
    public:
	Window(int height, int width, std::string title);
	~Window( );
	void createWindow();

	private:
	GLFWwindow *window;
	const int windowHeight;
	const int windowWidth;
	std::string windowTitle;
};


#endif // !WINDOW_H