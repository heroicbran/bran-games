#ifndef MOBS_H
#define MOBS_H

//#include<vector>
using namespace std;

struct Mob
{

  //Character Info
  string name = "null";
  char sex;

  //Other Info
  int x;
  int y;
  int w = 50;
  int h = 64;

  string role; //Innocent, Killer, Clue_Killer

  //Add color options
  int skin = 0;
  int hair = 0;
  int shirt = 0;
  int bottoms = 0;

  char dir = 'D';
  int sprite_frame = 0; //Frames 0 - 3.
  string sprite = "human_base";
  vector<Item> inventory;   //inventory
  int tokens = 0;
  string current_room = "test"; //Room being occupied by mob
  //int is_player = 0; //Used for PC
  int player_id = 0;
  int mob_type = 0; //0 is player, 1 is bot
  bool host = false;
  MSGPACK_DEFINE_ARRAY(name, sex, x, y, w, h, role, skin, hair, shirt, bottoms,
       dir, sprite_frame, sprite, inventory, tokens, current_room, player_id, mob_type, host);  //Note: Needed to make RPC function with custom type.

  Mob(string n) : name{n}, x{0}, y{0}
  {

  }

  Mob(string n, int posx, int posy) : name{n}, x{posx}, y{posy}
  {

  }

  Mob(string n, char s, int sk, int ha, int sh, int bo) : name(n), sex(s)
  {}

  Mob() : x{0}, y{0}
  {

  }

  //Z Key
  void interact()
  {

  }
};



#endif
