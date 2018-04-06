#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct Door
{
  string name = "door";
  string state = "closed"; //or open
  string icon = "door.png";
  SDL_Rect rect;
};

struct Wall
{
  string name = "wall";
  //string icon = "w.png";
  SDL_Rect rect;
};
