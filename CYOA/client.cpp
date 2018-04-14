#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "images.h"
#include "rooms.h"
#include "mobs.h"
#include "input.h"
//#include "objects.h" (redundant)
#include "network.h"
#include "menu.h"
#include "inventory.h"


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
  //test
}

/*void draw_player(SDL_Surface* img, SDL_Su)
{
  SDL_BlitSurface(img, NULL, screenSurface, &rect);
}*/

int main()
{
  int menu = 0; // Menu flag
  string menu_type = "main"; // "main (2x3)", "inv (1x4)", "inv2 (3x1 use/combine/examine/trade)"
  int cursor = 0; // main (0,1,2/3,4,5), inv(0,1,2,3), inv2(0,1,2)
  int inv = 0; //Inventory flag
  int inter = 0; //Interact flag
  int quit = 0;
  SDL_Event evt;
  SDL_Window* window;
  SDL_Surface* screenSurface;

  //1 grid spot is 50x50

  initialize(window, screenSurface);

  //Setup Images
  SDL_Surface* g;
  g = IMG_Load("images/G.png");

  SDL_Surface* img;
  img = IMG_Load("images/Cursor.png");

  SDL_Surface* door;
  door = IMG_Load("images/door.png");

  SDL_UpdateWindowSurface(window);

  //Set up network stuff

  //Set up Player Stuff
  Mob pc = Mob("Bran", 100, 100);
  //PC Inventory
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  SDL_Rect pc_rect;
  SDL_Rect hud_rect;

  //DOOR_TEST
  //Door door1 = Door();
  //door1.rect = {50, 50, 100, 100};


  while(!quit)
  {
    SDL_UpdateWindowSurface(window);
    SDL_WaitEvent(&evt);


    if(evt.type == SDL_QUIT)
      quit = 1;

    process_input(cursor, evt, pc, menu, menu_type, pc_rect, hud_rect, quit);

    //Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //Draw Room
    //if (door1.state == "closed")
      //SDL_BlitSurface(door, NULL, screenSurface, &(door1.rect));

    //Draw Player
    pc_rect = {pc.x, pc.y, 100, 100};
    SDL_BlitSurface(g, NULL, screenSurface, &pc_rect);
    SDL_UpdateWindowSurface(window);

    //Draw Other Players(s)

    //Draw HUD-related
    draw_menu(cursor, menu, menu_type, hud_rect, pc, screenSurface);

    //Clear everything? / Renderer?
    }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;

}
