#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "game.h"
#include <ClanLib/core.h>

#include "xbrz.h"
//gotta change this to use 'stdint'/'cstdint'
//typedef cl_int32 int32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/*enum OBJ_TILESET : __int8
{
  TILESET_HAUNTED = 10,
  TILESET_ARTIFACT = 11,
  TILESET_MONSTER = 12,
  TILESET_ARTIFACT_TAKEN = 13,
  TILESET_FLAG = 14,
  TILESET_RESOURCE_DISPLAY = 15,
  TILESET_HOURGLASS = 16,
  TILESET_ROUTE = 17,
  TILESET_STONBACK = 19,
  TILESET_MONSTER_ANIMATION = 20,
  TILESET_HERO = 21,
  TILESET_SNOW_MOUNTAIN = 22,
  TILESET_SWAMP_MOUNTAIN = 23,
  TILESET_LAVA_MOUNTAIN = 24,
  TILESET_DESERT_MOUNTAIN = 25,
  TILESET_DIRT_MOUNTAIN = 26,
  TILESET_MOUNTAIN_MULTIPLE = 27,
  TILESET_EXTRA_OVERLAY = 29,
  TILESET_ROAD = 30,
  TILESET_MOUNTAIN_CRACKED = 31,
  TILESET_MOUNTAIN_GRASS = 32,
  TILESET_TREE_JUNGLE = 33,
  TILESET_TREE_EVIL = 34,
  TILESET_OBJ_TOWN = 35,
  TILESET_TOWN_TERRAIN = 36,
  TILESET_TOWN_SHADOW = 37,
  TILESET_TOWN_RANDOM = 38,
  TILESET_OBJECT_EXTRA = 39,
  TILESET_OBJECT_WATER_2 = 40,
  TILESET_OBJECT_MULTIPLE_2 = 41,
  TILESET_OBJECT_TREE_SNOW = 42,
  TILESET_OBJECT_TREE_FIR = 43,
  TILESET_OBJECT_TREE_FALL = 44,
  TILESET_OBJECT_STREAM = 45,
  TILESET_OBJECT_RESOURCE = 46,
  TILESET_OBJECT_DUMMY = 47,
  TILESET_OBJECT_GRASS_2 = 48,
  TILESET_OBJECT_TREE_DECIDUOUS = 49,
  TILESET_OBJECT_WATER = 50,
  TILESET_OBJECT_GRASS = 51,
  TILESET_OBJECT_SNOW = 52,
  TILESET_OBJECT_SWAMP = 53,
  TILESET_OBJECT_LAVA = 54,
  TILESET_OBJECT_DESERT = 55,
  TILESET_OBJECT_DIRT = 56,
  TILESET_OBJECT_CRACKED = 57,
  TILESET_OBJECT_LAVA_3 = 58,
  TILESET_OBJECT_MULTIPLE = 59,
  TILESET_OBJECT_LAVA_2 = 60,
  TILESET_OBJECT_EXPANSION_1 = 61,
  TILESET_OBJECT_EXPANSION_2 = 62,
  TILESET_OBJECT_EXPANSION_3 = 63,
};*/

namespace ICN
{
    enum icn_type_e
		{
		UNKNOWN = 0,
	    OBJNARTI = 0x2C, MONS32 = 0x30, FLAG32 = 0x38, MINIHERO = 0x54,
		MTNSNOW = 0x58, MTNSWMP = 0x5C, MTNLAVA = 0x60, MTNDSRT = 0x64, 
		MTNDIRT = 0x68, MTNMULT = 0x6C, EXTRAOVR = 0x74, ROAD = 0x78, 
		MTNCRCK = 0x7C, MTNGRAS = 0x80, TREJNGL = 0x84, TREEVIL = 0x88, 
		OBJNTOWN = 0x8C, OBJNTWBA = 0x90, OBJNTWSH = 0x94, OBJNTWRD = 0x98, 
		OBJNWAT2 = 0xA0, OBJNMUL2 = 0xA4, TRESNOW = 0xA8, TREFIR = 0xAC,
		TREFALL = 0xB0, STREAM = 0xB4, OBJNRSRC = 0xB8, OBJNGRA2 = 0xC0,
		TREDECI = 0xC4, OBJNWATR = 0xC8, OBJNGRAS = 0xCC, OBJNSNOW = 0xD0,
		OBJNSWMP = 0xD4, OBJNLAVA = 0xD8, OBJNDSRT = 0xDC, OBJNDIRT = 0xE0,
		OBJNCRCK = 0xE4, OBJNLAV3 = 0xE8, OBJNMULT = 0xEC, OBJNLAV2 = 0xF0,
		X_LOC1 = 0xF4, X_LOC2 = 0xF8, X_LOC3 = 0xFC 
		};
	//const std::string transcribe(icn_type_e icn);
}



