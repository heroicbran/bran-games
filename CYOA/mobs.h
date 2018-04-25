struct Mob
{
  string name;
  int x;
  int y;
  vector<string> inventory;
  int current_room = 0; //Room being occupied by mob
  //int is_player = 0; //Used for PC
  int player_id;
  MSGPACK_DEFINE_ARRAY(name, x, y, inventory, current_room, player_id);  //Note: Needed to make RPC function with custom type.

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
