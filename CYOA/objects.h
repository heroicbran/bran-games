#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct Wall
{
  string sprite = "";
  int x;
  int y;
  int w;
  int h;

  Wall(int xx, int yy) : x{xx}, y{yy}
  {

  }

  Wall(int xx, int yy, int ww, int hh) : x{xx}, y{yy}, w{ww}, h{hh}
  {

  }

  Wall()
  {

  }

  MSGPACK_DEFINE_ARRAY(sprite, x, y, w, h);  //Note: Needed to make RPC function with custom type.

};

struct Door
{
  int id;
  int open = 0; //0 = closed, 1 = open
  int locked = 0; //0= unlocked
  string sprite = "door";
  int x;
  int y;
  int w;
  int h;
  //Warp Door coordinates and new room location.
  char type = 'n';  //n for normal or w for warp
  int wx;
  int wy;
  string wroom;

  int toggle_door()
  {
    if (open == 0)      //TODO: Add if check for different door direction sprites
    {
      open = 1;
      sprite = "door_open";
    }
    else if (open == 1)
    {
      open = 0;
      sprite = "door";
    }
    return open;
  }

  int close_door()
  {
    open == 0;
    //Change sprite
    return open;
  }

  int open_door()
  {
    open == 1;
    //Change sprite
    return open;
  }

  void warp_door(Mob &pc)
  {
    pc.x = wx;
    pc.y = wy;
    pc.current_room = wroom;
  }


  Door()
  {

  }

  Door(int i, int o, int l, string sp, int xx, int yy, int ww, int hh) : id{i}, open{o}, locked{l}, sprite{sp}, x{xx}, y{yy}, w{ww}, h{hh}
  {

  }

  MSGPACK_DEFINE_ARRAY(id, open, locked, sprite, x, y, w, h, type, wx, wy, wroom);  //Note: Needed to make RPC function with custom type.

};
