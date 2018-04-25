#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include "rpc/server.h"
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
map<string, Room>room_list;

string test_func(string name)
{
  Mob* newMob = new Mob(name);

  if (mob_list.find(name) == mob_list.end())
    mob_list[name] = *newMob;
  return "confirmation";
}

void check_mobs()
{

}

void check_rooms()
{

}


int get_id()
{
  //cout << "Peer " <<++pcount <<" has connected!" <<endl;
  return 0;
}

int type_select()
{
  int sel;
  cout << "Select operation mode (Server = 1, Peer = 2): ";
  cin >> sel;
  return sel;

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


  select = type_select();
  //Initialize Rooms (or Load previous state)


  //Process for server
  cout << "This process will operate as the Server." <<endl <<endl;
  //cout << "Select the port that will be used for listening: ";
  //cin >> port;
  //cout << endl;
  cout << "The server is now active." <<endl;

  //Set up server, bind each of the commands for peer
  rpc::server server(port);
  server.bind("test", &test_func);
  //Update Mob
  //Update room (with lock)
  server.async_run(1);


  //Initialize Game State (Rooms)
  Room testRoom = Room();

  while(quit == 0)
  {
    cin >> quit; //Just blocks.
  }
    //Initialize Mobs Upon Connect




  cout << "The process has ended." <<endl <<endl;
  return 0;
}
