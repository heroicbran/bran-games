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
  string name = "null";


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


struct Weapon
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

  string weapon_ability = "none";

  void attack(rpc::client &client, Mob &pc)
  {
     //Asks the server to create an attack ability with proper stats attached and proper dir of user (RPC call?)
     cout << "K call" <<endl;
     client.call("create_ability", pc, 100);
  }

  MSGPACK_DEFINE_ARRAY(name, type, level, upgrade_exp, max_exp, wep_atk, ele_bonus);


};

struct AllyMon
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

  //Has an array of ability ids
  vector<int> abilities = {102, 0, 0, 0};

  void attack(rpc::client &client, Mob &pc)
  {
    use_ability(1, client, pc);
  }

  void use_ability(int ability_number, rpc::client &client, Mob &pc)
  {
    switch(ability_number)
    {
      case 1:
        cout << "BASH" <<endl;
        client.call("create_ability", pc, abilities[0]);
        break;

      case 2:
        break;
    }
   //1 is always attack

  }


  MSGPACK_DEFINE_ARRAY(name, type, level, bond_level, bond_exp, mp, matk, mdef);

};

struct Player : public Mob
{
  MobType mob_type = player;

  //Modified Stats

  //Equipment Vars
  string armor;
  string accessory1;
  string accessory2;



  int curr_mon = 0;

  //List of weapon + 3 main monsters
  Weapon weapon;
  vector<AllyMon> monster_list; //Includes weapon (0) and ally monsters (1-3)
  vector<AllyMon> full_mon_list;

  //List of 10 reserve monsters (will increase limit as we go?)


  MSGPACK_DEFINE_ARRAY(name, hp_points, atk_points, def_points, char_points, level, levelup_points, experience, max_hp, hp, atk, def,
    ele_weak, ele_strong, ele_block, x, y, w, h, dir, sprite_frame, sprite, inventory, current_room, player_id, weapon, armor, accessory1, accessory2, curr_mon, weapon, monster_list, full_mon_list);  //Note: Needed to make RPC function with custom type.


   Player()
   {
    //  Weapon* new_weapon = new Weapon("Pocket Knife");
    //  offense_select_list.push_back(*new_weapon);
    //  cout << "con1" <<endl;
   }

   Player(string name) : Mob(name)
   {
     //make 1 weapon, 3 ally_mon as place holders (for tests)
      // Weapon* new_weapon = new Weapon("Pocket Knife");
      // offense_select_list.push_back(*new_weapon);
      // cout << "con2" <<endl;

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
     //Change curr_mon (check # of monsters)
     //Call to update player mob
     if (curr_mon < 3)
        curr_mon++;
     else
        curr_mon = 0;

    cout << "CURR: "<< curr_mon << endl;
   }

   //J
   void inspect()
   {

   }

   // I
   void use_item()
   {

   }

   // L
   void talk()
   {

   }

   //K key = 1, J key = 2, L key = 3, I key = 4
   void call_action(int action_number, rpc::client &client)
   {
      cout << "1" <<endl;
      if(curr_mon == 0)
      {
        switch(action_number)
        {
          case 1:
            cout << "2" <<endl;
            cout << "OS size: " << this->monster_list.size() <<endl;
            if (weapon.name != "none")
            {
              cout << "3" <<endl;
              weapon.attack(client, *this);
            }
            break;
          case 2:
            //inspect
          case 3:
            //talk
          case 4:
            //inventory
          default:
            break;
        }
      }
      /*else if (curr_mon > 0 && offense_select_list.size() > 1)
      {
          offense_select_list[curr_mon].use_ability(action_number);
      }*/

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
