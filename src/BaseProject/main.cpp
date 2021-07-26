#include "Base/base.h"
#include "Window/window.h"

#include <iostream>
#include <stdexcept>


int main()
{
    std::cout << "Testing Initial Setup\n\n";

    /****************************************************************
                       Testing Basic GLFW Setup
    ****************************************************************/
    Window testWindow(800, 600, "TestWindow");        
    

    /***************************************************************/
    BaseApplication app;
    
    try
    {
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    std::getchar(); // Only Here To Pause Before Auto Closing
}