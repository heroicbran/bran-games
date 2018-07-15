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

  enum StatConstants
  {
    max_level = 100,
    max_levelup_points = 2,
    experience_point_increaser = 2,
    min_points = 4,
    max_points = 50,

    //Bonuses per point
    hp_bonus = 25,
    atk_bonus = 2,
    def_bonus = 2,
    cha_bonus = 2
  };
  //Character Info
  string name;

  //Stat Points
  int hp_points = min_points;
  int atk_points = min_points;
  int def_points = min_points;
  int char_points = min_points;

  //Equipment Bonuses
  //Player only?

  //Battle Stats
  int level = 1;
  int levelup_points = 0;
  int experience = 0;
  int max_hp = hp_bonus * hp_points;
  int hp = max_hp;
  int atk = atk_bonus * atk_points;
  int def = def_bonus * def_points;

  //        Ele Array Key
  // 8            7     6      5      4      3          2       1       0
  //Physical    fire   ice   earth   wind   electric   light   death   status
  int ele_weak = 0x0ul;
  int ele_strong = 0x0ul;
  int ele_block = 0x0ul;


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
  bool targetable = false; //For NPC who do not fight or when player and monsters chatting
  MSGPACK_DEFINE_ARRAY(name, hp_points, atk_points, def_points, char_points, level, levelup_points, experience, max_hp, hp, atk, def,
    ele_weak, ele_strong, ele_block, x, y, w, h, dir, sprite_frame, sprite, inventory, current_room, player_id);  //Note: Needed to make RPC function with custom type.

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

struct NPC : public Mob
{
  MobType mob_type = npc;

};

struct AllyMon
{
  //Stats
  string name;
  int level = 1;
  int bond_level = 1;
  int bond_exp = 0; //Increases bond level at 100

  int mp = 50;
  int matk = 5;
  int mdef = 5;

  //        Ele Array Key
  // 8            7     6      5      4      3          2       1       0
  //Physical    fire   ice   earth   wind   electric   light   death   status
  int ele_weak = 0x0ul;
  int ele_strong = 0x0ul;
  int ele_block = 0x0ul;

  AllyMon()
  {

  };

  void use_ability(int ability_number)
  {

  }


  MSGPACK_DEFINE_ARRAY(name, level, bond_level, bond_exp, mp, matk, mdef);

};

struct Player : public Mob
{
  MobType mob_type = player;

  //Modified Stats

  //Equipment Vars
  string weapon;
  string armor;
  string accessory1;
  string accessory2;

  //List of 3 main monsters
  enum mon_select
  {
    none = 0,
    one,
    two,
    three
  };

  int curr_mon = none;

  vector<AllyMon> ally_mon_list;
  vector<AllyMon> full_mon_list;

  //List of 10 reserve monsters (will increase limit as we go?)


  MSGPACK_DEFINE_ARRAY(name, hp_points, atk_points, def_points, char_points, level, levelup_points, experience, max_hp, hp, atk, def,
    ele_weak, ele_strong, ele_block, x, y, w, h, dir, sprite_frame, sprite, inventory, current_room, player_id, weapon, armor, accessory1, accessory2, curr_mon, ally_mon_list, full_mon_list);  //Note: Needed to make RPC function with custom type.


   Player(string name) : Mob(name)
   {
     return;
   }

   //F Key
   void interact()
   {

   }

   //H key
   void change_action_set()
   {

   }

   void attack()
   {

   }

   void inspect()
   {

   }


   void use_item()
   {

   }


   void talk()
   {

   }

   //K key = 1, J key = 2, L key = 3, I key = 4
   void call_action(int action_number)
   {
      if(curr_mon == 0)
      {
        switch(action_number)
        {
          case 1:
            attack();
            break;
          case 2:
          case 3:
          case 4:
        }
      }
      else
      {
        ally_mon_list[curr_mon].use_ability(action_number);
      }
   }



};

struct Monster : public Mob
{
  enum Personality
  {
    empty = 0,
    aggressive,
    timid,
    wise,
    bubbly,
    childish,
    macho,
    unintelligent,
    sly
  };

  MobType mob_type = monster;
  Personality behavior = empty;
  //Character Info
  string name = "test_mon";


  //Stat Points
  int hp_points = min_points;
  int atk_points = min_points;
  int def_points = min_points;
  int char_points = min_points;

  //Equipment Bonuses
  //Player only?

  //Battle Stats
  int level = 1;
  int max_hp = hp_bonus * hp_points;
  int hp = max_hp;
  int atk = atk_bonus * atk_points;
  int def = def_bonus * def_points;

  //        Ele Array Key
  // 8            7     6      5      4      3          2       1       0
  //Physical    fire   ice   earth   wind   electric   light   death   status
  int ele_weak = 0xFul;
  int ele_strong = 0x0ul;
  int ele_block = 0x0ul;


  //Other Info
  int x = 75;
  int y = 75;
  int w = 50;
  int h = 50;
  char dir = 'D';
  int sprite_frame = 0; //Frames 1 - 4.
  string sprite = "shadow";
  //vector<Item> inventory;   //TODO: replace with loot drops?
  string current_room = "test"; //Room being occupied by mob

  void find_target()
  {

  }

  void call_monster_action(int action_number) //1 - 4
  {

  }

  void do_monster_actions()
  {

  }

};

#endif
