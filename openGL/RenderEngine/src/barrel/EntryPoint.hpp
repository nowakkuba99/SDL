#ifndef A2F93990_4999_4A90_8074_4E89BF8157EA
#define A2F93990_4999_4A90_8074_4E89BF8157EA
/* 
    File that has the main function implemented 
*/
// Includes
#include "application.hpp"
#include "Log.hpp"
/* Extern variables declaration */
extern Barrel::Application* Barrel::CreateApplication();

/* Main implementation */
int main(int aggc, char** argv)
{
    Barrel::Log::Init();    //Initialize logger
    //Barrel::Log::GetCoreLogger()->warn("This is a core warning!");
    //Barrel::Log::GetClientLogger()->info("This is a client info!");
    BR_CORE_ERROR("XXXX");
    auto app = Barrel::CreateApplication();
    app->Run();
    delete app;
}

#endif /* A2F93990_4999_4A90_8074_4E89BF8157EA */
