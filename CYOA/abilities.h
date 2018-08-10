#ifndef ABILITY_H
#define ABILITY_H
#include "mobs.h"
#include <SDL2/SDL.h>

struct Ability
{

  enum AbilityID
  {
    none = 000,

    //0xx will be human abilities
    interact = 001,
    talk = 002,
    use_item = 003,

    //1xx will be standard, melee types
    weapon_attack_short = 100,
    weapon_attack_long = 101,
    weapon_attack_ranged = 102,
    bash = 103

    //2xx with be projectile a
    //3xx will be projectile b
    //4xx will be aoe a
    //5xx will be aoe b
  };

  //SDL_Rect hit_box = {0, 0, 50, 50};
  int x;
  int y;
  int w;
  int h;
  int distance = 5; //Range is number steps the projectile will take before it fizzles
  int aoe_area = 0;
  int remaining_iterations = 4;
  string sprite = "item_twinkle";
  Mob user;
  //OffenseSelect user_os;

  MSGPACK_DEFINE_ARRAY(x, y, w, h, distance, aoe_area, remaining_iterations, sprite, user);
  Ability()
  {}

  Ability(int x_, int y_, int w_, int h_, string sprite_, Mob user_, bool distance_, int aoe_area_) :
         sprite(sprite_), user(user_), distance(distance_), aoe_area(aoe_area_)
  {
     x = x_;
     y = y_;
     w = w_;
     h = h_;
  }

  Mob collision_check(map<string, Mob> mobs)
  {
    Mob* null_mob = new Mob();
    map<string, Mob>::iterator it;
    SDL_Rect hit_box = {x, y, w, h};
    for (it = mobs.begin(); it != mobs.end(); it++)
    {
      SDL_Rect collide_rect = {it->second.x, it->second.y, it->second.w, it->second.h};
      if (SDL_HasIntersection(&hit_box, &collide_rect) && it->second.mob_type != Mob::npc && it->second.mob_type != user.mob_type)
         return it->second;
    }
    return *null_mob;
  }

  void process_damage(Mob caster, Mob target) //Caster and Target can be Player or Monsters
  {
    //if (caster is player)
    //Call sync  player to give back to player

  }

  void ability_update()
  {
    if (remaining_iterations > 0)
      remaining_iterations--;
    /*
    UPDATE TO SLASH LOCATION IF MOVING
    switch(user.dir)
    {
       case 'D':
         hit_box.x
    }
    hit_box.x =
    */

  }
};

struct MeleeAttack : public Ability //Base for all melee attacks
{
   MeleeAttack (int x_, int y_, int w_, int h_, string sprite_, Mob user_, bool distance_, int aoe_area_) : Ability(x_, y_, w_, h_, sprite_, user_, distance_, aoe_area_)
   {

   }

};

struct ProjectileAttack : public Ability //Base for all projectile attacks
{
  int curr_distance = distance;

  ProjectileAttack (int x_, int y_, int w_, int h_, string sprite_, Mob user_, bool distance_, int aoe_area_) : Ability(x_, y_, w_, h_, sprite_, user_, distance_, aoe_area_)
  {

  }

};

struct AOEAttack : public Ability //Base for all AOE attacks
{
   int aoe_area;

   AOEAttack (int x_, int y_, int w_, int h_, string sprite_, Mob user_, bool distance_, int aoe_area_) : Ability(x_, y_, w_, h_, sprite, user_, distance_, aoe_area_)
   {

   }

};

#endif
