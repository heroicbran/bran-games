#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct Wall
{
  //string name = "wall";
  string sprite = "door";
  int x;
  int y;

  Wall(int a, int b) : x{a}, y{b}
  {

  }

  Wall()
  {

  }

  MSGPACK_DEFINE_ARRAY(x, y);  //Note: Needed to make RPC function with custom type.

};

struct Door
{
  int id;
  int open = 0; //0 = closed, 1 = open
  int locked = 0; //0= unlocked
  string sprite = "door";
  int x;
  int y;

  int toggle_door()
  {
    if (open == 0)
    {
      open == 1;
      //Change sprite
    }
    else
    {
      open == 0;
      //Change sprite
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

  Door()
  {

  }

  Door(int i, int o, int l, string sp, int xx, int yy) : id{i}, open{o}, locked{l}, sprite{sp}, x{xx}, y{yy}
  {

  }

  MSGPACK_DEFINE_ARRAY(id, open, locked, sprite, x, y);  //Note: Needed to make RPC function with custom type.

};

//Warp Door, which inherits door but has a warp x and y. annd new msgpack

struct WarpDoor : public Door {

};
