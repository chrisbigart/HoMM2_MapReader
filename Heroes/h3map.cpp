#include <string>
#include <fstream>
#include <cassert>


#include "game.h"
#include <ClanLib/core.h>

//gotta change this to use 'stdint'/'cstdint'
//typedef cl_int32 int32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
//typedef cl_uint8 uint8_t;
//typedef char uint8_t;

#pragma warning(disable:4800)

/*
	struct ObjectTown {
		quint32 junk;
		quint8 owner;

		quint8 isName;

	//    if ( isName == 1 )
			HString name;

		quint8 isGuard;

	//    if (isGuard == 1 )
			 Guard_t guards[7];

		quint8 formation; // 00 - standalone, 01 - group

		quint8 isBuildings;

	//    if ( isBuildings == 1 ) {
			quint8 built[6];
			quint8 active[6];
	//    } else {
			quint8 isFort;
	//    }

		quint8 mustSpells[9];
		quint8 canSpells[9];

		quint32 event_quantity;

	//    if ( event_quantity > 0 ) {
			QVector<TownEvent_t> events;
	//    }
		quint32 junk3;
	};
	*/
town_t read_town(CL_File& f)
	{
	//town_t* town = new town_t;
	town_t town;
	uint32_t tjunk = f.read_uint32();
	uint8_t owner = f.read_uint8();
	uint8_t named = f.read_uint8();
	string name;
	if(named == 1)
		name = f.read_string_a();
	else
		{ //cook up a random name for the town
		name = "Random Name";
		}
	
	uint8_t guarded = f.read_uint8();
	if(guarded == 1)
		{
		/*
		struct Guard_t {
			quint16 GuardID;
			quint16 GuardCount;
		};
		*/
		for(int i = 0; i < 7; i++)
			{
			f.read_uint16();
			f.read_uint16();
			}
		}				
	
	uint8_t formation = f.read_uint8();
	
	uint8_t has_buildings = f.read_uint8();
	if(has_buildings == 1)
		{
		uint8_t built[6];
		uint8_t active[6];
		for(int i = 0; i < 6; i++)
			built[i] = f.read_uint8();
		for(int i = 0; i < 6; i++)
			active[i] = f.read_uint8();
		}
	else
		uint8_t has_fort = f.read_uint8();	
	
	
	uint8_t spells[9];
	uint8_t excluded_spells[9];
	
	for(int i = 0; i < 9; i++)
		spells[i] = f.read_uint8();
	
	for(int i = 0; i < 9; i++)
		excluded_spells[i] = f.read_uint8();
	
	/*
	struct TownEvent_t {
		HString event_name;
		HString event_text;

		Resources_t res;

		quint8 _map.player_attributes_affected;
		quint8 human_affected;
		quint8 ai_affected;

		quint16 day_of_first_event;
		quint16 event_iteration;
		quint32 junk[4];
		quint8 buildings[6];
		quint16 creatures[7];
		quint32 junk2;
	};
	*/
	uint32_t num_events = f.read_uint32();
	for(unsigned int i = 0; i < num_events; i++)
		{
		f.read_string_a();
		f.read_string_a();
		
		//todo					
		
		f.read_uint8();
		f.read_uint8();
		f.read_uint8();
		
		f.read_uint16();
		f.read_uint16();
		f.read_uint32();
		f.read_uint8();
		f.read_uint16();
		f.read_uint32();
		}
	
	uint32_t tjunk2 = f.read_uint32();
	
	return town;
	}




