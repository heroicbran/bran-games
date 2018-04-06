struct Mob
{
  string name;
  int x;
  int y;
  vector<string> inventory;
  int room_id = 0; //Room being occupied by mob
  int is_player = 0; //Used for PC

  Mob() : name{"test"}, x{0}, y{0}
  {

  }

  Mob(string n, int posx, int posy) : name{n}, x{posx}, y{posy}
  {

  }
};
