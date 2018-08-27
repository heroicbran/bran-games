#ifndef MOBS_H
#define MOBS_H

//#include<vector>
using namespace std;

struct Mob
{
  enum MobType
  {
    player = 0,
    monster = 1,
    npc = 2
  };

  //Character Info
  string name = "null";


  //Other Info
  int x;
  int y;
  int w = 50;
  int h = 64;
  char dir = 'D';
  int sprite_frame = 0; //Frames 1 - 4.
  string sprite = "human_base";
  vector<Item> inventory;   //inventory
  string current_room = "test"; //Room being occupied by mob
  //int is_player = 0; //Used for PC
  int player_id;
  MobType mob_type;
  MSGPACK_DEFINE_ARRAY(name, x, y, w, h, dir, sprite_frame, sprite, inventory, current_room, player_id, mob_type);  //Note: Needed to make RPC function with custom type.

  Mob(string n) : name{n}, x{0}, y{0}
  {

  }

  Mob(string n, int posx, int posy) : name{n}, x{posx}, y{posy}
  {

  }

  Mob() : x{0}, y{0}
  {

  }


};
#endif
