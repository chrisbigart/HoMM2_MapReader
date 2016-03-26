#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "town.h"
#include "hero.h"

#include <vector>
#include <set>

using std::vector;
using std::set;

struct player_t
	{
	public: //cross skill bonuses
	//private:
	//	void _calculate_income();
		
	int gold, ore, gems, mercury, sulfur, wood, crystal;
	bool human, computer;
	int behavior;
	vector<hero_t> heroes;
	//vector<town_t> towns;	
	set<mine_t*> flagged_mines;
	//vector<dwelling_t*> flagged_dwellings;
	};

#endif
