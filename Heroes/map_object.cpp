#include "game.h"


void game_t::_visit_object(int pos)
	{
	object_t* obj = _map.get_object_at(pos);
	if(!obj)
		return;
	
	const static std::string res_names[] = { "wood", "ore", "mercury", "sulfur", "crystal", "gems", "gold" };
	
	if(obj->type == resource_object)
		{
		resource_t& res = *(resource_t*)obj;
		int value = res.amount;
		int p = _current_player;
		switch(res.res_type)
			{
			case 0:	_players[p].wood += value; break;
			case 1: _players[p].ore += value; break;
			case 2: _players[p].mercury += value; break;
			case 3: _players[p].sulfur += value; break;
			case 4: _players[p].crystal += value; break;
			case 5: _players[p].gems += value; break;
			case 6: _players[p].gold += value; break;
			}
		_set_status("You find a small quantity of " + res_names[res.res_type]);
		_map.remove_object_at(pos);
		}
	else if(obj->type == mine_object)
		{
		mine_t& mine = *(mine_t*)obj;
		if(mine.owner != _current_player)
			{
			_players[_current_player].flagged_mines.insert(&mine);
			mine.owner = _current_player;
			_set_status("You have flagged a " + res_names[mine.mine_type] + " mine.");
			}
		else
			{//todo, allow adding guards, etc
			}
		
		}
	else if(obj->type == town_object)
		{ //show town screen
		_game_state = town_screen;
		}
	else if(obj->type == wandering_army_object)
		{ //show town screen
		_game_state = battle_screen;
		
		troop_t tr;
		tr.monster = (*(wandering_army_t*)obj).monster;
		tr.monster.type = 2;
		tr.monster.count = 18;
		tr.monster.max_hp = 3;
		tr.monster.min_damage = 1;
		tr.monster.max_damage = 2;
		tr.monster.attack = 3;
		tr.monster.defense = 1;
		tr.x = 21;
		tr.y = 0;
		tr.times_hit = 0;
		_battle.defender_troops.push_back(tr);
		
		hero_t& hero = _get_current_player().heroes[_current_hero];
		troop_t tra;
		tra.monster = hero.army[0];
		tra.x = 0;
		tra.y = 0;
		_battle.attacker_troops.push_back(tra);
		
		_init_battle();
		}
	}
