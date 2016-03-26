#include "map.h"

#include <string>
#include <sstream>


bool map_t::is_explored(int pos, int player)
	{
	return terrain[pos].explored | (1 << player);
	}

void map_t::set_explored(int pos, int player, bool explored)
	{
	terrain[pos].explored |= (explored ? 1 : 0 << player);
	}

map_t::tile_t map_t::get_terrain(int x, int y)
	{
	return terrain[x + y*width];
	}
map_t::tile_t map_t::get_terrain_at(int pos)
	{
	return terrain[pos];
	}
bool map_t::is_walkable(int pos)
	{
	if(terrain[pos].type == water) return false; //for now...
	
	bool indexed = (index[pos] != 0);
	return !indexed;
	}

bool map_t::is_visitable(int pos)
	{
	bool indexed = (index[pos] != 0);
	if(!indexed)
		return true;
	else
		return (index[pos]->map_x == (pos % width) && index[pos]->map_y == (pos / width));
	}

object_t* map_t::get_object_at(int pos)
	{
	return index[pos];
	}
object_t* map_t::get_object_at(int x, int y)
	{
	return index[x + y*width];
	}
	
void map_t::remove_object_at(int pos)
	{
	//grossly inefficient, but how often does this occur?  pretty infrequently
	object_t* obj = index[pos];
	objects.erase(std::find(objects.begin(), objects.end(), obj));
	for(int i = 0; i < (int)index.size(); i++)
		{
		if(index[i] == obj)
			index[i] = 0;
		}
	delete obj;
	}


/*
bool map_t::load(const std::string& filename)
	{
	return _load_heroes3_map(filename);
	return true;
	}


//i'd like to simply return references to strings here but...

const string map_t::get_object_name(const map_t::object_t* object) const
	{
	static const string object_names[] = { "Object" };
	static const string resource_names[] = { "Wood", "Mercury", "Ore", "Sulfur", "Crystal", "Gems", "Gold" };
	std::stringstream strm;
	switch(object->type)
		{
		case map_t::town:
			{
			string name = ((town_t*)object)->name;
			strm << ((town_t*)object)->alignment;
			return name + ", Town [Type: " + strm.str();
			}
		case map_t::mine:
			{
			int type = ((mine_t*)object)->mine_type;
			return resource_names[type] + " Mine";
			}
		case map_t::resource:
			{
			int type = ((resource_t*)object)->res_type;
			return resource_names[type];
			}
		default:
			return "Unknown";
		}
	return object_names[0];
	}

	
const string map_t::get_object_name_at(int map_x, int map_y)
	{
	static const string terrain_names[] = { "Dirt", "Sand", "Grass", "Snow", "Swamp", "----", "Rough", "Lava", "Water" };
	static const string none = "Object";
	static const string empty = "Empty";
	
	int loc = map_x + (map_y * _width);
	if(loc < 0 || loc > _index.size())
		return empty;
	
	if(_index[loc])
		return get_object_name(_index[loc]);
	else
		return terrain_names[_terrain[loc].type];
	}
	*/

	
