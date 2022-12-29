#ifndef FF5E1331_88AF_4C2B_BA17_7C2305C430C9
#define FF5E1331_88AF_4C2B_BA17_7C2305C430C9
// Includes

// User files
#include "../window/Window.hpp"
#include "../events/Event.hpp"
#include "../events/ApplicationEvent.hpp"
#include "../layers/LayerStack.hpp"
// Application class
namespace Barrel
{
    class Application
    {
    public:
        //Constructors
        Application();
        // Destructors
        virtual ~Application();
        // Custom functions
        void Run();
        // Event Realted
        void OnEvent(Event& event);
        // Layer related
        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
    private:
        // Functions
        bool OnWindowClose(WindowCloseEvent& event);

        // Member variables
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };
    /* Function used to create application by dependent application */
    Application* CreateApplication();
}
#endif /* FF5E1331_88AF_4C2B_BA17_7C2305C430C9 */
