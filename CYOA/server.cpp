#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include "rpc/server.h"
#include "rpc/client.h"
#include "rpc/this_session.h"
#include "rpc/this_server.h"
#include <dirent.h>
#include <chrono>

#include "rooms.h"
#include "mobs.h"
//#include "objects.h"
#include "network.h" //Functions for actions over network
#include "inventory.h"

using namespace std;

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
  //cout << mob_list[pc.name].name;// << " updated: " << mob_list[pc.name].x << " " << mob_list[pc.name].y <<endl;
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
  server.bind("get_mobsize", &get_mobsize);
  server.bind("get_mobs", &get_mobs);

  server.async_run(1);
  cout << "The server is now active." <<endl;


  //Initialize Game State (Rooms)
  Room testRoom = Room();
  room_list["test_room"] = testRoom;

  while(quit == 0)
  {
    cin >> quit; //Just blocks.
  }
    //Initialize Mobs Upon Connect




  cout << "The process has ended." <<endl <<endl;
  return 0;
}
