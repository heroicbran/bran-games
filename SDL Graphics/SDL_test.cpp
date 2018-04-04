#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

using namespace std;

const int s_width = 1280;
const int s_height = 760;


struct Mob
{
  string name;
  int x;
  int y;
  SDL_Rect m_rect;

  Mob() : name{"test"}, x{0}, y{0}
  {
    m_rect = {0, 0, 600, 300};
    //Stuff?
  }

  Mob(string n, int posx, int posy) : name{n}, x{posx}, y{posy}
  {
    m_rect = {0, 0, 600, 300};
  }
};

int initialize(SDL_Window* &window, SDL_Surface* &screenSurface)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Error");
    return 0;
  }
  else
  {
    window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_width, s_height, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
      printf("Error 2");
      return 0;
    }
    else
    {
      IMG_Init(IMG_INIT_PNG);

      screenSurface = SDL_GetWindowSurface(window);

      //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      SDL_UpdateWindowSurface(window);

      //SDL_Delay (2000);
    }

  }

  return 1;
}

void load_images()
{

}

/*void draw_player(SDL_Surface* img, SDL_Su)
{
  SDL_BlitSurface(img, NULL, screenSurface, &rect);
}*/

int main()
{
  //int there = 0;
  int inv = 0; //Inventory
  int inter = 0; //Interact
  int quit = 0;
  SDL_Event evt;
  SDL_Window* window;
  SDL_Surface* screenSurface;

  //1 grid spot is 50x50

  initialize(window, screenSurface);

  SDL_Surface* g;
  g = IMG_Load("G.png");

  SDL_Surface* img;
  img = IMG_Load("Cursor.png");

  SDL_UpdateWindowSurface(window);



  //Setup Game Stuff
  Mob pc = Mob("Bran", 100, 100);
  SDL_Rect pc_rect;
  while(!quit)
  {
    SDL_UpdateWindowSurface(window);
    SDL_WaitEvent(&evt);


    if(evt.type == SDL_QUIT)
      quit = 1;

    //REPLACE WITH BUTTON CHECK FUNCTION!
    if(evt.type == SDL_KEYDOWN)
    {
      switch(evt.key.keysym.sym)
      {
        case SDLK_DOWN:
          pc.y += 10;
          break;

        case SDLK_RIGHT:
          pc.x += 10;
          break;

        case SDLK_LEFT:
          pc.x -= 10;
          break;

        case SDLK_UP:
          pc.y -= 10;
          break;

        case SDLK_ESCAPE:
          quit = 1;
          break;

        case SDLK_z:
          //Interact flag toggle
          break;

        case SDLK_x:
          //Inventory flag toggle
          inv = 1;
          break;
      }
    }
    //Different drawings based on state/room
    //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

    //Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //Draw Player
    pc_rect = {pc.x, pc.y, 100, 100};
    SDL_BlitSurface(g, NULL, screenSurface, &pc_rect);
    SDL_UpdateWindowSurface(window);

    //Draw HUD-related
    //Inventory (REPLACE WITH FUNCTION)
    if (inv == 1)
    {
      SDL_Rect inv_rect = {0, 450, 1280, 500};
      SDL_FillRect(screenSurface, &inv_rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    }
    //Text boxes
  }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;
}
