#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "objects.cpp"
using namespace std;

struct Room
{
  int room_id;
  string room_name;
  vector<Wall> wall_list;
  vector<Door> door_list;
  //vector<Tile>tile_list;
  //vector<Item> item_list;
};
