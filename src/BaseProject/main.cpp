#include "Base/base.h"
#include "Window/window.h"

#include <iostream>
#include <stdexcept>


int main( )
{
	std::cout << "Testing Initial Setup\n\n";


	BaseApplication app;
	app.AddValidationLayer("VK_LAYER_KHRONOS_validation");

	try {
		app.Run( );
	} catch(const std::exception& e) {
		std::cerr << e.what( ) << '\n';
	}
}