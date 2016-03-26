#include "game.h"
#include "monster.h"


std::string game_t::_get_monster_name(int type)
	{
	switch(type)
		{
		case 1: return "Skeleton";			
		case 2: return "Goblin";
		
		default:
			return "Unknown";
		}
	}

void game_t::_load_monsters()
	{
	monster_t m;
	m.type = 1;
	m.attack = 3;
	m.defense = 1;
	m.max_hp = 4;
	m.min_damage = 1;
	m.max_damage = 3;
	m.speed = 4;
	}