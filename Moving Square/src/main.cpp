// Jakub Nowak 26.08.2022
#include <iostream>
#include <SDL2/SDL.h>
#define SDL_MAIN_HANDLED
//Colors
namespace Colors {
  const SDL_Color BLACK = {0,0,0,SDL_ALPHA_OPAQUE};
  const SDL_Color GREEN = {0, 255,0, SDL_ALPHA_OPAQUE};
}
namespace Graphics {
  struct Screen
  {
    const int WINDOW_WIDTH = 512;
    const int WINDOW_HEIGHT = 284;

    const int centerX = WINDOW_WIDTH/2;
    const int centerY = WINDOW_HEIGHT/2;
  };
};

//Game objects
enum SquareState {IDLE, MOVING_UP, MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT};

struct Square
{
  int h, w, x, y;
  SquareState state;
  int step;
};

//App
struct App
{
  const int DEFAULT_STEP = 2;

  SDL_Window* g_main_window;
  SDL_Renderer* g_main_renderer;

  Graphics::Screen screen;

  Square square
  {
    32,32,screen.centerX,screen.centerY,IDLE,DEFAULT_STEP
  };
} app;

//SDL routines
bool InitSDL() {
  if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
  {
    std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}
//Graphic routines

void ClearScreen(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b,Colors::BLACK.a);
  SDL_RenderClear(renderer);
}

void DrawSquare(int x, int y)
{
  SDL_Rect rect;
  rect.x = x - (app.square.w/2);
  rect.y = y - (app.square.h/2);
  rect.w = app.square.w;
  rect.h = app.square.h;
  //Green
  SDL_SetRenderDrawColor(app.g_main_renderer, Colors::GREEN.r,Colors::GREEN.g,Colors::GREEN.b,Colors::GREEN.a);
  SDL_RenderFillRect(app.g_main_renderer,&rect);
}
//Application routines
void ShutDown() {
  if(app.g_main_window != nullptr)
  {
    SDL_DestroyWindow(app.g_main_window);
    app.g_main_window = nullptr;
  }
  if(app.g_main_renderer != nullptr)
  {
    SDL_DestroyRenderer(app.g_main_renderer);
    app.g_main_renderer = nullptr;
  }
  SDL_Quit();
}

bool InitApp() {
  if(InitSDL() == false)
  {
    ShutDown();
    return false;
  }


  app.g_main_window = SDL_CreateWindow(
    "Moving Square (512x284)",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    app.screen.WINDOW_WIDTH,
    app.screen.WINDOW_HEIGHT,
    SDL_WINDOW_OPENGL
  );
  if(app.g_main_window == nullptr) {
    std::cout<< "Unable to create window" << SDL_GetError()<<"\n";
    ShutDown();
    return false;
  }
  app.g_main_renderer = SDL_CreateRenderer(app.g_main_window,-1,SDL_RENDERER_PRESENTVSYNC);

  return true;
}

void setState(SquareState st)
{
  app.square.state = st;
}
void incStep()
{
  app.square.step = app.square.state * app.DEFAULT_STEP;
}

void decStep()
{
  int new_step = app.square.step / app.DEFAULT_STEP;
  if (new_step > app.DEFAULT_STEP)
  {
    app.square.step = new_step;
  }
  else
  {
    app.square.step = app.DEFAULT_STEP;
  }
}

int main(int argc, char *argv[])
{
  if(InitApp() == false)
  {
    ShutDown();
    return EXIT_FAILURE;
  }
  //Draw loop
  SDL_Event event;
  bool running = true;
  while(running)
  {
    ClearScreen(app.g_main_renderer);
    //Check square state
    switch(app.square.state)
    {
      case MOVING_UP:
      {
        int new_y = app.square.y - app.square.step;
        if (new_y > (app.square.h / 2))
        {
          app.square.y = app.square.y - app.square.step;
        }
        else
        {
          app.square.y = (app.square.h / 2);
          setState(MOVING_DOWN);
        }

        break;
      }
      case MOVING_DOWN:
      {
        int new_y = app.square.y + app.square.step;
        if (new_y + (app.square.h / 2) < app.screen.WINDOW_HEIGHT)
        {
          app.square.y = app.square.y + app.square.step;
        }
        else
        {
          app.square.y = new_y - (new_y + (app.square.h / 2) - app.screen.WINDOW_HEIGHT);
          setState(MOVING_UP);
        }

        break;
      }
      case MOVING_LEFT:
      {
        int new_top_left_x = app.square.x - app.square.step - (app.square.w / 2);
        if (new_top_left_x > app.square.step)
        {
          app.square.x = app.square.x - app.square.step;
        }
        else
        {
          app.square.x = (app.square.w / 2);
          setState(MOVING_RIGHT);
        }

        break;
      }
      case MOVING_RIGHT:
      {
        int new_top_left_x = app.square.x + app.square.step;
        if (new_top_left_x + (app.square.w / 2) <= app.screen.WINDOW_WIDTH)
        {
          app.square.x = app.square.x + app.square.step;
        }
        else
        {
          setState(MOVING_LEFT);
        }

        break;
      }
      default:
        break;
    }
 // Check and process I/O events
    if (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_KEYDOWN:
        {
          running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;

          if (event.key.keysym.scancode == SDL_SCANCODE_UP)
          {
            setState(MOVING_UP);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
          {
            setState(MOVING_DOWN);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
          {
            setState(MOVING_LEFT);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
          {
            setState(MOVING_RIGHT);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_S)
          {
            setState(IDLE);
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_I)
          {
            incStep();
          }

          if (event.key.keysym.scancode == SDL_SCANCODE_D)
          {
            decStep();
          }

          break;
        }
        case SDL_QUIT:
        {
          running = false;
          break;
        }
        default:
          break;
      }
    }
    //Draw new square
    DrawSquare(app.square.x,app.square.y);
    //Update the screen with the content rendered in buffer
    SDL_RenderPresent(app.g_main_renderer);
  }
  ShutDown();
  return EXIT_SUCCESS;
}