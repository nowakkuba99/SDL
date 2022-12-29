#include "../../pch/pchBarrel.hpp" //Pre-compiled headers

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

        /* --- Set GLFW events callbacks --- */
        // Window Resize 
        glfwSetWindowSizeCallback(m_Window,[](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width,height);
            data.EventCallback(event);
        });

        // Window Close
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        // Key callbacks
        glfwSetKeyCallback(m_Window,[](GLFWwindow* window,int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key,false);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key,true);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        // Set Char ?
        glfwSetCharCallback(m_Window,[](GLFWwindow* window,unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        // Mouse button press
        glfwSetMouseButtonCallback(m_Window,[](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        // Mouse scroll
        glfwSetScrollCallback(m_Window,[](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event{(float)xOffset,(float)yOffset};
            data.EventCallback(event);
        });

        //Mouse moved
        glfwSetCursorPosCallback(m_Window,[](GLFWwindow* window,double xPos, double yPos){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event{(float)xPos, (float)yPos};
            data.EventCallback(event);
        });
    }

    
    
}

