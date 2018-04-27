#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "rpc/client.h"
#include "images.h"
using namespace std;
#include "mobs.h"
#include "inventory.h"
#include "objects.h"
#include "rooms.h"
#include "input.h"
//#include "network.h"
#include "menu.h"



const int s_width = 1280;
const int s_height = 760;

int initialize_player()
{

  return 1;
}

int initialize_SDL(SDL_Window* &window, SDL_Surface* &screenSurface)
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

//Load all potential images into surfaces and places them into a map
void load_images(map<string, SDL_Surface*> &images)
{
  //Make a loop and used the file names?
  SDL_Surface* g = new SDL_Surface;
  g = IMG_Load("images/g.png");
  images["g"] = g;

  SDL_Surface* img = new SDL_Surface ;
  img = IMG_Load("images/cursor.png");
  images["img"] = img;

  SDL_Surface* door = new SDL_Surface;
  door = IMG_Load("images/door.png");
  images["door"] = door;

}

/*void draw_player(SDL_Surface* img, SDL_Su)
{
  SDL_BlitSurface(img, NULL, screenSurface, &rect);
}*/

int main()
{
  string name;
  int menu = 0; // Menu flag
  string menu_type = "main"; // "main (2x3)", "inv (1x4)", "inv2 (3x1 use/combine/examine/trade)"
  int cursor = 0; // main (0,1,2/3,4,5), inv(0,1,2,3), inv2(0,1,2)
  int inv = 0; //Inventory flag
  int inter = 0; //Interact flag
  int quit = 0;
  int port = 10000;
  SDL_Event evt;
  SDL_Window* window;
  SDL_Surface* screenSurface;
  map<string, SDL_Surface*> images;
  vector<Wall> room_walls;
  Room pc_room;
  SDL_Rect door;
  vector<SDL_Rect> doors;
  //vector<Item> items;

  //1 grid spot is 50x50 pixels

  //Set up network stuff
  rpc::client client("127.0.0.1", port);
  cout << "Enter your name: ";
  cin >> name;

  //Setup Images
  initialize_SDL(window, screenSurface);
  load_images(images);


  //Set up Player Stuff
  Mob pc = client.call("add_player", name).as<Mob>();    //Retrieves initial player data
  Mob otherpc;

  if (pc.name.length() > 0)
    cout << pc.name << " has been added." << endl;

  //PC Inventory
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");
  pc.inventory.push_back("none");

  SDL_Rect pc_rect = {pc.x, pc.y, 100, 100};;
  SDL_Rect hud_rect;

  //DOOR_TEST
  //Door door1 = Door();
  //door1.rect = {50, 50, 100, 100};

  //Room Initialization
  pc_room = client.call("get_room", pc.current_room).as<Room>(); //Gets the room (Also happens upon room change)
  room_walls = pc_room.wall_list;               //Get walls for room


  while(!quit)
  {
    SDL_UpdateWindowSurface(window);
    SDL_WaitEvent(&evt);


    if(evt.type == SDL_QUIT)
      quit = 1;

    //Do special events/cutscenes?

    process_input(cursor, evt, pc, menu, menu_type, pc_rect, hud_rect, quit, client);

    //Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //Draw Room (loop through items, doors)
    pc_room = client.call("get_room", pc.current_room).as<Room>();
    doors.clear();
    for (int j = 0; j < pc_room.door_list.size(); j++)
    {
        door = {pc_room.door_list[j].x, pc_room.door_list[j].y, 100, 100};
        doors.push_back(door);
        SDL_BlitSurface(images[pc_room.door_list[j].sprite], NULL, screenSurface, &door);
    }


    //items = pc_room.item_list;
    //loop to draw items and rects and stuff

    //Draw Player
    pc_rect = {pc.x, pc.y, 100, 100};
    SDL_BlitSurface(images[pc.sprite], NULL, screenSurface, &pc_rect);
    //SDL_UpdateWindowSurface(window);

    //Draw Other Players(s)
    int count = client.call("get_mobsize").as<int>();
    int i = 1;
    while(i <= count)
    {
      otherpc = client.call("get_mobs", (i-1)).as<Mob>();
      if (pc.name != otherpc.name)
      {
        //cout << "draw other" <<endl;
        pc_rect = {otherpc.x, otherpc.y, 100, 100};
        SDL_BlitSurface(images[otherpc.sprite], NULL, screenSurface, &pc_rect);

      }
      i++;
    }

    //for(map<string, Mob>::iterator i = ; )

    //Draw HUD-related
    draw_menu(cursor, menu, menu_type, hud_rect, pc, screenSurface);

    //Clear everything? / Renderer?
  }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;

}
