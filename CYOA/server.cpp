#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
using namespace std;
#include "rpc/server.h"
#include "rpc/client.h"
#include "rpc/this_session.h"
#include "rpc/this_server.h"
#include <dirent.h>
#include <chrono>
#include <sstream>
#include "inventory.h"
#include "mobs.h"
#include "objects.h"
#include "rooms.h"
//#include "network.h" //Functions for actions over network


//Maps for mob list and room list
map<string, Mob> mob_list;
map<string, Room>room_list; //Room ID: Name needed for mob control


Mob add_player(string name)
{
  Mob* newMob = new Mob(name);
  //Logic to determine which images to use

  if (mob_list.find(name) == mob_list.end())
  {
    mob_list[name] = *newMob;
    cout << "New Player: " << mob_list[name].name << endl;
  }
  else
  {
    //Make mob with modified name with num attached?
  }
  return mob_list[name];
}

void check_mobs()
{

}

void check_rooms()
{

}

void player_update(Mob pc)
{
  mob_list[pc.name] = pc;
  cout << mob_list[pc.name].name << " updated: " << mob_list[pc.name].x << " " << mob_list[pc.name].y <<endl;
}

Mob sync_player(Mob pc)
{
  return mob_list[pc.name];
}

int get_mobsize()
{
  return mob_list.size();
}

Mob get_mobs(int pos)
{
  //Step through map and return Mobs at pos
  map<string, Mob>::iterator i = mob_list.begin();
  while(pos-- > 0)
  {
    i++;
  }
  return i->second;

}

Room get_room(string id)
{
  return room_list[id];
}

void use_door(int index, string room_name)
{
  room_list[room_name].door_list[index].toggle_door();
}

Item search_item(int item_id, Mob pc)
{
  Item it;
  for (int i = 0; i < room_list[pc.current_room].item_list.size(); i++)
  {
    if (room_list[pc.current_room].item_list[i].item_id == item_id)
      return room_list[pc.current_room].item_list[i];
  }
  return it;
}

int search_index(int item_id, Mob pc)
{
  for (int i = 0; i < room_list[pc.current_room].item_list.size(); i++)
  {
    if (room_list[pc.current_room].item_list[i].item_id == item_id)
      return i;
  }
  return 0;
}

Mob obtain_item(int item_id, Mob pc) //Change how mob is used?
{
  int i;
  if (mob_list[pc.name].inventory.size() < 4)
  {
    cout << "ROOM Inventory (B4)  Size:" <<room_list[pc.current_room].item_list.size() <<endl;
    cout << "=========" <<endl;
    for(i=0; i < room_list[pc.current_room].item_list.size(); i++)
    cout << room_list[pc.current_room].item_list[i].name <<endl;

    if (search_item(item_id, pc).name.length() > 0)
      mob_list[pc.name].inventory.push_back(search_item(item_id, pc));
    if (room_list[pc.current_room].item_list.size() > 0)
      room_list[pc.current_room].item_list.erase(room_list[pc.current_room].item_list.begin() + search_index(item_id, pc));
    cout << "============" <<endl;
    cout << room_list[pc.current_room].item_list[item_id].name << " obtained" <<endl;
    cout << "============" <<endl;

    cout << endl;
    cout << "Inventory (Server)  Size:" <<mob_list[pc.name].inventory.size() <<endl;
    cout << "=========" <<endl;
      for(i=0; i < mob_list[pc.name].inventory.size(); i++)
        cout << mob_list[pc.name].inventory[i].name <<endl;

    cout << endl;
    cout << "ROOM Inventory (after)  Size:" <<room_list[pc.current_room].item_list.size() <<endl;
    cout << "=========" <<endl;
    for(i=0; i < room_list[pc.current_room].item_list.size(); i++)
      cout << room_list[pc.current_room].item_list[i].name <<endl;
  }
  return mob_list[pc.name];
}

void drop_item()
{}

void setup_room(string room_name)
{
  string buffer;
  char c_buffer[50];
  string entry;
  ifstream file_reader;
  ifstream str_reader;
  vector<string> tokens;
  file_reader.open("rooms/" + room_name);
  int id;

  Room* new_room = new Room();

  while(file_reader.getline(c_buffer, 50))
  {
    buffer = c_buffer;
    stringstream stream (buffer);
    getline(stream, entry, ' '); //Get first char

    switch(entry[0])
    {
      case '#':
        getline(stream, entry, ' ');
        id = stoi(entry);
        break;

      case 'n':
        getline(stream, entry, ' ');
        new_room->room_name = entry;
        break;

      case 'w':
        Wall* new_wall = new Wall();
        getline(stream, entry, ' ');
        new_wall->x = stoi(entry);
        getline(stream, entry, ' ');
        new_wall->y = stoi(entry);
        getline(stream, entry, ' ');
        new_wall->w = stoi(entry);
        getline(stream, entry, ' ');
        new_wall->h = stoi(entry);
        new_room->wall_list.push_back(*new_wall);
        break;

    }
  }
  room_list[new_room->room_name] = *new_room;

}

int main()
{
  string ip;
  int port = 10000;
  int select = 0;
  int quit = 0;
  int peer_id = 0;
  int room_count = 0;
  int mob_count = 0;


  //Process for server

  //Set up server, bind each of the commands for peer
  rpc::server server(port);
  server.bind("add_player", &add_player);
  server.bind("player_update", &player_update);
  server.bind("sync_player", &sync_player);
  server.bind("get_mobsize", &get_mobsize);
  server.bind("get_mobs", &get_mobs);
  server.bind("get_room", &get_room);
  server.bind("use_door", &use_door);
  server.bind("obtain_item", &obtain_item);

  server.async_run(4);
  cout << "The server is now active." <<endl;


  //Initialize Game State (Rooms)

  setup_room("test");
/*  Room testRoom = Room();
  Door d = Door(0, 0, 0, "door", 300, 300, 100, 100);
  testRoom.door_list.push_back(d);

  //Test wall(bound)
  Wall w = Wall(-1,0, 1, 100);
  testRoom.wall_list.push_back(w);

  //Test item
  Item i = Item("test_item", 0, "test_item_portrait", 100, 300);
  testRoom.item_list.push_back(i);

  Item j = Item("test_item2", 1, "test_item_portrait", 100, 50);
  testRoom.item_list.push_back(j);

  room_list["test"] = testRoom;*/

  while(quit == 0)
  {
    cin >> quit; //Just blocks.
  }
    //Initialize Mobs Upon Connect




  cout << "The process has ended." <<endl <<endl;
  return 0;
}
