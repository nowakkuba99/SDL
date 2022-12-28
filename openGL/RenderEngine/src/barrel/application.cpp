// Includes
#include <iostream>

#include "application.hpp"
#include "../events/ApplicationEvent.hpp"

// Application class implementation
namespace Barrel
{
    Application::Application()
    {
        m_Window = std::unique_ptr<Window> (Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        std::cout<<"Barrel started!\n";
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
    }
}
