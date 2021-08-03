#ifndef WINDOW_H
#define WINDOW_H

/*
    Probably uneccessary at this point in time and in this file but using the
    defines as a way to determine how to draw to the window will be useful I think
*/
#define VK_GRAPHICS // So As A Placeholder -> Just Going To Force Define VK_GRAPHICS

#ifdef VK_GRAPHICS
	#define GLFW_INCLUDE_VULKAN
#else
	#define DX_GRAPHICS
#endif

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


class Window
{
      public:
	Window(int height, int width, const char* title);
	~Window( );

	// Temporary Functions Until Event Handler Implemented
	bool Close( );
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void window_pos_callback(GLFWwindow* window, int x, int y);
	void PollEvents( );

      private:
	void createWindow( );


      private:
	GLFWwindow* window;
	const int windowHeight;
	const int windowWidth;
	const char* windowTitle;
};


#endif // !WINDOW_H