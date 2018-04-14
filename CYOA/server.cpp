#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include "rpc/client.h"
#include "rpc/server.h"
#include "rpc/this_session.h"
#include "rpc/this_server.h"
#include <dirent.h>
#include <chrono>

#include "rooms.h"
#include "mobs.h"
//#include "objects.h"
#include "network.h"
#include "inventory.h"

using namespace std;

vector<Mob> mob_list;
vector<Room>room_list;
//Maps for mob list and room list

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

void setup_rooms()
{
  //Read rooms from file and add them to room vector
}

void setup_mob()
{
  //Create a player mob and add to mob vector
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
  if (select == 1)
  {
    cout << "This process will operate as the Server." <<endl <<endl;
    //cout << "Select the port that will be used for listening: ";
    //cin >> port;
    //cout << endl;
    cout << "The server is now active." <<endl;

    //Set up server, bind each of the commands for peer
    rpc::server server(port);
    //server.bind("registry", &registry);
    //Update Mob
    //Update room (with lock)
    server.async_run(1);

    while(quit == 0)
    {
      cin >> quit; //Just blocks.
    }
      //Initialize Mobs Upon Connect
  }



  cout << "The process has ended." <<endl <<endl;
  return 0;
}
