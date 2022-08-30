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
  int pos = 0;
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
  SDL_RenderPresent(g_main_renderer); 
  while(running)
  {
    //Check and process I/O event
    if(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN: {
          if(event.key.keysym.scancode != SDL_SCANCODE_ESCAPE)
          {
            //int i = rand() % 5;
            //int j = rand() % 5;
            //int pos = rand() % 2;
            int i = 0, j = 0;
            
            ClearScreen(g_main_renderer);
            ChangeGrid(i,j,pos);
            if(pos<NUMBER_OF_IMG_WITH_ROTATED-1)
              pos++;
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