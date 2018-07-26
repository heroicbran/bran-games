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

struct OffenseSelect
{
   void attack(){}
   void use_ability(int ability_number){}
   MSGPACK_DEFINE_ARRAY();
};

struct Weapon : public OffenseSelect
{
  //Stats
  string name;
  string type = "weapon";

  //for weapon upgrades
  int level = 1;
  int upgrade_exp = 0; //Increases upgrade level at 100
  int max_exp = 100;
  int wep_atk = 5;

  //        Ele Array Key
  // 8            7     6      5      4      3          2       1       0
  //Physical    fire   ice   earth   wind   electric   light   death   status
  int ele_bonus = 0x100ul;

  Weapon()
  {}

  Weapon(string n) : name(n)
  {

  }

  string ability = "none";

  void attack()
  {
     //Asks the server to create an attack ability with proper stats attached and proper dir of user
  }

  MSGPACK_DEFINE_ARRAY(name, type, level, upgrade_exp, max_exp, wep_atk, ele_bonus);


};

struct AllyMon : public OffenseSelect
{
  //Stats
  string name;
  string type = "ally_mon";

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
  {}

  AllyMon(string n) : name(n)
  {
    return;
  }
  //Different constructor that reads ability list from somewhere. File?

  vector<string> abilities = {"none", "none", "none", "none"};

  void use_ability(int ability_number)
  {

  }


  MSGPACK_DEFINE_ARRAY(name, type, level, bond_level, bond_exp, mp, matk, mdef);

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



  int curr_mon = 0;

  //List of weapon + 3 main monsters

  vector<OffenseSelect> offense_select_list; //Includes weapon (0) and ally monsters (1-3)
  vector<AllyMon> full_mon_list;

  //List of 10 reserve monsters (will increase limit as we go?)


  MSGPACK_DEFINE_ARRAY(name, hp_points, atk_points, def_points, char_points, level, levelup_points, experience, max_hp, hp, atk, def,
    ele_weak, ele_strong, ele_block, x, y, w, h, dir, sprite_frame, sprite, inventory, current_room, player_id, weapon, armor, accessory1, accessory2, curr_mon, offense_select_list, full_mon_list);  //Note: Needed to make RPC function with custom type.


   Player(string name) : Mob(name)
   {
     //make 1 weapon, 3 ally_mon as place holders (for tests)
    //  Weapon* new_weapon = new Weapon("none");
    //  offense_select_list.push_back(*new_weapon);
    //  AllyMon* new_a_mon = new AllyMon("none");
    //  offense_select_list.push_back(*new_a_mon);
    //  offense_select_list.push_back(*new_a_mon);
    //  offense_select_list.push_back(*new_a_mon);
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
   void call_action(string player_name, int action_number)
   {
      if(curr_mon == 0)
      {
        switch(action_number)
        {
          case 1:
            if (offense_select_list.size() > 0)
            {
              offense_select_list[0].attack();
            }
            break;
          case 2:
          case 3:
          case 4:
          default:
            break;
        }
      }
      else if (curr_mon > 0 && offense_select_list.size() > 1)
      {
          offense_select_list[curr_mon].use_ability(action_number);
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
  int ele_weak = 0xFFul;
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

  void handle_monster_actions() //add number to decide behavior type?)
  {

  }

};

#endif
