struct Mob
{
  string name;
  int x;
  int y;
  vector<string> inventory;
  int current_room = 0; //Room being occupied by mob
  //int is_player = 0; //Used for PC
  int player_id;

  Mob(string n) : name{n}, x{0}, y{0}
  {

  }

  Mob(string n, int posx, int posy) : name{n}, x{posx}, y{posy}
  {

  }

  Mob()
  {
    
  }
};