/*
char *cEvilTranslate[37][2] =
{
{ "advbord.icn", "advborde.icn" },
{ "heroextg.icn", "heroexte.icn" },
{ "buybuild.icn", "buybuile.icn" },
{ "advbtns.icn", "advebtns.icn" },
{ "herologo.icn", "herologe.icn" },
{ "sunmoon.icn", "sunmoone.icn" },
{ "stonback.icn", "stonbake.icn" },
{ "scroll.icn", "scrolle.icn" },
{ "locators.icn", "locatore.icn" },
{ "system.icn", "systeme.icn" },    //////0-9 in gTilesetFiles[]
{ "CPANBKG.ICN", "CPANBKGE.ICN" },
{ "CPANEL.ICN", "CPANELE.ICN" },
{ "APANBKG.ICN", "APANBKGE.ICN" },
{ "APANEL.ICN", "APANELE.ICN" },
{ "VIEWWRLD.ICN", "EVIWWRLD.ICN" },
{ "VIEWRSRC.ICN", "EVIWRSRC.ICN" },
{ "VIEWRTFX.ICN", "EVIWRTFX.ICN" },
{ "VIEWTWNS.ICN", "EVIWTWNS.ICN" },
{ "VIEWHROS.ICN", "EVIWHROS.ICN" },
{ "VIEW_ALL.ICN", "EVIW_ALL.ICN" },
{ "VIEWMINE.ICN", "EVIWMINE.ICN" },
{ "VIEWDDOR.ICN", "EVIWDDOR.ICN" },
{ "VIEWPUZL.ICN", "EVIWPUZL.ICN" },
{ "LGNDXTRA.ICN", "LGNDXTRE.ICN" },
{ "SPANBKG.ICN", "SPANBKGE.ICN" },
{ "SPANBTN.ICN", "SPANBTNE.ICN" },
{ "CSPANBKG.ICN", "CSPANBKE.ICN" },
{ "CSPANBTN.ICN", "CSPANBTE.ICN" },
{ "TRADPOST.ICN", "TRADPOSE.ICN" },
{ "VIEWARMY.ICN", "VIEWARME.ICN" },
{ "WINLOSE.ICN", "WINLOSEE.ICN" },
{ "WINCMBTB.ICN", "WINCMBBE.ICN" },
{ "SURRENDR.ICN", "SURRENDE.ICN" },
{ "SURDRBKG.ICN", "SURDRBKE.ICN" },
{ "VGENBKG.ICN", "VGENBKGE.ICN" },
{ "campbkgg.ICN", "campbkge.ICN" },
{ "campxtrg.ICN", "campxtre.ICN" }
};
*/
/*


























































char *gTilesetFiles[] =
{
&unk_4F74C0,
&unk_4F74C4,
&unk_4F74C8,
&unk_4F74CC,
&unk_4F74D0,
&unk_4F74D4,
&unk_4F74D8,
&unk_4F74DC,
&unk_4F74E0,
&unk_4F74E4,
"objnhaun.icn",
"objnarti.icn",
"mons32.icn",
"art32.icn",
"flag32.icn",
"ressmall.icn",
"hourglas.icn",
"route.icn",
&unk_4F7558,
"stonback.icn",
"minimon.icn",
"minihero.icn",
"mtnsnow.icn",
"mtnswmp.icn",
"mtnlava.icn",
"mtndsrt.icn",
"mtndirt.icn",
"mtnmult.icn",
&unk_4F75D0,
"extraovr.icn",
"road.icn",
"mtncrck.icn",
"mtngras.icn",
"trejngl.icn",
"treevil.icn",
"objntown.icn",
"objntwba.icn",
"objntwsh.icn",
"objntwrd.icn",
"objnxtra.icn",
"objnwat2.icn",
"objnmul2.icn",
"tresnow.icn",
"trefir.icn",
"trefall.icn",
"stream.icn",
"objnrsrc.icn",
"dummy.icn",
"objngra2.icn",
"tredeci.icn",
"objnwatr.icn",
"objngras.icn",
"objnsnow.icn",
"objnswmp.icn",
"objnlava.icn",
"objndsrt.icn",
"objndirt.icn",
"objncrck.icn",
"objnlav3.icn",
"objnmult.icn",
"objnlav2.icn",
"x_loc1.icn",
"x_loc2.icn",
"x_loc3.icn"
};
*/

