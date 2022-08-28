#include "graphics.h"
#include "pickTiles.h"
#include <iostream>

using namespace std;
using namespace Tiles;

/* Variables declaration */
SDL_Window* Graphics::g_main_window = nullptr;        //Window object pointer
SDL_Renderer* Graphics::g_main_renderer = nullptr;    //Renderer object pointer
SDL_Surface* Graphics::rm_sur = nullptr;              //Surface to load imgs
std::vector<SDL_Texture*> Graphics::arr;    //Array of textures cointaing loaded images
std::vector<std::vector<SDL_Rect> > Graphics::rectMap(5,std::vector<SDL_Rect>(5));   //Map of rectangles used to display objects


/* FUNCTIONS */

/* Init SDL, window, rendered, load imgs */ 
bool Graphics::Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) > 0)      //Init SDL
  {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  if (IMG_Init(IMG_INIT_JPG) == 0) {          //Init SDL image to load JPGs
		std::cout << "Error SDL2_image Initialization"<<std::endl;
	}

  g_main_window = SDL_CreateWindow(           //Create window 
    "Wave function collapse",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_OPENGL
  );
  if(g_main_window == nullptr) {
    std::cout<< "Unable to create window" << SDL_GetError()<<"\n";
    SDL_Quit();
    return EXIT_FAILURE;
  }                                       
  g_main_renderer = SDL_CreateRenderer(g_main_window,-1,SDL_RENDERER_PRESENTVSYNC);     //Create renderer
  // Load all images into the array
  for(int i = 0; i<5; i++)
  {
      std::string x = "img/";
      x+=(((i+1)+'0'));
      x+=".jpeg";
      rm_sur = IMG_Load(x.c_str());     //Load imgs into surface
      if (rm_sur == NULL) {
        std::cout << "Error loading image: " << IMG_GetError();
      }

      arr.push_back(SDL_CreateTextureFromSurface(g_main_renderer, rm_sur));   //Push into array as a texuture
      if (arr[i] == NULL) {
        std::cout << "Error creating texture";
        return false;
      }

      SDL_FreeSurface(rm_sur);    //Free surface for next imgs
      rm_sur = nullptr;
  }

  return true;
}

/*Shut down - delete all pointers etc. */
void Graphics::ShutDown() {
  if(g_main_window != nullptr)
  {
    SDL_DestroyWindow(g_main_window);   //Destroy window
    g_main_window = nullptr;
  }
  if(g_main_renderer != nullptr)
  {
    SDL_DestroyRenderer(g_main_renderer);   //Destroy renderer
    g_main_renderer = nullptr;
  }
  for(int i =0;i<arr.size(); i++)
  {
    if(arr[i] != nullptr)
    {
      SDL_DestroyTexture(arr[i]);     //Destroy all textures
      arr[i] = nullptr;
    }
  }
  IMG_Quit();     //Quit SDL_IMG
  SDL_Quit();     //Quit SDL
}
/* Clear screen */
void Graphics::ClearScreen(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b,Colors::BLACK.a);
  SDL_RenderClear(renderer);
}
SDL_Rect rect = {0,0, 100, 100};

/* Initialise grid */
void Graphics::InitGrid(){
  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<5; j++)
    {
      rectMap[i][j].x = i*100;
      rectMap[i][j].y = j*100;
      rectMap[i][j].h = 100;
      rectMap[i][j].w = 100;
		  SDL_RenderCopy(g_main_renderer, arr[pickMap[i][j]], NULL, &rectMap[i][j]);
    }
  }
}

/* Upadte grid */
void Graphics::ChangeGrid(int i, int j, int pos)
{
  Graphics::InitGrid();
  pickMap[i][j] = pos;
  SDL_RenderCopy(g_main_renderer, arr[pickMap[i][j]], NULL, &rectMap[i][j]);
}
