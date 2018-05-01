struct Item
{
  string name;
  int item_id;

  MSGPACK_DEFINE_ARRAY(name, item_id);  //Note: Needed to make RPC function with custom type.

};

//Keys just need to be inv to open doors

//Notes have messages you may examine.

//Make a flashlight? Maybe.
