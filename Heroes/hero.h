#ifndef HERO_H
#define HERO_H

#include <string>
#include <list>

using std::string;

#include "monster.h"
#include "path.h"

struct hero_t
	{
	hero_t() : command(stop), moving(false) { }
	
	int type, subtype;
	int portrait;
	int mapx, mapy, facing;
	float drawx, drawy;
	int attack, defense, power, knowledge;
	//secondary_skill_e skills[8];
	int specialty;
	int movement_left, max_movement;
	int current_mana, max_mana;
	int level, experience;
	//artifact_t backpack;
	//spells_t spellbook;
	string name;
	path_t path;
	enum command_e
		{
		stop, move, finish_moving
		} command;
		
	bool moving;
	monster_t army[8];
	//string story;
	};

#endif
