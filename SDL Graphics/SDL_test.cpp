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
  int menu = 0; // Menu flag
  string menu_type = "main"; // "main (2x3)", "inv (1x4)", "inv2 (3x1 use/examine/etc)"
  int cursor = 0; // main (0,1,2/3,4,5), inv(0,1,2,3), inv2(0,1,2)
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
  SDL_Rect hud_rect;
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
          if (menu == 0)
            pc.y += 10;
          break;

        case SDLK_RIGHT:
          if (menu == 0)
            pc.x += 10;
          break;

        case SDLK_LEFT:
          if (menu == 0)
            pc.x -= 10;
          break;

        case SDLK_UP:
          if (menu == 0)
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
          if (menu == 0)
          {
            menu = 1;
          }
          else if (menu == 1 && menu_type == "main")
          {
            menu = 0;
          }
          break;
      }
    }

    //Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //Draw Player
    pc_rect = {pc.x, pc.y, 100, 100};
    SDL_BlitSurface(g, NULL, screenSurface, &pc_rect);
    SDL_UpdateWindowSurface(window);

    //Draw Other Players(s)

    //Draw HUD-related

    //Inventory (REPLACE WITH FUNCTION)
    if (menu == 1)
    {
      //Hides in-game image
      //HUD Background
      hud_rect = {0, 450, 1280, 500};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
      /////////////////////////////
      //Profile Image
      hud_rect = {50, 500, 200, 200};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xBB, 0xFF));

      ////////////////////
      //Cursor
      if (menu_type == "main")
      {
        switch(cursor)
        {
          case 0:
            hud_rect = {390, 490, 270, 120};      //-10,-10, +20, +20 vs original
            break;
          case 1:
            hud_rect = {665, 490, 270, 120};
            break;
          case 2:
            hud_rect = {940, 490, 270, 120};
            break;
          case 3:
            hud_rect = {390, 625, 200, 200};
            break;
          case 4:
            hud_rect = {665, 625, 200, 200};
            break;
          case 5:
            hud_rect = {940, 625, 200, 200};
            break;
        }
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xE3, 0x86, 0x34));
      }
      else if (menu_type == "inv")
      {
        switch(cursor)
        {
          case 0:
            hud_rect = {50, 500, 200, 200};
            break;
          case 1:
            hud_rect = {50, 500, 200, 200};
            break;
          case 2:
            hud_rect = {50, 500, 200, 200};
            break;
          case 3:
            hud_rect = {50, 500, 200, 200};
            break;
        }
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xBB, 0xFF));
      }
      else if (menu_type == "inv2")
      {
        switch(cursor)
        {
          case 0:
            hud_rect = {50, 500, 200, 200};
            break;
          case 1:
            hud_rect = {50, 500, 200, 200};
            break;
          case 2:
            hud_rect = {50, 500, 200, 200};
            break;
        }
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xBB, 0xFF));
      }


      /////////////////////////////////
      //Menu Slots
      hud_rect = {400, 500, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {675, 500, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {950, 500, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {400, 625, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {675, 625, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {950, 625, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image
    }
    //Text boxes

    //Clear everything? / Renderer?
  }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;
}
