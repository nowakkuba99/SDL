#ifndef FF5E1331_88AF_4C2B_BA17_7C2305C430C9
#define FF5E1331_88AF_4C2B_BA17_7C2305C430C9
// Includes

// User files

// Application class
namespace Barrel
{
    class Application
    {
    private:

    public:
        //Constructors
        Application();
        // Destructors
        virtual ~Application();
        // Custom functions
        void Run();
    };
    /* Function used to create application by dependent application */
    Application* CreateApplication();
}
#endif /* FF5E1331_88AF_4C2B_BA17_7C2305C430C9 */