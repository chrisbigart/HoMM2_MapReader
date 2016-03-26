#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <algorithm>

#include "monster.h"

#include "mp2.h"

using std::vector;
using std::string;

struct player_attributes_t
	{
	bool is_playable;
	bool human_allowed, computer_allowed;
	bool human, computer;
	int behavior;
	int starting_alignment;
	int allowed_alignments;
	bool random_city; 
	bool has_main_city;
	int main_city_type;
	struct { int x, y, level; } main_city_location;
	bool gen_hero_at_main_city;
	int random_hero, hero_type;
	int hero_portrait;
	std::string hero_name;
	};

enum object_types_e
	{
	town_object, mine_object, resource_object, wandering_army_object
	};

enum resource_type_e
	{
	wood, ore, mercury, sulfur, crystal, gems, gold
	};

enum difficulty_e
	{
	easy, normal, hard, expert
	};

struct object_t
	{
	object_t() {}
	object_t(object_types_e type_) : type(type_) { }
	bool object_t::operator<(const object_t& other) const;
	int map_x, map_y;
	int draw_x, draw_y;
	int draw_layer; //draw flags
	int level; //either 1 or 2
	bool is_animated;
	std::pair<MP2::obj_type_e, int> h2_obj_id;
	MP2::obj_type_e h2_id;
	object_types_e type;
	};
	
struct town_t : object_t
	{
	town_t() : object_t(town_object) { }
	string name;
	enum alignment_t
		{ castle, rampart, tower, inferno, necropolis, dungeon, stronghold, fortress, conflux }
		alignment;
	short owner;
	};

struct mine_t : object_t
	{
	mine_t() : object_t(mine_object) { }
	resource_type_e mine_type;
	int owner;
	};
	
struct wandering_army_t : object_t
	{
	wandering_army_t() : object_t(wandering_army_object) { }
	monster_t monster;
	int quantity;
	};
	
struct resource_t : object_t
	{
	resource_t() : object_t(resource_object) { }
	resource_type_e res_type;
	int amount;
	};

struct map_t
	{
	
	/*		
	public:
		bool load(const std::string& filename);
		const string get_object_name_at(int x, int y);
		//player_specs_t get_player_specs() const;
	
	protected:	
		const string get_object_name(const map_t::object_t* object) const;
		
	protected:
		bool _load_heroes3_map(const std::string& filename);
		void _compute_passability(unsigned char arr[6], int objx, int objy, object_t* obj);
		
		
	private:*/
		
	
		
	enum terrain_type_e
		{
		dirt, sand, grass, snow, swamp, rough, subterrainian, lava, water
		};
		
	struct tile_t //change this to custom specification
		{
		tile_t() : type(0), subtype(0), rotation(0), explored(0) { }
		unsigned int type, subtype, rotation;
		short river, road; //combine into a union?
		short landscape;
		char explored;
		};
	
	typedef tile_t terrain_tile_t;

	struct map_tile_t
		{
		terrain_tile_t terrain;
		vector<object_t> objects;
		};
		
	bool is_explored(int pos, int player);
	void set_explored(int pos, int player, bool explored);
	tile_t get_terrain(int x, int y);
	tile_t get_terrain_at(int pos);
	bool is_walkable(int pos);
	bool is_visitable(int pos);
	bool is_walkable(int x, int y) { return is_walkable(x + (y * width)); }
	bool is_visitable(int x, int y) { return is_visitable(x + (y * width)); }
	object_t* get_object_at(int pos);
	object_t* get_object_at(int x, int y);
	void remove_object_at(int pos);
		
	int num_players;
	player_attributes_t player_attributes[8];

	vector<MP2::mp2tile_t> h2_mp2_tiles;
	vector<MP2::mp2addon_t> h2_mp2_addon_tiles;
		
	string name, description;
	int width, height;
	difficulty_e difficulty;
	vector<tile_t> terrain;
	vector<map_tile_t> map_tiles;
	vector<object_t*> objects;
		
	vector<object_t*> index;
	vector<town_t*> towns;
	};


#endif
