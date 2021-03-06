#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "rpc/client.h"
#include "images.h"
using namespace std;
#include "inventory.h"
#include "mobs.h"
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
  vector<Wall> room_bounds;
  Room pc_room;
  SDL_Rect door_rect;
  vector<SDL_Rect> door_rects;
  SDL_Rect item_rect;
  vector<SDL_Rect> item_rects;
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
  Player pc = client.call("add_player", name).as<Player>();    //Retrieves initial player data
  Player otherpc;

  if (pc.name.length() > 0)
    cout << pc.name << " has been added." << endl;

  //PC Inventory
  //Starts off as empty inventory

  //Ancillary
  SDL_Rect pc_rect = {pc.x, pc.y, pc.w, pc.h};
  SDL_Rect sprite_rect = {0, 0, pc.w, pc.h};
  SDL_Rect otpc_rect;
  SDL_Rect hud_rect;
  SDL_Rect bg_rect;


  //Room Initialization
  //pc_room = client.call("get_room", pc.current_room).as<Room>(); //Gets the room (Also happens upon room change)
  //room_bounds = pc_room.wall_list;               //Get walls for room


  while(!quit)
  {
    SDL_UpdateWindowSurface(window);
    SDL_WaitEvent(&evt);


    if(evt.type == SDL_QUIT)
      quit = 1;

    //Do special events/cutscenes?

    //User Input
    pc = client.call("sync_player", pc).as<Player>();
    process_input(cursor, evt, pc, menu, menu_type, pc_rect, hud_rect, quit, client, door_rects, item_rects, pc_room.door_list, room_bounds); //TODO: Combine room_bounds + visible walls

    //Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    pc_room = client.call("get_room", pc.current_room).as<Room>(); //Gets the room (Also happens upon room change)
    bg_rect = {0, 0, 1280, 760};
    SDL_BlitSurface(images[pc_room.background], NULL, screenSurface, &bg_rect);

    //Boundaries (temporary)
    room_bounds = pc_room.wall_list;               //Get walls for room
    for(int j = 0; j < room_bounds.size(); j++)
    {

      //TODO: UPDATE WALL TREATMENT TO BE LIKE HOW DOORS WORK.SAVE TO VECTOR AND PASS TO PROCESS INPUT
      SDL_Rect bound_rect;
      bound_rect = {room_bounds[j].x, room_bounds[j].y, room_bounds[j].w, room_bounds[j].h};
      bound_rect.h = 500;
      SDL_Surface* bound = SDL_CreateRGBSurface(0, room_bounds[j].w, room_bounds[j].h, 32, 0, 0, 0, 0);
      SDL_FillRect(bound, NULL, SDL_MapRGB(bound->format, 0x00, 0x00, 0xFF));
      SDL_BlitSurface(bound, NULL, screenSurface, &bound_rect);
    }

    //Walls (Decor)
    //TODO

    //Doors
    pc_room = client.call("get_room", pc.current_room).as<Room>();
    door_rects.clear();
    for (int j = 0; j < pc_room.door_list.size(); j++)
    {
        door_rect = {pc_room.door_list[j].x, pc_room.door_list[j].y, pc_room.door_list[j].w, pc_room.door_list[j].h};
        door_rects.push_back(door_rect);
        SDL_BlitSurface(images[pc_room.door_list[j].sprite], NULL, screenSurface, &door_rect);
    }

    //items
    item_rects.clear();
    for (int ii = 0; ii < pc_room.item_list.size(); ii++)
    {
        item_rect = {pc_room.item_list[ii].x, pc_room.item_list[ii].y, 50, 50};
        item_rects.push_back(item_rect);
        SDL_BlitSurface(images["item_twinkle"], NULL, screenSurface, &item_rect);
    }

    //Draw Player
    pc = client.call("sync_player", pc).as<Player>();
    SDL_BlitSurface(images[pc.sprite], &sprite_rect, screenSurface, &pc_rect);  //TODO: FIX SPRITES

    //Draw Other Players(s)
    pc_room = client.call("get_room", pc.current_room).as<Room>();
    int count = client.call("get_mobsize").as<int>();
    int i = 1;
    while(i <= count)
    { //Check for same room as you
      otherpc = client.call("get_players", (i-1)).as<Player>();
      if (pc.name != otherpc.name)
      {
        //cout << "draw other" <<endl;
        otpc_rect = {otherpc.x, otherpc.y, 100, 100};
        SDL_BlitSurface(images[otherpc.sprite], NULL, screenSurface, &otpc_rect);

      }
      i++;
    }

    //Draw Monster(s)

    //Draw Ability Effects
    pc_room = client.call("get_room", pc.current_room).as<Room>();
    cout << pc_room.ability_list.size() <<endl;
    cout << pc_room.room_name <<endl;
    for (int i = 0; i < pc_room.ability_list.size(); i++)
    {
      cout <<"K draw 2" <<endl;
      Ability ability = pc_room.ability_list[i];
      SDL_Rect ability_rect = {ability.x, ability.y, ability.w, ability.h};
      SDL_BlitSurface(images[ability.sprite], NULL, screenSurface, &ability_rect);
    }

    //Draw HUD-related
    draw_menu(cursor, menu, menu_type, hud_rect, pc, screenSurface, images);
    //Health bar
    //Mana bar
    //Selected OffenseSelect portrait
    //4 Ability icons

  }

  SDL_DestroyWindow(window);
  cout << "QUITTING!" <<endl;
  SDL_Quit();


  return 0;

}
