// graphics.h
#ifndef GRAPHICS_H // include guard
#define GRAPHICS_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

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
    /* Define EXTERN variables */
    extern SDL_Window* g_main_window;        //Window object pointer
    extern SDL_Renderer* g_main_renderer;    //Renderer object pointer
    extern SDL_Surface* rm_sur;              //Surface to load imgs
    extern std::vector<SDL_Texture*> arr;    //Array of textures cointaing loaded images
    extern std::vector<std::vector<SDL_Rect> > rectMap;   //Map of rectangles used to display objects
    /* Define functions */
    bool Init();
    void ShutDown();
    void ClearScreen(SDL_Renderer* renderer);
    void InitGrid();
    void ChangeGrid(int i, int j, int pos);
}

#endif /* GRAPHICS */