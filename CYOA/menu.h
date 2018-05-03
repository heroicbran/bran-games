void draw_menu(int &cursor, int &menu, string &menu_type, SDL_Rect &hud_rect, Mob pc, SDL_Surface* screenSurface, map<string, SDL_Surface*> &images)
{
  if (menu == 1)
  {
    //////////
    //HUD Black Background
    /////////
    hud_rect = {0, 450, 1280, 500};
    SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    ///////////
    //Profile Image
    ///////////
    hud_rect = {50, 500, 200, 200};
    SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xBB, 0xFF));

    if (menu_type == "main")
    {
      /////////
      //Cursor
      /////////
      switch(cursor)
      {
        case 0:
          hud_rect = {390, 490, 270, 120};      //-10,-10, +20, +20 vs original
          break;
        case 1:
          hud_rect = {665, 490, 270, 120};
          break;
        case 2:
          hud_rect = {940, 490, 270, 120};
          break;
        case 3:
          hud_rect = {390, 615, 270, 120};
          break;
        case 4:
          hud_rect = {665, 615, 270, 120};
          break;
        case 5:
          hud_rect = {940, 615, 270, 120};
          break;
      }
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xE3, 0x86, 0x34));

      /////////
      //menu slot background
      ////////
      //Menu Slots
      hud_rect = {400, 500, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {675, 500, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {950, 500, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {400, 625, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {675, 625, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

      hud_rect = {950, 625, 250, 100};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image

    }
    else if (menu_type == "inv")
    {
      /////////
      //Cursor
      /////////
      switch(cursor)
      {
        case 0:
          hud_rect = {337, 510, 200, 200};
          break;
        case 1:
          hud_rect = {537, 510, 200, 200};
          break;
        case 2:
          hud_rect = {737, 510, 200, 200};
          break;
        case 3:
          hud_rect = {937, 510, 200, 200};
          break;
      }
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xE3, 0x86, 0x34));

      /////////
      //menu slot background
      ////////
      //Menu Slots
      ///////
      hud_rect = {350, 525, 175, 175};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image
      cout << pc.inventory.size() <<endl;
      cout << pc.inventory[0].sprite <<endl;
      if (pc.inventory.size() >= 1)
        SDL_BlitSurface(images[pc.inventory[0].sprite], NULL, screenSurface, &hud_rect);

      hud_rect = {550, 525, 175, 175};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image
      if (pc.inventory.size() >= 2)
        SDL_BlitSurface(images[pc.inventory[1].sprite], NULL, screenSurface, &hud_rect);

      hud_rect = {750, 525, 175, 175};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image
      if (pc.inventory.size() >= 3)
        SDL_BlitSurface(images[pc.inventory[2].sprite], NULL, screenSurface, &hud_rect);

      hud_rect = {950, 525, 175, 175};
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      //Actual Menu Image
      if (pc.inventory.size() == 4)
        SDL_BlitSurface(images[pc.inventory[3].sprite], NULL, screenSurface, &hud_rect);

    }
    else if (menu_type == "inv2")
    {
      switch(cursor)
      {
        case 0:
          hud_rect = {50, 500, 200, 200};
          break;
        case 1:
          hud_rect = {50, 500, 200, 200};
          break;
        case 2:
          hud_rect = {50, 500, 200, 200};
          break;
      }
      SDL_FillRect(screenSurface, &hud_rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xBB, 0xFF));

      //INV2 SLOT BACKGROUNDS
    }

    //Text boxes
  }
}
