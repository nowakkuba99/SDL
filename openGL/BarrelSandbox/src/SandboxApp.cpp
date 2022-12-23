// Include libraries
#include <iostream>
#include <Barrel.hpp>
// Include user files

/* Sandbox application that is a sub class of Barrel Application */
class Sandbox : public Barrel::Application
{
    public:
        Sandbox()
        {

        };
        ~Sandbox()
        {

        };
};


/* Create application and pass to the barrel engine */
Barrel::Application* Barrel::CreateApplication()
{
    return new Sandbox();
}