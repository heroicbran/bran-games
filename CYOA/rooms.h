#include "objects.h"
#include <map>
using namespace std;

struct Room
{
  int id;
  string room_name;
  vector<Wall> wall_list;
  map<int,int> door_list; //Key = id, value = state
  //vector<Tile>tile_list;
  map<string,int> item_list; //Key = name, value = quantity


};
