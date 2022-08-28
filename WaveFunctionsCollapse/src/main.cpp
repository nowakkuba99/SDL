/* Includes */
#include <iostream>

/* Files */
#include "graphics.h"

/* Namespace */
using namespace Graphics;

/* Main function */
int main()
{
  if(Init() == false)
  {
    ShutDown();
  }
  //Draw loop
  SDL_Event event;
  bool running = true;
  SDL_RenderClear(g_main_renderer);
  InitGrid();
  SDL_RenderPresent(g_main_renderer); 
  while(running)
  {
    //Check and process I/O event
    if(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN: {
          if(event.key.keysym.scancode != SDL_SCANCODE_ESCAPE)
          {
            int i = 0;
            int j = 0;
            int pos = rand() % 4 + 1;
            ClearScreen(g_main_renderer);
            ChangeGrid(i*100,j*100,pos);
            SDL_RenderPresent(g_main_renderer); 
          }
          else
            running = false;
          break;
        }
        case SDL_QUIT: {
          running = false;
          break;
        }
        default:
          break;
      }
    }
  }
  ShutDown();
  return EXIT_SUCCESS;
}