#ifndef BATTLE_H
#define BATTLE_H

#include <deque>
#include <string>
#include "monster.h"
#include "hero.h"

using std::deque;
using std::string;

struct troop_t
	{
	monster_t monster;
	int x, y;
	int target_x, target_y;
	float draw_x, draw_y;
	enum state_e
		{
		creature_waiting, moving, attacking, defending, retaliating
		} state;
	//spell_t[8] buffs, debuffs;
	int times_hit;
	};

//struct hero_t;

struct battle_t
	{
	battle_t();
	
	hero_t* attacker;
	hero_t* defender;
		
	//monster_t attacker_starting_troops;
	//monster_t defender_starting_troops;
	
	int turn;
	
	troop_t* current_troop;
	
	deque<troop_t> attacker_troops;
	deque<troop_t> defender_troops;
	
	deque<string> battle_log;
	};


#endif
