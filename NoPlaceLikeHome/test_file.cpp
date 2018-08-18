#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;




int main()
{
  string buffer;
  char c_buffer[50];
  string entry;
  ifstream file_reader;
  ifstream str_reader;
  vector<string> tokens;
  file_reader.open("rooms/test");
  int id;
  //Room* new_room = new Room();

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
        cout << id;
        break;

      case 'n':
        getline(stream, entry, ' ');
        cout << entry <<endl;
        break;

      case 'w':
        //reader >> id;
        break;

    }
  }


  return 0;
}