bool game_t::_load_heroes3_map(const std::string& filename)
	{
	/*std::ifstream in(filename.c_str(), std::ios_base::binary);
	if(!in)
		return;
	*/
	
	/*
	Heroes 3 maps can apparently either be .gz (zlib) compressed or uncompressed.
	*/
	
	
	CL_File f(filename);
	if(f.is_null())
		return false;
	
	
	
	/*
	struct BASIC_PARAMETERS {
    int	    magic_header;
    char	junk;
    uint32	size;
    char	under;

    hstring name;
    hstring description;

    char	difficult;
    char	levelLimit;
	};
	*/
	
	//wrap this in a try... block?

	/*	
	const quint32 MAP_HOMM3_ROE = 0x0000000E;
	const quint32 MAP_HOMM3_AB = 0x00000015;
	const quint32 MAP_HOMM3_SOD = 0x0000001C;
	*/
	
	const uint32_t ROE = 0x0000000e;
	const uint32_t AB  = 0x00000015;
	const uint32_t SOD = 0x0000001C;
	
	int32_t version = f.read_int32();
	if(version != ROE && version != AB && version != SOD)
		{
		std::cerr << "Unsupported map type\n";
		return false;
		}
	
	uint8_t junk1 = f.read_int8(); //junk?
	uint32_t size = f.read_uint32();
	uint8_t underworld = f.read_uint8();
	CL_String name = f.read_string_a();
	CL_String desc = f.read_string_a();
	
	_map.width = size;
	_map.height = size;
	
	//check validity of width and height values
	if(size > 1000 || size <= 0)
		{
		std::cerr << "Map size invalid\n";
		return false;
		}
	
	_map.index.resize(size*size, 0);
	
	uint8_t difficulty = f.read_uint8();
	if(version == SOD)
		uint8_t level_limit = f.read_uint8();
	
	/*
	PLAYER_ATTRIBUTES red;
	PLAYER_ATTRIBUTES blue;
	PLAYER_ATTRIBUTES tan;
	PLAYER_ATTRIBUTES green;
	PLAYER_ATTRIBUTES orange;
	PLAYER_ATTRIBUTES purple;
	PLAYER_ATTRIBUTES teal;
	PLAYER_ATTRIBUTES pink;
	
	quint8 isHuman;
    quint8 isComputer;
    quint8 behavior;	// 0-Random
                        // 1-Warrior
                        // 2-Builder
                        // 3-Explorer
    quint8 isCityTypesOpt;
    quint16 cityTypes;  // Bit0 Castle
                        // Bit1 Rampart
                        // Bit2 Tower
                        // Bit3 Inferno
                        // Bit4 Necropolis
                        // Bit5 Dungeon
                        // Bit6 Stronghold
                        // Bit7 Fortress
                        // Bit8 Conflux
    quint8 randomCity;
    quint8 mainCity;

	//  if mainCity == 1 {
		quint8 generateHero;
		quint8 city[4]; // 0 - city type, 0xFF - random city
						// 1-3 coords (x,y,z)
	// }

		quint8 randomHero;
		quint8 heroType;


	//  if ( heroType != 0xFF ) {
		quint8 heroPortret;
		HString heroName;
	//  }

		quint8 junk; // ??? get more info
		quint32 heroesCount;

	//  if ( heroesCount > 0 ) {
		QVector<Hero_t> heroes;
	*/
	_num_players = 0;
	
	switch(version)
		{
		case ROE:
			for(int i = 0; i < 8; i++)
				{
				/*
				for ROE: (this isn't quite right for some cases...)
				
				main town at:  x  y lvl
				has main town  |  |  |
				            |  v  v  v
				            v  |------|
				01 01 00 01 00 00 00 FF 
				00 01 00 01 00 00 00 FF 
				00 01 00 08 00 00 00 FF 
				00 01 00 20 00 00 00 FF 
				00 01 00 FF 01 00 00 FF 
				00 01 00 01 00 00 00 FF 
				00 01 00 01 00 00 00 FF 
				01 01 03 02 00 01 1B 0A
				      ^  ^
				      |  - allowed alignments
				
				behavior
				*/
				
				_map.player_attributes[i].human = (bool)(f.read_uint8());
				_map.player_attributes[i].computer = (bool)f.read_uint8();
				_map.player_attributes[i].behavior = f.read_uint8();
				_map.player_attributes[i].starting_alignment = f.read_uint8();
				_map.player_attributes[i].has_main_city = f.read_uint8();
				_map.player_attributes[i].main_city_location.level = f.read_uint8();
				_map.player_attributes[i].main_city_location.x = f.read_uint8();
				_map.player_attributes[i].main_city_location.y = f.read_uint8();
				
				if(_map.player_attributes[i].human || _map.player_attributes[i].computer)
					_num_players++;
				}
			break;
			
		case SOD:
			for(int i = 0; i < 8; i++)
				{
				_map.player_attributes[i].human = (bool)f.read_uint8();
				_map.player_attributes[i].computer = (bool)f.read_uint8();
				_map.player_attributes[i].behavior = f.read_uint8();
				_map.player_attributes[i].starting_alignment = f.read_uint8(); 
				_map.player_attributes[i].allowed_alignments = f.read_uint16();
				_map.player_attributes[i].random_city = (bool)f.read_uint8();
				_map.player_attributes[i].has_main_city = f.read_uint8();
				
				if(_map.player_attributes[i].human || _map.player_attributes[i].computer)
					_num_players++;
				
				if(_map.player_attributes[i].has_main_city)
					{
					_map.player_attributes[i].gen_hero_at_main_city = f.read_uint8();
					_map.player_attributes[i].main_city_type = f.read_uint8();
					_map.player_attributes[i].main_city_location.x = f.read_uint8();
					_map.player_attributes[i].main_city_location.y = f.read_uint8();
					_map.player_attributes[i].main_city_location.level = f.read_uint8();
					}
				
				_map.player_attributes[i].random_hero = f.read_uint8();
				_map.player_attributes[i].hero_type = f.read_uint8();
				
				if(_map.player_attributes[i].hero_type != 0xff)
					{
					uint8_t portrait = f.read_uint8();
					CL_String8 name = f.read_string_a();			
					}
				
				uint8_t junk = f.read_uint8();
				uint32_t hero_count = f.read_uint32();
				
				for(unsigned int i = 0; i < hero_count; i++)
					{
					uint8_t portrait = f.read_uint8();
					CL_String8 name = f.read_string_a();	
					}
				
				}
			break;
	}
	
	/*
	struct SpecialLossConditions {
    uchar id;

    if ( id != 0xFF ) {
        if ( id == 0x00 || id == 0x01 ) {
            uchar coord[3];
        }
        else if ( id == 0x02 )
            ushort days;
    }
	};
	*/
	
	uint8_t win_condition = f.read_uint8();
	uint8_t loss_condition = f.read_uint8();
	
	/*
	struct Teams {
    uchar commands_count;

    if ( commands_count > 0 ) {
        uchar commands[8];
    }
	};
	*/
	
	uint8_t num_teams = f.read_uint8();
	uint8_t teams[8];
	for(int i = 0; (num_teams > 0) && (i < 8); i++) //if we have teams
		{
		teams[i] = f.read_uint8();
		}
	
	
	/*
	struct FreeHeroes {
    uchar free_heroes[20];
    uchar junk[4];
    uchar heroes_count;
    
    if (heroes_count > 0) {
        struct tuned_tag {
            uchar heroID;
            uchar heroPortrait;
            hstring hero_name;

            uchar _map.player_attributes;
        } tuned[heroes_count] <optimize=false>;
    }

    uchar junk2[31];
	};
	*/
	
	//27 bytes of info here for ROE, 67 for SOD
	uint8_t free_heroes[20];
	switch(version)
		{
		case ROE:
			{
			for(int i = 0; i < 20; i++)
				free_heroes[i] = f.read_uint8();
			}
		case SOD:
			{
			for(int i = 0; i < 20; i++)
				free_heroes[i] = f.read_uint8();
			}
			break;
		}
	
	uint8_t junk[4];
	junk[0] = f.read_uint8();
	junk[1] = f.read_uint8();
	junk[2] = f.read_uint8();
	junk[3] = f.read_uint8();
	
	uint8_t freehero_count = f.read_uint8();
	
	for(int i = 0; i < freehero_count; i++)
		{
		uint8_t hero_id = f.read_uint8();
		uint8_t portrait = f.read_uint8();
		CL_String name = f.read_string_a();
		uint8_t map_players = f.read_uint8();
		}
	
	uint8_t fhjunk[32];
	for(int i = 0; i < 31; i++)
		fhjunk[i] = f.read_uint8();
	
	
	/*
	struct Artefacts {
    uchar artefacts[18] <format=binary>;
	};

	struct Spells {
		uchar spells[9] <format=binary>;
	};

	struct SecSkills {
		uchar skills[4] <format=binary>;
	};
	*/
	
	uint8_t artifacts[18];
	for(int i = 0; i < 18; i++)
		artifacts[i] = f.read_uint8();
		
	uint8_t spells[9];
	for(int i = 0; i < 9; i++)
		spells[i] = f.read_uint8();
		
	uint8_t skills[4];
	for(int i = 0; i < 4; i++)
		skills[i] = f.read_uint8();
		
	
	/*
	struct Rumors {
    uint32 total_rumors;

    if ( total_rumors > 0 ) {
        struct Rumor_tag {
        
            hstring rumor_name;

            hstring rumor_text;
        } rumors[total_rumors] <optimize=false>;
    }
	};
	*/
	
	uint32_t num_rumors = f.read_uint32();
	for(unsigned int i = 0; i < num_rumors; i++)
		{
		CL_String name = f.read_string_a();
		CL_String rumor = f.read_string_a();
		}
	
	
	/*
	struct HeroOptions_enabled {
    uchar isExp;
    
    if ( isExp == 1 )
        uint32 exp;

    uchar isSecSkill;

    if ( isSecSkill == 1 ) {
        uint32 skills_count;

        secskill_tag secskills [skills_count];
    }

    uchar isArtefacts;

    if ( isArtefacts == 1 ) {
        ushort headID;
        ushort shouldersID;
        ushort neckID;
        ushort rightHandID;
        ushort leftHandID;
        ushort trunkID;
        ushort rightRingID;
        ushort leftRingID;
        ushort legsID;
        ushort misc1ID;
        ushort misc2ID;
        ushort misc3ID;
        ushort misc4ID;
        ushort machine1ID;
        ushort machine2ID;
        ushort machine3ID;
        ushort machine4ID;
        ushort magicbook;
        ushort misc5ID;

        ushort knapsack_count;

        if ( knapsack_count > 0 )
            ushort knapsackID[knapsack_count];
    }

    uchar isBiography;
    
    if (isBiography == 1)
        hstring biography;

    uchar gender <read=genderRead>;

    uchar isSpells;

    if ( isSpells == 1 )
        uchar spells[9] <format=binary>;

    uchar isPrimarySkills;

    if ( isPrimarySkills == 1 ) {
        uchar attack;
        uchar defence;
        uchar power;
        uchar knowledge;
    }
	};

	struct HeroOptions {
		local int i;

		for (i = 0; i < 156; i++) {
			uchar enable;
	        
			if ( enable == 1 )
				HeroOptions_enabled options;
		}  
	};
	*/
	
	for(int i = 0; i < 156; i++) //there are 156 different heroes in homm3sod
		{
		uint8_t enabled = f.read_uint8();
		if(enabled)
			{
			uint8_t has_xp = f.read_uint8();
			
			}
		}
	
	
	/*
	struct LandCell {
    uchar surfaceID;
    uchar surfacePattern;
    uchar riverID;
    uchar riverPattern;
    uchar roadID;
    uchar roadPattern;
    uchar mirroring <format=binary>;
	};
	
	
	LandCell ground[bp.size*bp.size] <optimize=true>;
	*/
	
	_map.terrain.reserve(size*size); //don't like this
	
	for(unsigned int i = 0; i < size * size; i++)
		{
		uint8_t surface_id = f.read_uint8();
		uint8_t surface_pattern = f.read_uint8();
		uint8_t river_id = f.read_uint8();
		uint8_t river_pattern = f.read_uint8();
		uint8_t road_id = f.read_uint8();
		uint8_t road_pattern = f.read_uint8();
		uint8_t mirroring = f.read_uint8();
		
		map_t::tile_t tile; //i don't like this approach
		tile.type = surface_id;
		tile.subtype = surface_pattern;
		tile.road = road_id;
		tile.river = river_id;
		_map.terrain.push_back(tile);
		}
	
	if(underworld)
		{		
		for(unsigned int i = 0; i < size * size; i++)
			{
			uint8_t surface_id = f.read_uint8();
			uint8_t surface_pattern = f.read_uint8();
			uint8_t river_id = f.read_uint8();
			uint8_t river_pattern = f.read_uint8();
			uint8_t road_id = f.read_uint8();
			uint8_t road_pattern = f.read_uint8();
			uint8_t mirroring = f.read_uint8();
			}
		}
	
	
	/*
	struct Object {
    hstring filename;
    uchar passability[6];
    uchar actions[6];
    ushort landscape;
    ushort land_edit_groups; // for editor
    uint32 object_class;
    uint32 object_number;
    uchar object_group;
    uchar isOverlay;
    uchar junk[16];
	};
	*/
	
	uint32_t num_objects = f.read_uint32();
	
	struct h3object_t
		{
		int x, y;
		uint8_t passability[6];
		uint8_t actions[6];
		uint32_t obj_class, object_number;
		};
	
	vector<h3object_t> objects;
	objects.reserve(num_objects);  //instead, create local array of heroes3-specific objects, then convert
	
	for(unsigned int i = 0; i < num_objects; i++)
		{
		CL_String object_filename = f.read_string_a();
		
		h3object_t obj;
		
		for(int n = 0; n < 6; n++)
			obj.passability[n] = f.read_uint8();
		
		for(int n = 0; n < 6; n++)
			obj.actions[n] = f.read_uint8();
		
		uint16_t landscape = f.read_uint16();
		uint16_t land_edit_groups = f.read_uint16();
		
		uint32_t object_class = f.read_uint32();
		uint32_t object_number = f.read_uint32();
		uint8_t object_group = f.read_uint8();
		uint8_t is_overlay = f.read_uint8();		
		
		uint8_t obj_junk[16];
		for(int n = 0; n < 16; n++)
			obj_junk[n] = f.read_uint8();
			
		
		obj.obj_class = object_class;
		obj.object_number = object_number;
		objects.push_back(obj);
			
		std::cout << "Object(" << object_number << ") of class [" << 
			object_class << "] is in file: " << object_filename.c_str() << "\n";
		
		for(int n = 0; n < 6; n++)
			std::cout << (int)obj.actions[n] << "\n";
		}
	
	/*
	struct hrObjectOptions {
    quint8 coord[3]; // x, y, z;
    quint32 objectID;
    quint8 junk[5]; // need more info
	};
	*/
	uint32_t num_objoptions = f.read_uint32();
	
	for(unsigned int i = 0; i < num_objoptions; i++)
		{
		uint8_t objx = f.read_uint8();
		uint8_t objy = f.read_uint8();
		uint8_t objz = f.read_uint8();
		uint32_t obj_id = f.read_uint32();
		
		if(obj_id == 0 && i != 0)
			continue;
			
		if(obj_id >= num_objects)
			break;
		
		uint8_t ojunk[5];
		for(int n = 0; n < 5; n++)
			ojunk[n] = f.read_uint8();
		
		objects[obj_id].x = objx;
		objects[obj_id].y = objy;
		
		switch(objects[obj_id].obj_class)
			{
			case 147: //rocks?  some sort of decoration
				{
				}
				break;
			case 103: //subterrainian gate
				break;
			
			case 134:
			case 135:
			case 137:
			case 155: //trees
			case 118: //trees? maybe mountains
				break;
				
			case 127: //lava flow? (2x2)
				break;
			
			case 150: //shrub (1x1)
				break;
				
			case 199: //single lone small tree
				break;
				
			case 206: //desert hill (1x1)
				break;
			
			case 208: //grassy hill (1x1 size?)
				break;
				
			case 207: //dirt hills (2x2 size?)
				break;
			
			case 107: //shrub
				break;
			
			case 126: //lake
				break;
				
			case 10: //keymaster's tent
				break;
			
			case 12: //campfire
				break;
			
			case 57: //obelisk
				break;
				
			case 35: //hill fort
				break;
				
			case 64: //rally flag
				break;
			
			case 100: //learning stone
				break;
				
			case 101: //treasure chest
				break;
			
			case 106: //war machine factory
				break;
			
			case 61: //star axis
				break;
			
			case 4: //arena
				break;
			
			case 51: //mercenary camp
				break;
				
			case 41: //library of enlightenment
				break;
			
			case 23: //marletto tower
				break;
			
			case 32: //garden of revalation
				break;
			
			case 25: //dragon utopia
				break;
				
			case 85: //shipwreck
				break;
				
			case 6: //pandora
				{
				}
				break;
				/*
				struct ObjectPandora {
				ObjectArtefact art;
				quint32 exp;
				qint32 spell_points;
				qint8 morals;
				qint8 luck;

				Resources_t res;

				quint8 offence;
				quint8 defence;
				quint8 power;
				quint8 knowledge;

				quint8 isSecSkills;

				//    if ( isSecSkills > 0 ) {
						QVector<SecondarySkill_t> sec_skills;

					quint8 isArtefacts;

				//    if ( artefacts > 0 ) {
						QVector<quint16> artefacts;

					quint8 isSpells;

				//    if ( isSpells > 0 ) {
						QVector<quint8> spells;

					quint8 monstres_count;

				//    if ( monstres_count > 0 ) {
						QVector<Guard_t> monstres;

					quint8 junk3[8];
				};*/
			case 26: //event
				{
				/*struct ObjectEvent {
				ObjectPandora event;
				quint8 _map.player_attributes;
				quint8 isAICan;
				quint8 disableAfterFirstDay;
				quint32 junk;
				};*/
				}
				break;
				
			case 91: //sign
				{
				/*
				struct ObjectSign {
				HString text;
				quint32 junk;
				};*/
				CL_String text = f.read_string_a();
				f.read_uint32();
				}
				break;
				
			case 219: //garrison
				{
				/*
				struct Guard_t {
				quint16 GuardID;
				quint16 GuardCount;
				};
				
				struct ObjectGarrison {
				quint32 color;
				Guard_t guards[7];
				quint8 undeleteSoldiers;
				quint32 junk[2];
				};
				*/
				uint32_t color = f.read_uint32();
				for(int i = 0; i < 7; i++)
					{
					uint16_t guard_id = f.read_uint16();
					uint16_t guard_count = f.read_uint16();
					}
				uint8_t troops_are_removable = f.read_uint8();
				f.read_uint32();
				f.read_uint32();
				}
				break;
			
			case 220: //abandoned mine
				{
				/*struct ObjectAbandonedMine {
				quint8 resources;
				quint8 junk[3];
				};*/
				uint8_t resources = f.read_uint8();
				f.read_uint8();
				f.read_uint8();
				f.read_uint8();
				}
				break;
				
			case 217: //random dwelling
				{
				/*struct ObjectLevelRandomDwelling {
					quint32 owner;
					quint32 junk;
				//  if ( junk == 0 )
					quint16 towns;
				};
				*/
				uint32_t owner = f.read_uint32();
				uint32_t alignment = f.read_uint32();
				
				if(alignment == 0)
					uint16_t allowed = f.read_uint16();
				
				//uint8_t minlvl = f.read_uint8();
				//uint8_t maxlvl = f.read_uint8();
				}
				break;
			
			case 81: //scholar
				{
				/*
				struct ObjectScientist {
					quint8 bonus_type; // FF - Random
					union {
						quint32 primaryID;
						quint32 secondaryID;
						quint32 spellID;
					};
					quint8 junk2[3];
				};
				*/
				uint8_t bonus_type = f.read_uint8();
				uint32_t id = f.read_uint32();
				uint8_t j1 = f.read_uint8();
				uint8_t j2 = f.read_uint8();
				uint8_t j3 = f.read_uint8();
				}
				break;
	
			case 88: //lvl1
			case 89: //lvl2
			case 90: //lvl3   shrine
				{
				uint32_t spell_id = f.read_uint32();
				}
				break;
			
			case 113:  //witch hut
				{
				uint32_t skills = f.read_uint32();
				}
				break;
				
			case 87:  //shipyard
				{
				uint32_t owner = f.read_uint32();
				}
				break;
			
			case 98:
			case 77: //town
				{				
				std::cout << "Town found at location: (" << (int)objx << ", " << (int)objy << ").\n";
				town_t* town = new town_t(read_town(f));
				town->map_x = objx - 2; //moar possible bugs
				town->map_y = objy;
				town->draw_x = objx - 5;
				town->draw_y = objy - 5;				
				town->name = name;
				town->alignment = (town_t::alignment_t)objects[obj_id].object_number;
				
				_map.objects.push_back(town);
				//_map.towns.push_back(town);
				
				_compute_passability(objects[obj_id].passability, objx, objy, town);
				}
				break;
				
			case 5:
			case 65:
			case 66:
			case 67:
			case 68:
			case 69: //artifact
				{
				/*
				struct ObjectArtefact {
					quint8 isText;

				//if ( isText == 1 ) {
					HString text;
				//
				//
					quint8 isGuards;
				//
				//  if ( isGuards == 1 ) {
						Guard_t guards[7];

					quint8 junk[4];
				//    }
				};
				*/
				uint8_t has_text = f.read_uint8();
				if(has_text)
					{
					f.read_string_a();
					uint8_t guarded = f.read_uint8();
					if(guarded)
						{
						;
						}
					uint32_t ajunk = f.read_uint32();
					}
				}
				break;
				
			case 76: //random resource
			case 79: //resource
				{
				/*
				struct ObjectResource {
					ObjectArtefact res;
					quint32 quantity;
					quint32 junk;
				};
				*/
				
				uint8_t has_text = f.read_uint8();
				if(has_text)
					{
					f.read_string_a();
					uint8_t guarded = f.read_uint8();
					if(guarded)
						{
						1==1;
						}
					uint32_t ajunk = f.read_uint32();
					}
				
				uint32_t quantity = f.read_uint32();
				uint32_t rjunk = f.read_uint32();
				
				std::cout << "Resource of type: " << objects[obj_id].object_number << " found in quantity of: " << quantity << " at location: (" << (int)objx << ", " << (int)objy << ").\n";
				
				if(quantity == 0)
					quantity = 4 + rand() % 4;
				
				
				resource_t* res = new resource_t;
				res->map_x = objx;
				res->map_y = objy;
				res->amount = quantity;
				if(objects[obj_id].obj_class == 76)
					res->res_type = (resource_type_e)(rand() % 7);
				else
					res->res_type = (resource_type_e)objects[obj_id].object_number;
				
				if(res->res_type == gold)
					res->amount *= 100;
				
				_map.objects.push_back(res);
				
				assert(objx+objy*_map.width >= 0);
				
				_map.index[objx+objy*_map.width] = res;
				}
				break;
			
			case 53: //mine
				{
				uint32_t color = f.read_uint32(); //??
				std::cout << "Mine found with 'color': " << color << ", type: " << objects[obj_id].object_number << " at location: (" << (int)objx << ", " << (int)objy << ").\n";
				mine_t* mine = new mine_t;
				mine->map_x = objx - 1; //moar possible bugs
				mine->map_y = objy;
				mine->mine_type = (resource_type_e)objects[obj_id].object_number;
				//mine->owner = color
				
				_map.objects.push_back(mine);
				
				_compute_passability(objects[obj_id].passability, objx, objy, mine);
				}
				break;
			
			case 17: 
			case 20:
			case 42: //lighthouse
				{
				//	ObjectDwelling dwelling;
				//	m >> dwelling;
				uint32_t owner = f.read_uint32();
				}
				break;
            
            
			case 54:
			case 71:
			case 72:
			case 73:
			case 74:
			case 75:
			case 162:
			case 163:
			case 164: //wandering army/monster
				{
				/*
				struct ObjectMonster {
					quint32 monsterID;
					quint16 monsters_count; // if 0, then random
					quint8 mood;
					quint8 isTreasureOrText;

				//  if ( isTreasureOrText == 1 ) {
						HString text;

						Resources_t res;
						quint16 artefactID;
				//  }

					quint8 monsterNeverRunAway; // 1 - yes, 0 - no
					quint8 monsterDontGrowUp; // 1 - yes, 0 - no

					quint8 junk2[2];
				};
				*/
				uint32_t id = f.read_uint32();
				uint16_t count = f.read_uint16();
				
				uint8_t disposition = f.read_uint8();
				uint8_t loot = f.read_uint8();
				if(loot)
					{
					break;
					}
				uint8_t never_flees = f.read_uint8();
				uint8_t never_grows = f.read_uint8();
				
				uint8_t jnk1 = f.read_uint8();
				uint8_t jnk2 = f.read_uint8();
				
				wandering_army_t* army = new wandering_army_t;
				army->map_x = objx;
				army->map_y = objy;
				_map.objects.push_back(army);
				_compute_passability(objects[obj_id].passability, objx, objy, army);
				
				std::cout << "Monster of type: " << objects[obj_id].object_number << " found in quantity of: " << count << " at location: (" << (int)objx << ", " << (int)objy << ") [id: " << obj_id << ", i: " << i << "].\n";
				}
				break;
			
			default:
				{
				std::cout << "Unknown object of type: " << objects[obj_id].obj_class << " encountered at location: (" << (int)objx << ", " << (int)objy << ") [id: " << obj_id << ", i: " << i << "].\n";
				object_t* obj = new object_t((object_types_e) objects[i].obj_class);
				obj->map_y = objects[i].y;
				obj->map_x = objects[i].x;
				_map.objects.push_back(obj);
				//return false;
				}
				break;
			}
		}
	
		
	/*	
	uint32 gevents_quantity;

	globalEvent gevents[gevents_quantity] <optimize=false>;
	
	struct globalEvent {
    hstring name;
    hstring text;

    int32 resources[7];

    uchar _map.player_attributes_affected;
    uchar human_affected;
    uchar ai_affected;

    ushort day_of_first_event;
    ushort event_iteration;

    char junk[16];
	};
	*/
	
	return true;
	}


void game_t::_compute_passability(unsigned char arr[6], int objx, int objy, object_t* obj)
	{
	//objx objy are lower right coordinates	
	for(int i = 0; i < 6; i++)
		{
		uint8_t bitmap = arr[i];
		for(int n = 0; n < 8; n++)
			{
			int loc = (objx - 7 + n) + ((objy - 5 + i) * _map.width);
			if(loc < 0 || loc > _map.width * _map.height)
				continue;
			
			if(!((1 << n) & bitmap))
				_map.index[loc]	= obj;
			}		
		}
	
	}

