// Includes
#include <iostream>

#include "application.hpp"

// Application class implementation
namespace Barrel
{
/* Macros */
// Macro to bind application function with 1 argument
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application()
    {
        /* Create window */
        m_Window = std::unique_ptr<Window> (Window::Create());
        /* Set callback that will be called if ANY event occurs */
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
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
    // Function that is called with all events
    void Application::OnEvent(Event& event)
    {
        // Create Event Dispatcher
        EventDispatcher dispatch(event);
        // Create call for WindowCloseEvent to OnWindowClose function
        dispatch.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));


        // Trace all events occurences
        BR_CORE_TRACE("{0}",event);
    }
    // Function being called when window close event occurs
    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
}
