#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct Wall
{
  //string name = "wall";
  //string icon = "w.png"; : public Wall
  SDL_Rect rect;

  Wall(int x, int y)
  {
    rect.x = x;
    rect.y = y;
  }
};

struct Door
{
  int id;
  int state = 0; //0 = closed, 1 = open
  string icon = "door.png";
  SDL_Rect rect;

  int toggle_door()
  {
    if (state == 0)
    {
      state == 1;
      //Change icon
    }
    else
    {
      state == 0;
      //Change icon
    }
    return state;
  }

  int close_door()
  {
    state == 0;
    //Change icon
    return state;
  }

  int open_door()
  {
    state == 1;
    //Change icon
    return state;
  }

  Door(int i, string ic, SDL_Rect r, int s) : id{i}, icon{ic}, rect{r}, state{s}
  {

  }
};
