#ifndef MONSTER_H
#define MONSTER_H

struct monster_t
	{
	int type;
	int max_hp, current_hp;
	int min_damage, max_damage;
	int attack, defense;
	int speed;
	int count;
	};


#endif