ICN::icn_type_e get_icn_type(int type)
	{
	switch(type & 0xFC) //is this needed because of a bitfield somewhere?
		{
		// artifact
		case 0x2C: return ICN::OBJNARTI;
			// monster
		case 0x30: return ICN::MONS32;
			// castle flags
		case 0x38: return ICN::FLAG32;
			// heroes
		case 0x54: return ICN::MINIHERO;
			// relief: snow
		case 0x58: return ICN::MTNSNOW;
			// relief: swamp
		case 0x5C: return ICN::MTNSWMP;
			// relief: lava
		case 0x60: return ICN::MTNLAVA;
			// relief: desert
		case 0x64: return ICN::MTNDSRT;
			// relief: dirt
		case 0x68: return ICN::MTNDIRT;
			// relief: others
		case 0x6C: return ICN::MTNMULT;
			// mines
		case 0x74: return ICN::EXTRAOVR;
			// road
		case 0x78: return ICN::ROAD;
			// relief: crck
		case 0x7C: return ICN::MTNCRCK;
			// relief: gras
		case 0x80: return ICN::MTNGRAS;
			// trees jungle
		case 0x84: return ICN::TREJNGL;
			// trees evil
		case 0x88: return ICN::TREEVIL;
			// castle and tower
		case 0x8C: return ICN::OBJNTOWN;
			// castle lands
		case 0x90: return ICN::OBJNTWBA;
			// castle shadow
		case 0x94: return ICN::OBJNTWSH;
			// random castle
		case 0x98: return ICN::OBJNTWRD;
			// water object
		case 0xA0: return ICN::OBJNWAT2;
			// object other
		case 0xA4: return ICN::OBJNMUL2;
			// trees snow
		case 0xA8: return ICN::TRESNOW;
			// trees trefir
		case 0xAC: return ICN::TREFIR;
			// trees
		case 0xB0: return ICN::TREFALL;
			// river
		case 0xB4: return ICN::STREAM;
			// resource
		case 0xB8: return ICN::OBJNRSRC;
			// gras object
		case 0xC0: return ICN::OBJNGRA2;
			// trees tredeci
		case 0xC4: return ICN::TREDECI;
			// sea object
		case 0xC8: return ICN::OBJNWATR;
			// vegetation gras                                            
		case 0xCC: return ICN::OBJNGRAS;
			// object on snow                                             
		case 0xD0: return ICN::OBJNSNOW;
			// object on swamp                                            
		case 0xD4: return ICN::OBJNSWMP;
			// object on lava                                             
		case 0xD8: return ICN::OBJNLAVA;
			// object on desert                                           
		case 0xDC: return ICN::OBJNDSRT;
			// object on dirt                                             
		case 0xE0: return ICN::OBJNDIRT;
			// object on crck
		case 0xE4: return ICN::OBJNCRCK;
			// object on lava
		case 0xE8: return ICN::OBJNLAV3;
			// object on earth
		case 0xEC: return ICN::OBJNMULT;
			//  object on lava                                            
		case 0xF0: return ICN::OBJNLAV2;
			// extra objects for loyalty version
		case 0xF4: return ICN::X_LOC1;
			// extra objects for loyalty version
		case 0xF8: return ICN::X_LOC2;
			// extra objects for loyalty version
		case 0xFC: return ICN::X_LOC3;
			// unknown
		default: 
			std::cerr << "H2::MP2ICN: unknown object:" << type;
			break;
		}

	return ICN::UNKNOWN;
	}

