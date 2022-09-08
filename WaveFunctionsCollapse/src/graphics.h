// graphics.h
#ifndef GRAPHICS_H // include guard
#define GRAPHICS_H

#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "image.h"

/* Colors */
namespace Colors {
  const SDL_Color BLACK = {0,0,0,SDL_ALPHA_OPAQUE}; //Black used to clear the screen
}

/* Graphics */
namespace Graphics
{
    /* Define CONST variables */
    const int WINDOW_WIDTH = 500;     //Window size
    const int WINDOW_HEIGHT = 500;
    const int NUMBER_OF_IMG = 3;
    extern int NUMBER_OF_IMG_WITH_ROTATED;
    const int GRID_SIZE_H = 10;    //5x5
    const int GRID_SIZE_W = 10;
    const int GRID_ELEMENT_H = WINDOW_HEIGHT/GRID_SIZE_H;
    const int GRID_ELEMENT_W = WINDOW_WIDTH/GRID_SIZE_W;
    /* Define EXTERN variables */
    extern SDL_Window* g_main_window;        //Window object pointer
    extern SDL_Renderer* g_main_renderer;    //Renderer object pointer
    extern SDL_Surface* rm_sur;              //Surface to load imgs
    extern std::vector<SDL_Texture*> arr;    //Array of textures cointaing loaded images
    extern std::vector<image*> imgArr;
    extern std::vector<std::vector<SDL_Rect> > rectMap;   //Map of rectangles used to display objects
    extern std::vector<std::vector<std::string>> boundArr;
    extern std::set<std::vector<std::string>> boundSet;
    /* Define functions */
    bool Init();
    void ShutDown();
    void ClearScreen(SDL_Renderer* renderer);
    void InitGrid();
    void DisplayGrid();
    void FindRotations();
}

#endif /* GRAPHICS */