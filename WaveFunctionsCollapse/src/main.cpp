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
  Graphics::FindRotations();
  Tiles::InitTilesMap();
  InitGrid();
  Tiles::PickFirstTile();
  SDL_RenderPresent(g_main_renderer); 
  while(running)
  {
    //Check and process I/O event
    if(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN: {
          if(event.key.keysym.scancode != SDL_SCANCODE_ESCAPE)
          {
            /* Main CODE part*/

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