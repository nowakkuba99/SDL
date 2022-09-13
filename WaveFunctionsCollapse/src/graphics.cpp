#include "graphics.h"
#include "pickTiles.h"
#include <iostream>
#include <string>

using namespace std;
using namespace Tiles;

/* Variables declaration */
int Graphics::NUMBER_OF_IMG_WITH_ROTATED = 14;
SDL_Window* Graphics::g_main_window = nullptr;        //Window object pointer
SDL_Renderer* Graphics::g_main_renderer = nullptr;    //Renderer object pointer
SDL_Surface* Graphics::rm_sur = nullptr;              //Surface to load imgs
std::vector<SDL_Texture*> Graphics::arr;    //Array of textures cointaing loaded images
std::vector<std::vector<SDL_Rect> > Graphics::rectMap(GRID_SIZE_H,std::vector<SDL_Rect>(GRID_SIZE_W));   //Map of rectangles used to display objects
std::vector<image*> Graphics::imgArr;
//std::vector<std::vector<string>> Graphics::boundArr = {{"ABA","AAA","ABA","AAA"},{"AAA","ABA","ABA","AAA"},{"ABA","AAA","ABA","ABA"}};
std::vector<std::vector<string>> Graphics::boundArr = {{"ACA","ABA","ACA","ABA"}, {"DDD","DDD","DDD","DDD"}, {"DAA","ABA","AAD","DDD"}, {"DAA","AAA","AAA","AAD"}, {"ABA","ABA","ABA","ABA"},
{"AAA","ABA","ABA","AAA"},{"AAA","AAA","AAA","AAA"}, {"ABA","AAA","ABA","ABA"}, {"AAA","ABA","AAA","ABA"}, {"AAA","ACA","AAA","ABA"},
{"AAA","ABA","ABA","AAA"}, {"ABA","AAA","ABA","AAA"}, {"AAA","ABA","AAA","AAA"}, {"ACA","AAA","ACA","AAA"}};
std::set<std::vector<string>> Graphics::boundSet;


/* FUNCTIONS */

/* Init SDL, window, rendered, load imgs */ 
bool Graphics::Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) > 0)      //Init SDL
  {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {          //Init SDL image to load JPGs
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
  for(int i = 0; i<NUMBER_OF_IMG; i++)
  {
      std::string x = "img/";
      //std::string path = "lines/";
      std::string path = "Circuit/";
      x+= path;
      //x+=(((i)+'0'));
      x += to_string(i);
      x+=".png";
      rm_sur = IMG_Load(x.c_str());     //Load imgs into surface
      if (rm_sur == NULL) {
        std::cout << "Error loading image: " << IMG_GetError();
      }

      arr.push_back(SDL_CreateTextureFromSurface(g_main_renderer, rm_sur));   //Push into array as a texuture
      if (arr[i] == NULL) {
        std::cout << "Error creating texture";
        return false;
      }
      imgArr.push_back(new image(i,0,boundArr[i]));
      Graphics::boundSet.insert(boundArr[i]);
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
  for(int i = 0; i<GRID_SIZE_H; i++)  //Destroy all tiles
  {
    for(int j = 0; j<GRID_SIZE_W; j++)
    {
      delete pickMap[i][j];
      pickMap[i][j] = nullptr;
    }
  }
  for(int i = 0; i<imgArr.size(); i++)
  {
    if(imgArr[i] != nullptr)
    {
      delete imgArr[i];     //Destroy all textures
      imgArr[i] = nullptr;
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

/* Initialise grid */
void Graphics::InitGrid(){
  for(int i = 0; i<GRID_SIZE_H; i++)
  {
    for(int j = 0; j<GRID_SIZE_W; j++)
    {
      rectMap[i][j].y = i*GRID_ELEMENT_W;
      rectMap[i][j].x = j*GRID_ELEMENT_H;
      rectMap[i][j].h = GRID_ELEMENT_H;
      rectMap[i][j].w = GRID_ELEMENT_W;
      if(pickMap[i][j]->imageObj != nullptr)
		    SDL_RenderCopyEx(g_main_renderer, arr[pickMap[i][j]->imageObj->getImgNum()], NULL, &rectMap[i][j],pickMap[i][j]->imageObj->getRotation(),NULL,SDL_FLIP_NONE);
    }
  }
}

/* 
  Desc: Function to updte grid at the given row and col
  Params: int row, int col
*/
void Graphics::DisplayGrid()
{
  for(int i = 0; i<GRID_SIZE_H; i++)
  {
    for(int j = 0; j<GRID_SIZE_W; j++)
    {
      if(pickMap[i][j]->imageObj != nullptr)
        SDL_RenderCopyEx(g_main_renderer, arr[pickMap[i][j]->imageObj->getImgNum()], NULL, &rectMap[i][j],pickMap[i][j]->imageObj->getRotation(),NULL,SDL_FLIP_NONE);
    }
  }
}

void Graphics::FindRotations()
{
  for(int i = 0; i<NUMBER_OF_IMG; i++)  //For each image not rotated
  {
    for(int j = 0; j<3; j++)    //Check 3 possible rotations
    {
      std::vector<std::string> curr;                     //Create new rotated bound
      curr.push_back(Graphics::boundArr[i][1+j]);
      curr.push_back(Graphics::boundArr[i][(2+j)%4]);
      curr.push_back(Graphics::boundArr[i][(3+j)%4]);
      curr.push_back(Graphics::boundArr[i][(j)]);

      if(Graphics::boundSet.find(curr) == Graphics::boundSet.end()) //Check if it is new
      {
        Graphics::boundSet.insert(curr);          //If so -> Add
        Graphics::boundArr.push_back(curr);
        Graphics::imgArr.push_back(new image(i,-(j+1)*90,curr));
        NUMBER_OF_IMG_WITH_ROTATED++;
        
      }

    }
    
  }
}