#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

const int s_width = 1280;
const int s_height = 760;


struct Mob
{
  string name;
  int x;
  int y;
  vector<string> inventory;
  Mob() : name{"test"}, x{0}, y{0}
  {

  }

  Mob(string n, int posx, int posy) : name{n}, x{posx}, y{posy}
  {

  }
};

struct Door
{
  string name = "door";
  string state = "closed"; //or open
  string icon = "door.png";
  SDL_Rect rect;


  void interact()
  {
      //Put in player button press.
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
  g = IMG_Load("120430.gif");

  SDL_Surface* img;
  img = IMG_Load("Cursor.png");

  SDL_Surface* door;
  door = IMG_Load("door.png");

  SDL_UpdateWindowSurface(window);



  //Setup Game Stuff
  Mob pc = Mob("Bran", 100, 100);
  //PC Inventory
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  SDL_Rect pc_rect;
  SDL_Rect hud_rect;

  //DOOR_TEST
  Door door1 = Door();
  door1.rect = {50, 50, 100, 100};
  //Have file with entire layout and such.
  //Make list of rects for walls, doors, etc.
  //Draw by stepping through lists

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
          else
          {
            if (menu_type == "main")
            {
              switch(cursor)
              {
                case 0:
                  cursor = 3;
                  break;
                case 1:
                  cursor = 4;
                  break;
                case 2:
                  cursor = 5;
                  break;
                case 3:
                  cursor = 0;
                  break;
                case 4:
                  cursor = 1;
                  break;
                case 5:
                  cursor = 2;
                  break;
              }
            }
            else if (menu_type == "inv")
            {
              //Unused
            }
            else if (menu_type == "inv2")
            {
              case 0:
                cursor = 1;
                break;
              case 1:
                cursor = 2;
                break;
              case 2:
                cursor = 0;
                break;
            }
          }
          break;

        case SDLK_RIGHT:
          if (menu == 0)
            if (SDL_HasIntersection(&pc_rect, &(door1.rect)) == SDL_FALSE)    //DOOR_TEST
              pc.x += 10;
            else if (SDL_HasIntersection(&pc_rect, &(door1.rect)) == SDL_TRUE && door1.state == "open")
              pc.x += 10;
          else
          {
            if (menu_type == "main")
            {
              switch(cursor)
              {
                case 0:
                  cursor = 1;
                  break;
                case 1:
                  cursor = 2;
                  break;
                case 2:
                  cursor = 0;
                  break;
                case 3:
                  cursor = 4;
                  break;
                case 4:
                  cursor = 5;
                  break;
                case 5:
                  cursor = 3;
                  break;
              }
            }
            else if (menu_type == "inv")
            {
              switch(cursor)
              {
                case 0:
                  if (pc.inventory[0] == "none")
                    hud_rect = {0, 0, 0, 0};
                  else
                    cursor = 1;
                  break;

                case 1:
                  cursor = 2;
                  break;
                case 2:
                  cursor = 3;
                  break;
                case 3:
                  cursor = 0;
                  break;
              }
            }
            else if (menu_type == "inv2")
            {
              //Unused
            }
          }
          break;

        case SDLK_LEFT:
          if (menu == 0)
            pc.x -= 10;
          else
          {
            if (menu_type == "main")
            {
              switch(cursor)
              {
                case 0:
                    cursor = 2;
                  break;
                case 1:
                  cursor = 0;
                  break;
                case 2:
                  cursor = 1;
                  break;
                case 3:
                  cursor = 5;
                  break;
                case 4:
                  cursor = 3;
                  break;
                case 5:
                  cursor = 4;
                  break;
              }
            }
            else if (menu_type == "inv")
            {
              switch(cursor)
              {
                case 0:
                  if (pc.inventory[0] == "none")
                    hud_rect = {0, 0, 0, 0};
                  else
                    cursor = 3;
                  break;
                case 1:
                  cursor = 0;
                  break;
                case 2:
                  cursor = 1;
                  break;
                case 3:
                  cursor = 2;
                  break;
              }
            }
            else if (menu_type == "inv2")
            {
              //Unused
            }
          }
          break;

        case SDLK_UP:
          if (menu == 0)
            pc.y -= 10;
          else
          {
            if (menu_type == "main")
            {
              switch(cursor)
              {
                case 0:
                  cursor = 3;
                  break;
                case 1:
                  cursor = 4;
                  break;
                case 2:
                  cursor = 5;
                  break;
                case 3:
                  cursor = 0;
                  break;
                case 4:
                  cursor = 1;
                  break;
                case 5:
                  cursor = 2;
                  break;
              }
            }
            else if (menu_type == "inv")
            {
              //Unused
            }
            else if (menu_type == "inv2")
            {
              switch(cursor)
              {
                case 0:
                  cursor = 2;
                  break;
                case 1:
                  cursor = 0;
                  break;
                case 2:
                  cursor = 1;
                  break;
              }
            }
          }
          break;

        case SDLK_ESCAPE:
          quit = 1;
          break;

        case SDLK_z:
          //Interact flag toggle
          if (menu == 0)
          {
            //Interact button?
            //DOOR_TEST
            if (abs(pc.y - door1.rect.y) <= 100 && pc.x == door1.rect.x) //If next to door...
            {
              if(door1.state == "closed")
                door1.state = "open";
              else
                door1.state = "closed";
              cout << door1.state <<" " <<pc.y << " " << door1.rect.y << abs(pc.y - door1.rect.y)  <<endl;
            }
          }
          else
          {
            if (menu_type == "main")
            {
              switch(cursor)
              {
                case 0:
                  menu_type = "inv";
                  cursor = 0;
                  break;
              }
            }
            else if (menu_type == "inv")
            {

            }
          }
          break;

        case SDLK_x:
          //Inventory flag toggle
          if (menu == 0)
          {
            menu = 1;
          }
          else
          {
            if (menu_type == "main")
            {
              menu = 0;
            }
            else if (menu_type == "inv")
            {
              menu_type = "main";
              cursor = 0;
            }
          }
          break;
      }
    }

    //Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //Draw Room
    if (door1.state == "closed")
      SDL_BlitSurface(door, NULL, screenSurface, &(door1.rect));

    //Draw Player
    pc_rect = {pc.x, pc.y, 100, 100};
    SDL_BlitSurface(g, NULL, screenSurface, &pc_rect);
    SDL_UpdateWindowSurface(window);

    //Draw Other Players(s)

    ///
    //Draw HUD-related
    ////
    //Menu (REPLACE WITH FUNCTION)
    if (menu == 1)
    {
      //////////
      //HUD Black Background
      /////////
      hud_rect = {0, 450, 1280, 500};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
      ///////////
      //Profile Image
      ///////////
      hud_rect = {50, 500, 200, 200};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xBB, 0xFF));

      if (menu_type == "main")
      {
        /////////
        //Cursor
        /////////
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
            hud_rect = {390, 615, 270, 120};
            break;
          case 4:
            hud_rect = {665, 615, 270, 120};
            break;
          case 5:
            hud_rect = {940, 615, 270, 120};
            break;
        }
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xE3, 0x86, 0x34));

        /////////
        //menu slot background
        ////////
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
      else if (menu_type == "inv")
      {
        /////////
        //Cursor
        /////////
        switch(cursor)
        {
          case 0:
            if (pc.inventory[0] == "none")
              hud_rect = {0, 0, 0, 0};
            else
              hud_rect = {337, 510, 200, 200};
            break;
          case 1:
            hud_rect = {537, 510, 200, 200};
            break;
          case 2:
            hud_rect = {737, 510, 200, 200};
            break;
          case 3:
            hud_rect = {937, 510, 200, 200};
            break;
        }
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xE3, 0x86, 0x34));

        /////////
        //menu slot background
        ////////
        //Menu Slots
        ///////
        hud_rect = {350, 525, 175, 175};
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        //Actual Menu Image

        hud_rect = {550, 525, 175, 175};
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        //Actual Menu Image

        hud_rect = {750, 525, 175, 175};
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        //Actual Menu Image

        hud_rect = {950, 525, 175, 175};
        SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        //Actual Menu Image


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

        //INV2 SLOT BACKGROUNDS
      }

      //Text boxes
    }



    //Clear everything? / Renderer?
    }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;

}
