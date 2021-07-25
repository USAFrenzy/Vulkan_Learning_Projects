#include <iostream>
#include <stdexcept>


#include "Base/base.h"

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
    

    std::getchar(); // Only Here To Pause Before Auto Closing
}