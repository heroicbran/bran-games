using namespace std;

struct Item
{
  string name;
  int item_id;
  string sprite;
  int x;
  int y;

  MSGPACK_DEFINE_ARRAY(name, item_id, sprite, x, y);  //Note: Needed to make RPC function with custom type.*/

  Item()
  {

  }
  Item(string n, int ii, string s, int xx, int yy) : name{n}, item_id{ii}, sprite{s}, x{xx}, y{yy}
  {}
};

//Keys just need to be inv to open doors

//Notes have messages you may examine.

//Make a flashlight? Maybe.
