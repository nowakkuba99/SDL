#ifndef A2F93990_4999_4A90_8074_4E89BF8157EA
#define A2F93990_4999_4A90_8074_4E89BF8157EA
/* 
    File that has the main function implemented 
*/
// Includes
#include "application.hpp"

/* Extern variables declaration */
extern Barrel::Application* Barrel::CreateApplication();

/* Main implementation */
int main(int aggc, char** argv)
{
    auto app = Barrel::CreateApplication();
    app->Run();
    delete app;
}

#endif /* A2F93990_4999_4A90_8074_4E89BF8157EA */
