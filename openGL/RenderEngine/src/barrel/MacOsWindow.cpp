#include "../pch/pchBarrel.hpp" //Pre-compiled headers

#include "MacOsWindow.hpp"  // MacOsWindow

#include "../events/ApplicationEvent.hpp"   //Events
#include "../events/MouseEvent.hpp"
#include "../events/KeyEvent.hpp"

namespace Barrel
{
    // Variables
    static bool s_GLFWInitialized = false;  // Stores information if GLFW has beed initialized

    // Constructor
    MacOsWindow::MacOsWindow(const WindowProperties& properties)
    {
        Init(properties);
    }

    // Destructor
    MacOsWindow::~MacOsWindow()
    {
        Shutdown(); // Call shutdown function
    }

    /* Functions */

    // Create window
    Window* MacOsWindow::Create(const WindowProperties prop)
    {
        return new MacOsWindow(prop);  // Return heap allocated window object
    }

    // Shutdown window
    void MacOsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    // OnUpdate
    void MacOsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    // SetVSync
    void MacOsWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }
    // Check if V Sync set
    bool MacOsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
    
    // Initialize window
    void MacOsWindow::Init(const WindowProperties& prop)
    {
        // Set member variables
        m_Data.Title = prop.Title;
        m_Data.Width = prop.Width;
        m_Data.Height = prop.Height;

        // Create information that window is being created
        BR_CORE_INFO("Creating window through glfw {0} ({1}, {2})", prop.Title, prop.Width, prop.Height);

        // If GLFW is not initialized yet -> Initialize
        if(!s_GLFWInitialized)
        {
            // TODO: glfwTerminae on system shutdown
            int succes = glfwInit();
            BR_ASSERT(succes, "Could not initialize GLFW!");

            s_GLFWInitialized = true;
        }

        // Create window
        m_Window = glfwCreateWindow((int)prop.Width, (int)prop.Height, m_Data.Title.c_str(),nullptr,nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);    //Not sure how it works yet
        SetVSync(true);
    }

    
    
}

