// Includes
#include <iostream>

#include "application.hpp"
#include "Log.hpp"
#include "../events/ApplicationEvent.hpp"

// Application class implementation
namespace Barrel
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        std::cout<<"Barrel started!\n";
        WindowResizeEvent e(1280,720);
        BR_TRACE(e);
    }
}
