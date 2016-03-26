#include "battle.h"
#include "game.h"

#include <sstream>

battle_t::battle_t()
	: turn(0)
	{
	}


void game_t::_init_battle()
	{
	_battle_state = waiting;
	_battle.current_troop = &(_battle.attacker_troops.front());
	}
	
int get_damage(int min, int max)
	{
	return min + (rand() % (max - min + 1));
	}
	


int calc_damage(monster_t& attacker, monster_t& defender)
	{
	int idmg = attacker.count * get_damage(attacker.min_damage, attacker.max_damage);
	float mod = 1.0f;
	if(attacker.attack >= defender.defense)
		mod += (attacker.attack - defender.defense) * 0.10f;
	else
		mod += (attacker.attack - defender.defense) * 0.05f;
	int tdmg =(int) idmg * mod;
	return tdmg;
	}

string do_attack(monster_t& attacker, monster_t& defender)
	{
	int dmg = calc_damage(attacker, defender);
				
	int def_hp = attacker.max_hp * attacker.count;
	def_hp -= dmg;
	int killed = ceil(dmg / (float) defender.max_hp);
	defender.count = ceil(def_hp / (float) defender.max_hp);
	
	
	std::stringstream strm;
	strm << game_t::_get_monster_name(attacker.type) << "s do " << dmg << ".  " 
			<< killed << " " << game_t::_get_monster_name(defender.type) << "s perish.";
	return strm.str();
	}

void game_t::_update_battle()
	{
	switch(_battle_state)
		{
		case waiting:
			break;
		
		case creature_attacking:
			{			
			_battle.current_troop->x = _battle.current_troop->target_x;
			_battle.current_troop->y = _battle.current_troop->target_y;
			//_battle.current_troop->state = creature_waiting;
			
			
			_battle.battle_log.push_front(do_attack(_battle.current_troop->monster, _battle.defender_troops.back().monster));
			_battle.battle_log.push_front(do_attack(_battle.defender_troops.back().monster, _battle.current_troop->monster));

			//if(_battle.defender_troops.back().monster.count <= 0)
			//	_battle.defender_troops.pop_back();
			
			_battle_state = waiting;
			}
			break;
		case creature_moving:
			{
			_battle.current_troop->x = _battle.current_troop->target_x;
			_battle.current_troop->y = _battle.current_troop->target_y;
			//_battle.current_troop->state = creature_waiting;
			_battle_state = waiting;
			}
			break;
		}
	}

//void

void game_t::_battle_screen_click(int mx, int my)
	{
	if(_battle_state != waiting) //only accept clicks while busy to turn autocombat on/off
		{ //todo: autocombat
		
		return;
		}
	
	
	int sx = _battle.current_troop->x;
	int sy = _battle.current_troop->y;
	int ss = _battle.current_troop->monster.speed;
	
	int tx = (mx - 78) / 26;
	int ty = (my - 78) / 24;
	
	if((tx - sx) + (ty - sy) <= ss) //this is wrong
		{
		_battle.current_troop->target_x = ((mx - 70) / 30);
		_battle.current_troop->target_y = ((my - 70) / 30);
		if(_battle.defender_troops.back().x == tx && _battle.defender_troops.back().y == ty)
			{
			_battle_state = creature_attacking;
			}
		else
			{
			_battle_state = creature_moving;
			}
		}
	
	
	//int mx = _window.get_ic().get_mouse().get_x();
	//int my = _window.get_ic().get_mouse().get_y();
	
	}