#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

using namespace std;

const int s_width = 1280;
const int s_height = 760;


int initialize(SDL_Window* &window, SDL_Surface* &screenSurface)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Error");
    return 0;
  }
  else
  {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_width, s_height, SDL_WINDOW_SHOWN);

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

int main()
{
  int there = 0;
  int quit = 0;
  SDL_Event evt;
  SDL_Window* window;
  SDL_Surface* screenSurface;
  SDL_Rect rect = {0, 0, 600, 300};
  //1 grid spot is 50x50

  initialize(window, screenSurface);

  SDL_Surface* g;
  g = IMG_Load("Cursor.png");

  SDL_UpdateWindowSurface(window);




  while(!quit)
  {
    SDL_UpdateWindowSurface(window);
    SDL_WaitEvent(&evt);
    if(evt.type == SDL_QUIT)
      quit = 1;
    //Different drawings based on state/room
    //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_BlitSurface(g, NULL, screenSurface, &rect);
    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;
}
