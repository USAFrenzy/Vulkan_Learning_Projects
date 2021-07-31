#include <iostream> // Only here for std::cerr at the moment - remove when logging added
#include "window.h"


Window::Window(int height, int width, std::string title)
  : windowHeight(height), windowWidth(width), windowTitle(title)
{
	createWindow( );
	std::cout << "Window Successfully Created\n";
}

Window::~Window( )
{
	glfwDestroyWindow(window);
	std::cout << "Window Destroyed\n";
	glfwTerminate( );
	std::cout << "GLFW Terminated\n";
}

void Window::createWindow( )
{
	if(!glfwInit( )) {
		std::cerr << "Unable to Initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Fourth Parameter is Window Mode And Fifth Parameter Is For OpenGL context
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str( ), nullptr, nullptr);
}

// Temporary Functions Until Event Handler Implemented
bool Window::Close( )
{
	PollEvents( );
	return glfwWindowShouldClose(window);
}

void Window::PollEvents( )
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowPosCallback(window, window_pos_callback);
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "Cursor Position is at: Y=" << ypos << " X=" << xpos << "\n";
}
void Window::window_pos_callback(GLFWwindow* window, int x, int y)
{
	std::cout << "Window Position Moved To: (" << x << ", " << y << ")\n";
}