const std::string transcribe(ICN::icn_type_e type)
	{
	switch(type)
		{
		case ICN::OBJNARTI: return "OBJNARTI.ICN";
		case ICN::MONS32: return "MONS32.ICN";
		case ICN::FLAG32: return "FLAG32.ICN";
		case ICN::MINIHERO: return "MINIHERO.ICN";
		case ICN::MTNSNOW: return "MTNSNOW.ICN";
		case ICN::MTNSWMP: return "MTNSWMP.ICN";
		case ICN::MTNLAVA: return "MTNLAVA.ICN";
		case ICN::MTNDSRT: return "MTNDSRT.ICN";
		case ICN::MTNDIRT: return "MTNDIRT.ICN";
		case ICN::MTNMULT: return "MTNMULT.ICN";
		case ICN::EXTRAOVR: return "EXTRAOVR.ICN";
		case ICN::ROAD: return "ROAD.ICN";
		case ICN::MTNCRCK: return "MTNCRCK.ICN";
		case ICN::MTNGRAS: return "MTNGRAS.ICN";
		case ICN::TREJNGL: return "TREJNGL.ICN";
		case ICN::TREEVIL: return "TREEVIL.ICN";
		case ICN::OBJNTOWN: return "OBJNTOWN.ICN";
		case ICN::OBJNTWBA: return "OBJNTWBA.ICN";
		case ICN::OBJNTWSH: return "OBJNTWSH.ICN";
		case ICN::OBJNTWRD: return "OBJNTWRD.ICN";
		case ICN::OBJNWAT2: return "OBJNWAT2.ICN";
		case ICN::OBJNMUL2: return "OBJNMUL2.ICN";
		case ICN::TRESNOW: return "TRESNOW.ICN";
		case ICN::TREFIR: return "TREFIR.ICN";
		case ICN::TREFALL: return "TREFALL.ICN";
		case ICN::STREAM: return "STREAM.ICN";
		case ICN::OBJNRSRC: return "OBJNRSRC.ICN";
		case ICN::OBJNGRA2: return "OBJNGRA2.ICN";
		case ICN::TREDECI: return "TREDECI.ICN";
		case ICN::OBJNWATR: return "OBJNWATR.ICN";
		case ICN::OBJNGRAS: return "OBJNGRAS.ICN";
		case ICN::OBJNSNOW: return "OBJNSNOW.ICN";
		case ICN::OBJNSWMP: return "OBJNSWMP.ICN";
		case ICN::OBJNLAVA: return "OBJNLAVA.ICN";
		case ICN::OBJNDSRT: return "OBJNDSRT.ICN";
		case ICN::OBJNDIRT: return "OBJNDIRT.ICN";
		case ICN::OBJNCRCK: return "OBJNCRCK.ICN";
		case ICN::OBJNLAV3: return "OBJNLAV3.ICN";
		case ICN::OBJNMULT: return "OBJNMULT.ICN";
		case ICN::OBJNLAV2: return "OBJNLAV2.ICN";
		case ICN::X_LOC1: return "X_LOC1.ICN";
		case ICN::X_LOC2: return "X_LOC2.ICN";
		case ICN::X_LOC3: return "X_LOC3.ICN";
			// unknown
		default: break;
		}

	return nullptr;
	}

int game_t::_get_number_of_animation_frames(const object_t& obj)
	{


	return 0;
	}

bool game_t::_load_h2_object(int type, int index)
	{
	std::pair<int, int> obj_id(type, index);
	if(_h2_objects.count(obj_id) || get_icn_type(type) == ICN::UNKNOWN)
		return false;

	const std::string directory = "h2objects";
	std::string subdirectory = transcribe(get_icn_type(type)) + ".cadres";

	std::stringstream strm;
	//strm << "hr-" << std::setfill('0') << std::setw(3) << i << ".png";
	strm << std::setfill('0') << std::setw(4) << index << "_4x.png";
	string fname = directory + "/" + subdirectory + "/" + strm.str();
	CL_FileHelp fh;
	if(!fh.file_exists(fname))
		return false;
	_h2_objects[obj_id] = CL_Sprite(_gc, fname);
	return true;
	}

bool game_t::_load_h2_objects()
	{
	//for
	const std::string directory = "h2objects";
	std::string subdirectory = "220";
	const int num_objndsrt = 130;

	for(int i = 0; i < num_objndsrt; i++)
		{
		std::stringstream strm;
		strm << "hr-" << std::setfill('0') << std::setw(3) << i << ".png";
		string fname = directory + "/" + subdirectory + "/" + strm.str();

		std::pair<int, int> obj_id(220, i);
		_h2_objects[obj_id] = CL_Sprite(_gc, fname);
		}

	subdirectory = "106";
	const int num_mtndirt = 113;
	for(int i = 0; i < num_mtndirt; i++)
		{
		std::stringstream strm;
		strm << "hr-" << std::setfill('0') << std::setw(3) << i << ".png";
		string fname = directory + "/" + subdirectory + "/" + strm.str();

		std::pair<int, int> obj_id(106, i);
		_h2_objects[obj_id] = CL_Sprite(_gc, fname);
		}

	return true;
	}
