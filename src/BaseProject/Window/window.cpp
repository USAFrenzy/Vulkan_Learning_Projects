#include <iostream> // Only here for std::cerr at the moment - remove when logging added
#include "window.h"



Window::Window(int height, int width, std::string title) : windowHeight(height), windowWidth(width), windowTitle(title) { 
	createWindow();
}

Window::~Window( ) 
{ 

}

void Window::createWindow() 
{
	if( !glfwInit) 
	{
		std::cerr << "Unable to Initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
}