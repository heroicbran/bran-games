#include "rpc/client.h"

void process_input(int &cursor, SDL_Event evt, Mob &pc, int &menu, string &menu_type, SDL_Rect &pc_rect, SDL_Rect &hud_rect, int &quit, rpc::client &client, vector<SDL_Rect> door_rects, vector<SDL_Rect> item_rects, vector<Door> doors, vector<Wall> walls)
{

  if(evt.type == SDL_KEYDOWN)
  {
    switch(evt.key.keysym.sym)
    {
      case SDLK_DOWN:
        if (menu == 0)
        {
            SDL_Rect collicheck = pc_rect;
            collicheck.y += 5;
            int canMove = 1;

            //Note: These are bounds + decorative/visible walls
            for (int w = 0; w < walls.size(); w++)
            {
              SDL_Rect wallRect = {walls[w].x, walls[w].y, 100, 100};
              if (SDL_HasIntersection(&collicheck, &wallRect))
                canMove = 0;
            }

            for (int d = 0; d < door_rects.size(); d++)
            {

              if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 1) //open door
              {
                //cout << "branch1 " << endl;
              }
              else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_FALSE)
              {
                //cout << "branch2 " << endl;
              }
              else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 0)
              {
                //cout << "branch3 " << endl;
                canMove = 0;
                //cout << "Open?" << doors[d].open <<endl;
              }
            }
            if (canMove == 1)
            {
              pc.y += 10;
              pc_rect.y += 10;
              client.call("player_update", pc);    //Supplies updated player data
            }
            cout << "PC     " << "PC_R " << " Coll     "   << "DOOR" <<endl;
            cout << pc.x << ", " << pc.y << " | ";
            cout << pc_rect.x << ", " << pc_rect.y << " | ";
            cout << collicheck.x << ", " << collicheck.y << " | " <<endl;
        }
        else
        {
          if (menu_type == "main")
          {
            switch(cursor)
            {
              case 0:
                cursor = 3;
                break;
              case 1:
                cursor = 4;
                break;
              case 2:
                cursor = 5;
                break;
              case 3:
                cursor = 0;
                break;
              case 4:
                cursor = 1;
                break;
              case 5:
                cursor = 2;
                break;
            }
          }
          else if (menu_type == "inv")
          {
            //Unused
          }
          else if (menu_type == "inv2")
          {
            case 0:
              cursor = 1;
              break;
            case 1:
              cursor = 2;
              break;
            case 2:
              cursor = 0;
              break;
          }
        }
        break;

      case SDLK_RIGHT:
        if (menu == 0)
        {
          SDL_Rect collicheck = pc_rect;
          collicheck.x += 5;
          int canMove = 1;

          //Note: These are bounds + decorative/visible walls
          for (int w = 0; w < walls.size(); w++)
          {
            SDL_Rect wallRect = {walls[w].x, walls[w].y, 100, 100};
            if (SDL_HasIntersection(&collicheck, &wallRect))
              canMove = 0;
          }

          for (int d = 0; d < door_rects.size(); d++)
          {
            if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 1) //open door
            {
              cout << "branch1 " << endl;
            }
            else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_FALSE)
            {
              cout << "branch2 " << endl;
            }
            else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 0)
            {
              cout << "branch3 " << endl;
              canMove = 0;
              cout << "Open?" << doors[d].open <<endl;
            }

          }
          if (canMove == 1)
          {
            pc.x += 10;
            pc_rect.x += 10;
            client.call("player_update", pc);    //Supplies updated player data
          }

          cout << "PC     " << "PC_R " << " Coll     "   << "DOOR" <<endl;
          cout << pc.x << ", " << pc.y << " | ";
          cout << pc_rect.x << ", " << pc_rect.y << " | ";
          cout << collicheck.x << ", " << collicheck.y << " | " <<endl;

        }
        else
        {
          if (menu_type == "main")
          {
            switch(cursor)
            {
              case 0:
                cursor = 1;
                break;
              case 1:
                cursor = 2;
                break;
              case 2:
                cursor = 0;
                break;
              case 3:
                cursor = 4;
                break;
              case 4:
                cursor = 5;
                break;
              case 5:
                cursor = 3;
                break;
            }
          }
          else if (menu_type == "inv")
          {
            switch(cursor)
            {
              case 0:
                if (pc.inventory.size() == 0)
                  hud_rect = {0, 0, 0, 0};
                else
                  cursor = 1;
                break;

              case 1:
                cursor = 2;
                break;
              case 2:
                cursor = 3;
                break;
              case 3:
                cursor = 0;
                break;
            }
          }
          else if (menu_type == "inv2")
          {
            //Unused
          }
        }
        break;

      case SDLK_LEFT:
        if (menu == 0)
        {
          SDL_Rect collicheck = pc_rect;
          collicheck.x -= 5;
          int canMove = 1;

          //Note: These are bounds + decorative/visible walls
          for (int w = 0; w < walls.size(); w++)
          {
            SDL_Rect wallRect = {walls[w].x, walls[w].y, 100, 100};
            if (SDL_HasIntersection(&collicheck, &wallRect))
              canMove = 0;
          }

          for (int d = 0; d < door_rects.size(); d++)
          {
            if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 1) //open door
            {
              cout << "branch1 " << endl;
            }
            else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_FALSE)
            {
              cout << "branch2 " << endl;
            }
            else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 0)
            {
              cout << "branch3 " << endl;
              canMove = 0;
              cout << "Open?" << doors[d].open <<endl;
            }

          }
          if (canMove == 1)
          {
            pc.x -= 10;
            pc_rect.x -= 10;
            client.call("player_update", pc);    //Supplies updated player data
          }

          cout << "PC     " << "PC_R " << " Coll     "   << "DOOR" <<endl;
          cout << pc.x << ", " << pc.y << " | ";
          cout << pc_rect.x << ", " << pc_rect.y << " | ";
          cout << collicheck.x << ", " << collicheck.y << " | " <<endl;

        }

        else
        {
          if (menu_type == "main")
          {
            switch(cursor)
            {
              case 0:
                  cursor = 2;
                break;
              case 1:
                cursor = 0;
                break;
              case 2:
                cursor = 1;
                break;
              case 3:
                cursor = 5;
                break;
              case 4:
                cursor = 3;
                break;
              case 5:
                cursor = 4;
                break;
            }
          }
          else if (menu_type == "inv")
          {
            switch(cursor)
            {
              case 0:
                if (pc.inventory.size() == 0)
                  hud_rect = {0, 0, 0, 0};
                else
                  cursor = 3;
                break;
              case 1:
                cursor = 0;
                break;
              case 2:
                cursor = 1;
                break;
              case 3:
                cursor = 2;
                break;
            }
          }
          else if (menu_type == "inv2")
          {
            //Unused
          }
        }
        break;

      case SDLK_UP:
        if (menu == 0)
        {
          SDL_Rect collicheck = pc_rect;
          collicheck.y -= 5;
          int canMove = 1;

          //Note: These are bounds + decorative/visible walls
          for (int w = 0; w < walls.size(); w++)
          {
            SDL_Rect wallRect = {walls[w].x, walls[w].y, 100, 100};
            if (SDL_HasIntersection(&collicheck, &wallRect))
              canMove = 0;
          }

          for (int d = 0; d < door_rects.size(); d++)
          {
            if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 1) //open door
            {
              cout << "branch1 " << endl;
            }
            else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_FALSE)
            {
              cout << "branch2 " << endl;
            }
            else if (SDL_HasIntersection(&collicheck, &door_rects[d]) == SDL_TRUE && doors[d].open == 0)
            {
              cout << "branch3 " << endl;
              canMove = 0;
              cout << "Open?" << doors[d].open <<endl;
            }

          }
          if (canMove == 1)
          {
            pc.y -= 10;
            pc_rect.y -= 10;
            client.call("player_update", pc);    //Supplies updated player data
          }

          cout << "PC     " << "PC_R " << " Coll     "   << "DOOR" <<endl;
          cout << pc.x << ", " << pc.y << " | ";
          cout << pc_rect.x << ", " << pc_rect.y << " | ";
          cout << collicheck.x << ", " << collicheck.y << " | " <<endl;
        }
        else
        {
          if (menu_type == "main")
          {
            switch(cursor)
            {
              case 0:
                cursor = 3;
                break;
              case 1:
                cursor = 4;
                break;
              case 2:
                cursor = 5;
                break;
              case 3:
                cursor = 0;
                break;
              case 4:
                cursor = 1;
                break;
              case 5:
                cursor = 2;
                break;
            }
          }
          else if (menu_type == "inv")
          {
            //Unused
          }
          else if (menu_type == "inv2")
          {
            switch(cursor)
            {
              case 0:
                cursor = 2;
                break;
              case 1:
                cursor = 0;
                break;
              case 2:
                cursor = 1;
                break;
            }
          }
        }
        break;

      case SDLK_ESCAPE:
        quit = 1;
        break;

      case SDLK_z:
        //Interact canMove toggle
        if (menu == 0)
        {
          for (int d = 0; d < door_rects.size(); d++)
          {
            if (abs(pc.y - door_rects[d].y) <= 120 && abs(pc.x - door_rects[d].x) <= 120) //Check is player is by door...
            {
              client.call("use_door", d, pc.current_room); //TODO: ADD LOCKED OPTION (Maybe with a sound)
            }
          }


          for (int i = 0; i < item_rects.size(); i++)
          {
            if (abs(pc.y - item_rects[i].y) <= 30 && abs(pc.x - item_rects[i].x) <= 30) //Check is player is by door...
            {
              pc = client.call("obtain_item", i, pc).as<Mob>(); //TODO: (IF INV IS FULL. check return var) (Maybe with a sound)
              cout << "Inventory (Client)  Size:" <<pc.inventory.size() <<endl;
              cout << "=========" <<endl;
                for(i=0; i < pc.inventory.size(); i++)
                  cout << pc.inventory[i].name <<endl;
              break;
            }
          }
        }
        else
        {
          if (menu_type == "main")
          {
            switch(cursor)
            {
              case 0:
                menu_type = "inv";
                cursor = 0;
                break;
            }
          }
          else if (menu_type == "inv")
          {
            //SHOW INVENTORY ITEM DETAIL
          }
        }
        break;

      case SDLK_x:
        //Inventory canMove toggle
        if (menu == 0)
        {
          menu = 1;
          cursor = 0;
        }
        else
        {
          if (menu_type == "main")
          {
            menu = 0;
          }
          else if (menu_type == "inv")
          {
            menu_type = "main";
            cursor = 0;
          }
        }
        break;
    }
  }
}
