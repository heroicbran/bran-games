#ifndef ABILITY_H
#define ABILITY_H

#include <SDL2/SDL.h>

struct Ability
{
  SDL_Rect hit_box = {0, 0, 50, 50};
  int frames = 4;
  string sprite = "item_twinkle";
  string origin;   //player or monster. This is used to decide who to collision/damage check
  Mob user;

  Mob collision_check(map<string, Mob> mobs)
  {

  }

  void process_damage(Mob caster, Mob target) //Caster and Target can be Player or Monsters
  {

  }

  void ability_update()
  {

  }

};

struct MeleeAttack : public Ability
{
   void melee_attack()
   {

   }
};

struct ProjectileAttack : public Ability
{

  int range = 5; //Range is number steps the projectile will take before it fizzles
  int curr_range = range;
  SDL_Rect hit_box = {0, 0, 50, 50};

  void projectile_attack()
  {

  }
};

struct AOEAttack : public Ability
{
   int area;
};

#endif
