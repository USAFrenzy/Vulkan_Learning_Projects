#include "Base/base.h"
#include "Window/window.h"

#include <iostream>
#include <stdexcept>


int main()
{
    std::cout << "Testing Initial Setup\n\n";
        
  
    BaseApplication app;
    
    try
    {
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

   
}