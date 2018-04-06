//Add functions for simplicity?

void process_input(int &cursor, SDL_Event evt, Mob &pc, int &menu, string &menu_type, SDL_Rect &pc_rect, SDL_Rect &hud_rect, int &quit)
{
    if(evt.type == SDL_KEYDOWN)
  {
    switch(evt.key.keysym.sym)
    {
      case SDLK_DOWN:
        if (menu == 0)
          pc.y += 10;
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
          /*if (SDL_HasIntersection(&pc_rect, &(door1.rect)) == SDL_FALSE)    //DOOR_TEST
            pc.x += 10;
          else if (SDL_HasIntersection(&pc_rect, &(door1.rect)) == SDL_TRUE && door1.state == "open*/
            pc.x += 10;
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
                if (pc.inventory[0] == "none")
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
          pc.x -= 10;
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
                if (pc.inventory[0] == "none")
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
          pc.y -= 10;
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
        //Interact flag toggle
        if (menu == 0)
        {
          //Interact button?
          //DOOR_TEST
          /*if (abs(pc.y - door1.rect.y) <= 100 && pc.x == door1.rect.x) //If next to door...
          {
            if(door1.state == "closed")
              door1.state = "open";
            else
              door1.state = "closed";
            cout << door1.state <<" " <<pc.y << " " << door1.rect.y << abs(pc.y - door1.rect.y)  <<endl;
          }*/
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

          }
        }
        break;

      case SDLK_x:
        //Inventory flag toggle
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
