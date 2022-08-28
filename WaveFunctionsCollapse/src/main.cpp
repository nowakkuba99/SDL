/* Includes */
#include <iostream>

/* Files */
#include "graphics.h"
#include "pickTiles.h"

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
  Tiles::InitTilesMap();
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
            int i = rand() % 5;
            int j = rand() % 5;
            int pos = rand() % 5;
            int rot = 90;
            ClearScreen(g_main_renderer);
            ChangeGrid(i,j,pos,rot);
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