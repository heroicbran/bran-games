struct Mob
{
  string name;
  int hp = 100;
  int x;
  int y;
  int frame = 0;
  string sprite = "g";
  vector<string> inventory;
  string current_room = "first"; //Room being occupied by mob
  //int is_player = 0; //Used for PC
  int player_id;
  MSGPACK_DEFINE_ARRAY(name, hp, x, y, frame, sprite, inventory, current_room, player_id);  //Note: Needed to make RPC function with custom type.

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
