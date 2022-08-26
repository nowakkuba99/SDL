// Jakub Nowak 26.08.2022
#include <iostream>
#include <SDL2/SDL.h>

//Graphics
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 284;
SDL_Window* g_main_window;
SDL_Renderer* g_main_renderer;

//Colors
namespace Colors {
  const SDL_Color BLACK = {0,0,0,SDL_ALPHA_OPAQUE};
}
static bool Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
  {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }
  g_main_window = SDL_CreateWindow(
    "SDL Create Window (512x284)",
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
  g_main_renderer = SDL_CreateRenderer(g_main_window,-1,SDL_RENDERER_PRESENTVSYNC);

  return true;
}

void ShutDown() {
  if(g_main_window != nullptr)
  {
    SDL_DestroyWindow(g_main_window);
    g_main_window = nullptr;
  }
  if(g_main_renderer != nullptr)
  {
    SDL_DestroyRenderer(g_main_renderer);
    g_main_renderer = nullptr;
  }
  SDL_Quit();
}

static void ClearScreen(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b,Colors::BLACK.a);
  SDL_RenderClear(renderer);
}

int main()
{
  if(Init() == false)
  {
    ShutDown();
  }
  //Draw loop
  SDL_Event event;
  bool running = true;
  while(running)
  {
    ClearScreen(g_main_renderer);
    //Check and process I/O event
    if(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN: {
          running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
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

    //Update the screen with the content rendered in buffer
    SDL_RenderPresent(g_main_renderer);
  }
  ShutDown();
  return EXIT_SUCCESS;
}