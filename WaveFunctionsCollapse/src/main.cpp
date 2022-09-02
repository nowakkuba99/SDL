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
  srand(time(0));
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
  DisplayGrid();   
  SDL_RenderPresent(g_main_renderer); 
  while(running)
  {
    //Check and process I/O event
    if(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN: {
          if(event.key.keysym.scancode != SDL_SCANCODE_ESCAPE)
          {
            ClearScreen(g_main_renderer);
            /* Main CODE part*/
            DisplayGrid();                                    //Display grid
            if(!Tiles::ListOfTilesToCollapse.empty())
            {
              Tiles::CountPossForListOfTilesToCollapse();       //Count the possibilites for List and sort
              int randPick = rand() % Tiles::ListOfTilesToCollapse.back()->numOfPosImgs;  //Pick randomly the imgae from possibilites
              Tiles::ListOfTilesToCollapse.back()->imageObj = Tiles::ListOfTilesToCollapse.back()->ListOfPossImgs[randPick];  //Set the image object to picked img
              Tiles::ListOfTilesToCollapse.back()->collapsed = true;  //Marked as collapsed
              int row = Tiles::ListOfTilesToCollapse.back()->row, col = Tiles::ListOfTilesToCollapse.back()->col;
              Tiles::ListOfTilesToCollapse.pop_back();
              Tiles::UpdateListOfTilesToCollapse(row,col);    //Update the list of Tiles to collapse
            }
            /* MAIN CODE part end */
            DisplayGrid();                                    //Display grid
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