#include <fstream>
#include <string>
////////////////
// Room Functions
//////////////////

Room setup_room(string name) //Argument is room file name
{
  //Read room from file and add them to room vector
  string buffer;
  ifstream reader;
  reader.open("rooms/test");
  int id;
  Room* new_room = new Room();
  while(reader >> buffer)
  {

    switch(buffer[0])
    {
      case '#':
        reader >> new_room->id;
        break;
      case 'n':

        break;
      case 'w':
        int x;
        reader >> x;
        int y;
        reader >> y;
        Wall* new_wall = new Wall(x, y);
        new_room->wall_list.push_back(*new_wall);

        //reader >> new_room.;
        //re
        break;
    }
  }

  return *new_room;









}

void update_items(int room_id, string item_name, int action, map<int, Room> &room_list) //action is 1 = obtain, 0 = dropped
{
  //Read rooms from file and add them to room vector
  if (action == 1)
    (room_list[room_id].item_list[item_name])--;
  else
    (room_list[room_id].item_list[item_name])++;
}

void update_doors(int room_id, int door_id)
{
  //Read rooms from file and add them to room vector
}

////////////////
// Mob Functions
//////////////////

Mob setup_mob(string name)
{
  //Create a player mob, add to mob vector, and pass to client
  Mob* new_mob = new Mob(name, 100, 100);
  return *new_mob;
}

void update_mob(Mob &player, map<int, Mob> &mob_list)
{
  //Pass copy of Mob from client to server. Replace server's with it. (Type mismatch?)
  mob_list[player.player_id] = player;
}
