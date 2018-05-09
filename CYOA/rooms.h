//#include "objects.h"
using namespace std;

struct Room
{
  int id;
  string room_name = "test";
  string background;      //Drawn image for background;
  vector<Wall> wall_list;
  vector<Door> door_list; //Key = id, value = state
  //vector<Tile>tile_list;
  vector<Item> item_list; //Key = name, value = quantity available
  bool change_lock = false;  //Lock to keep room updates from happening

  MSGPACK_DEFINE_ARRAY(id, room_name, background, wall_list, door_list, item_list, change_lock);  //Note: Needed to make RPC function with custom type.


};

//Room_Lite Struct
