#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct Wall
{
  //string name = "wall";
  //string sprite = "w.png"; : public Wall
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
  int state = 0; //0 = closed, 1 = open
  int locked = 0; //0= unlocked
  string sprite = "door";
  int x;
  int y;

  int toggle_door()
  {
    if (state == 0)
    {
      state == 1;
      //Change sprite
    }
    else
    {
      state == 0;
      //Change sprite
    }
    return state;
  }

  int close_door()
  {
    state == 0;
    //Change sprite
    return state;
  }

  int open_door()
  {
    state == 1;
    //Change sprite
    return state;
  }

  Door()
  {

  }

  Door(int i, int s, int l, string sp, int xx, int yy) : id{i}, state{s}, locked{l}, sprite{sp}, x{xx}, y{yy}
  {

  }

  MSGPACK_DEFINE_ARRAY(id, state, locked, sprite, x, y);  //Note: Needed to make RPC function with custom type.

};
