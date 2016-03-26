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


int get_h2_mp2_icn(int type)
	{
	return false;
	/*int H2::MP2ICN(int type, bool warn)
{
    switch(type & 0xFC)
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
	default: if(warn) qWarning() << "H2::MP2ICN: unknown object:" << type; break;
    }

    return ICN::UNKNOWN;
}*/
	}


bool game_t::_load_heroes2_map(const std::string& filename)
	{
	CL_File f(filename);
	if(f.is_null())
		return false;

	/*
	// magic byte
	fd.read(reinterpret_cast<char *>(&byte32), sizeof(byte32));
	SwapLE32(byte32);

	if(byte32 != 0x0000005C)
		{
		DEBUG(DBG_GAME, DBG_WARN, "incorrect maps file " << filename);
		fd.close();
		return false;
		}
		*/

	int32_t magic = f.read_int32();
	if(magic != 0x0000005C)
		{
		std::cerr << "Unsupported map type\n";
		return false;
		}

	/*
	// level
	fd.read(reinterpret_cast<char *>(&byte16), sizeof(byte16));
	SwapLE16(byte16);

	switch(byte16)
		{
		case 0x00:
			difficulty = Difficulty::EASY;
			break;

		case 0x01:
			difficulty = Difficulty::NORMAL;
			break;

		case 0x02:
			difficulty = Difficulty::HARD;
			break;

		case 0x03:
			difficulty = Difficulty::EXPERT;
			break;

		default:
			DEBUG(DBG_GAME, DBG_WARN, "incorrect difficulty" << ", maps: " << filename << ", load easy default");
			break;
		}
		*/
	uint16_t difficulty = f.read_uint16();

	switch(difficulty)
		{
		case 0:
			_map.difficulty = easy;
			break;
		case 1:
			_map.difficulty = normal;
			break;
		case 2:
			_map.difficulty = hard;
			break;
		case 3:
			_map.difficulty = expert;
			break;
		}

	std::clog << "map difficulty: " << (int)difficulty << "\n";

	/*

	// width
	fd.read(reinterpret_cast<char *>(&byte8), 1);
	size_w = byte8;

	// height
	fd.read(reinterpret_cast<char *>(&byte8), 1);
	size_h = byte8;

	*/
	uint8_t width = f.read_uint8();
	uint8_t height = f.read_uint8();
	
	_map.width = width;
	_map.height = height;

	//check validity of width and height values
	if(width > 1000 || width <= 0 || height > 1000 || height <= 0)
		{
		std::cerr << "Map size invalid\n";
		return false;
		}

	std::clog << "map size is: (" << (int)width << ", " << (int)height << ")\n";

	/*
	// kingdom color: blue, gree, red, yellow, orange, purple
	for(int ii = 0; ii < 6; ++ii)
	kingdomColor[ii] = map.readByte();


	// kingdom color blue
	fd.read(reinterpret_cast<char *>(&byte8), 1);
	if(byte8) kingdom_colors |= Color::BLUE;

	// kingdom color green
	fd.read(reinterpret_cast<char *>(&byte8), 1);
	if(byte8) kingdom_colors |= Color::GREEN;
	...

	*/

	//6 colors in h2 maps
	for(size_t i = 0; i < 6; i++)
		{
		uint8_t kingdom_color = f.read_uint8();
		_map.player_attributes[i].is_playable = kingdom_color & 1;
		}

	/* // allow human blue
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    if(byte8) allow_human_colors |= Color::BLUE;
	...
	*/
	for(size_t i = 0; i < 6; i++)
		{
		uint8_t kingdom_color = f.read_uint8();
		_map.player_attributes[i].human_allowed = kingdom_color & 1;
		}

	/*
    // allow comp blue
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    if(byte8) allow_comp_colors |= Color::BLUE;
	*/
	for(size_t i = 0; i < 6; i++)
		{
		uint8_t kingdom_color = f.read_uint8();
		_map.player_attributes[i].computer_allowed = kingdom_color & 1;
		}

	/* // kingdom count
    // fd.seekg(0x1A, std::ios_base::beg);
    // fd.read(&byte8, 1);
	*/

	uint8_t kingdom_count = f.read_uint8();

	/* // wins
    fd.seekg(0x1D, std::ios_base::beg);
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    conditions_wins = byte8;

    // data wins
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    wins1 = byte8;
    // data wins
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    wins2 = byte8;
    // data wins
    fd.read(reinterpret_cast<char *>(&byte16), 2);
    SwapLE16(byte16);
    wins3 = byte16;
    // data wins
    fd.seekg(0x2c, std::ios_base::beg);
    fd.read(reinterpret_cast<char *>(&byte16), 2);
    SwapLE16(byte16);
    wins4 = byte16;

    // loss
    fd.seekg(0x22, std::ios_base::beg);
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    conditions_loss = byte8;
    // data loss
    fd.read(reinterpret_cast<char *>(&byte16), 2);
    SwapLE16(byte16);
    loss1 = byte16;
    // data loss
    fd.seekg(0x2e, std::ios_base::beg);
    fd.read(reinterpret_cast<char *>(&byte16), 2);
    SwapLE16(byte16);
    loss2 = byte16;
	*/





	/* // start with hero
    fd.seekg(0x25, std::ios_base::beg);
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    with_heroes = 0 == byte8;
	*/



	/*// race color
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    races[0] = ByteToRace(byte8);
    if(Race::RAND == races[0]) rnd_races |= Color::BLUE;
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    races[1] = ByteToRace(byte8);
    if(Race::RAND == races[1]) rnd_races |= Color::GREEN;
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    races[2] = ByteToRace(byte8);
    if(Race::RAND == races[2]) rnd_races |= Color::RED;
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    races[3] = ByteToRace(byte8);
    if(Race::RAND == races[3]) rnd_races |= Color::YELLOW;
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    races[4] = ByteToRace(byte8);
    if(Race::RAND == races[4]) rnd_races |= Color::ORANGE;
    fd.read(reinterpret_cast<char *>(&byte8), 1);
    races[5] = ByteToRace(byte8);
    if(Race::RAND == races[5]) rnd_races |= Color::PURPLE;

	*/


	/*   // name
    char bufname[LENGTHNAME];
    fd.seekg(0x3A, std::ios_base::beg);
    fd.read(bufname, LENGTHNAME);
    bufname[LENGTHNAME - 1] = 0;
    name = Game::GetEncodeString(bufname);

    // description
    char bufdescription[LENGTHDESCRIPTION];
    fd.seekg(0x76, std::ios_base::beg);
    fd.read(bufdescription, LENGTHDESCRIPTION);
    bufdescription[LENGTHDESCRIPTION - 1] = 0;
    description = Game::GetEncodeString(bufdescription);
	*/

	//#define LENGTHNAME		16
	//#define LENGTHDESCRIPTION	143
	const int NAME_LENGTH = 16;
	const int DESCRIPTION_LENGTH = 143;
	f.seek(0x3A, f.seek_set);

	char name_buf[NAME_LENGTH + 1];
	name_buf[NAME_LENGTH] = '\0';
	f.read(&name_buf, NAME_LENGTH);
	
	_map.name = name_buf;
	std::clog << "map name: '" << _map.name << "'\n";

	char desc_buf[DESCRIPTION_LENGTH + 1];
	f.seek(0x76, f.seek_set);
	desc_buf[DESCRIPTION_LENGTH] = '\0';
	f.read(&desc_buf, DESCRIPTION_LENGTH);

	_map.description = desc_buf;
	std::clog << "map description: '" << _map.description << "'\n";

	/*	// data map: width, heigth
	map.seek(0x01A4);
	if(static_cast<int>(map.readLE32()) != size.width())
	{
	    qDebug() << "MP2Format::loadMap:" << "incorrect size";
    	    return false;
	}
	if(static_cast<int>(map.readLE32()) != size.height())
	{
	    qDebug() << "MP2Format::loadMap:" << "incorrect size";
    	    return false;
	}
	*/

	f.seek(0x01A4, f.seek_set);
	uint32_t tiles_width = f.read_uint32();
	uint32_t tiles_height = f.read_uint32();
	
	if(tiles_width != _map.width || tiles_height != _map.height)
		{
		std::cerr << "tile width/height does not match with map width/height\n";
		return false;
		}
	
	/*
	// data map: mp2tile, part1
	// count blocks: width * heigth
	tiles.resize(size.width() * size.height());

	for(QVector<mp2til_t>::iterator
	    it = tiles.begin(); it != tiles.end(); ++it)
		{
	    QDataStream ds(map.read(20));
	    ds >> (*it);
		}

	QDataStream & operator>> (QDataStream & ds, mp2til_t & til)
		{
		ds.setByteOrder(QDataStream::LittleEndian);
		til.ext.quantity = 0;
		return ds >> til.tileSprite >>
		til.ext.level1.object >> til.ext.level1.index >>
		til.quantity1 >> til.quantity2 >>
		til.ext.level2.object >> til.ext.level2.index >>
		til.tileShape >> til.objectID >>
		til.ext.indexExt >> til.ext.level1.uniq >> til.ext.level2.uniq;
		}

	QDataStream & operator>> (QDataStream & ds, mp2ext_t & ext)
		{
		ds.setByteOrder(QDataStream::LittleEndian);
		ds >> ext.indexExt >> ext.level1.object >> ext.level1.index >>
		ext.quantity >> ext.level2.object >> ext.level2.index >> ext.level1.uniq >> ext.level2.uniq;
		ext.level1.object *= 2;
		return ds;
		}

	*/

	/*
	struct mp2lev_t
		{
		mp2lev_t();

		quint8	object;
		quint8	index;
		quint32	uniq;
		};

	struct mp2ext_t
		{
		mp2ext_t();

		quint16     indexExt;
		quint8      quantity;
		mp2lev_t	level1;
		mp2lev_t	level2;
		};

	struct mp2til_t
		{
		mp2til_t();

		quint16     tileSprite;
		quint8      quantity1;
		quint8      quantity2;
		quint8      tileShape;
		quint8      objectID;
		mp2ext_t	ext;
		};
	*/

	struct ext_obj_t
		{
		uint8_t object;
		uint8_t index;
		uint32_t unique_id;
		};

	ext_obj_t elvl1, elvl2;

	std::vector<int> vec_object;
	//std::vector<MP2::mp2tile_t> map_tiles;
	//map_tiles.reserve(_map.width * _map.height);
	_map.h2_mp2_tiles.reserve(_map.width * _map.height);
	_map.map_tiles.resize(_map.width * _map.height);
	MP2::mp2tile_t mp2tile;

	const unsigned int ANIMATION_MASK = 1;

	int num_blocks = tiles_width * tiles_height;
	for(int i = 0; i < num_blocks; i++)
		{
		/*struct mapCell
			{
			__int16 groundIndex;
			char bitfield_1_hasObject_1_isRoad_6_objTileset;
			__int8 objectIndex;
			unsigned __int16 field_4_1_1_isShadow_1_13_extraInfo;
			char field__1_hasOverlay_1_hasLateOverlay_6_overlayTileset;
			char overlayIndex;
			char displayFlags;
			char objType;
			__int16 extraIdx;
			int objLink;
			int ovrLink;
			};*/
		mp2tile.tileIndex = f.read_uint16();
		mp2tile.objectName1 = f.read_uint8();
		mp2tile.indexName1 = f.read_uint8();
		mp2tile.quantity1 = f.read_uint16();
		mp2tile.quantity2 = 0;
		//mp2tile.quantity1 = f.read_uint8();
		//mp2tile.quantity2 = f.read_uint8();
		mp2tile.objectName2 = f.read_uint8();
		mp2tile.indexName2 = f.read_uint8();
		mp2tile.shape = f.read_uint8();
		mp2tile.generalObject = f.read_uint8();
		// offset first addon
		size_t offsetAddonsBlock = f.read_uint16();
		mp2tile.indexAddon = offsetAddonsBlock;

		mp2tile.uniqNumber1 = f.read_uint32();
		mp2tile.uniqNumber2 = f.read_uint32();


		MP2::obj_type_e genobj_type = MP2::obj_type_e(mp2tile.generalObject);

		_map.h2_mp2_tiles.push_back(mp2tile);

		switch(mp2tile.generalObject)
			{
			case MP2::OBJ_RNDTOWN:
			case MP2::OBJ_RNDCASTLE:
			case MP2::OBJ_CASTLE:
			case MP2::OBJ_HEROES:
			case MP2::OBJ_SIGN:
			case MP2::OBJ_BOTTLE:
			case MP2::OBJ_EVENT:
			case MP2::OBJ_SPHINX:
			case MP2::OBJ_JAIL:
				vec_object.push_back(i);
			}


		/*
		return ds >> til.tileSprite >>

		til.ext.level1.object >> til.ext.level1.index >>
		til.quantity1 >> til.quantity2 >>
		//
		til.ext.level2.object >> til.ext.level2.index >>
		til.tileShape >> til.objectID >>


		til.ext.indexExt >> til.ext.level1.uniq >> til.ext.level2.uniq;
		*/
		
		/*
		//std::clog << "tile(" << i << "):\t";
		uint16_t sprite = f.read_uint16();
	
		elvl1.object = f.read_uint8();
		elvl1.index = f.read_uint8();
		uint8_t quantity1 = f.read_uint8();
		uint8_t quantity2 = f.read_uint8();
		//
		elvl2.object = f.read_uint8();
		elvl2.index = f.read_uint8();
		uint8_t shape = f.read_uint8();
		uint8_t object_id = f.read_uint8();

		uint16_t ext_index = f.read_uint16();
		elvl1.unique_id = f.read_uint32();
		elvl2.unique_id = f.read_uint32();
		*/
		//std::clog << "[" << (int)sprite << "]: <" << (int)quantity1 << ", " << (int)quantity2
		//	<< ", " << (int)shape << ", " << (int)object_id << ">\n";


		/*if(elvl1.unique_id != 0)
			{
			object_t obj;
			//obj.h2_id = MP2::obj_type_e(elvl1.unique_id);
			obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(elvl1.object, elvl1.index);
			obj.map_x = i % (_map.width);
			obj.map_y = i / (_map.width);
			_map.objects.push_back(new object_t(obj));
			}

		if(elvl2.unique_id != 0)
			{
			object_t obj;
			//obj.h2_id = MP2::obj_type_e(elvl2.unique_id);
			obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(elvl2.object, elvl2.index);
			obj.map_x = i % (_map.width);
			obj.map_y = i / (_map.width);
			_map.objects.push_back(new object_t(obj));
			}
			*/
		map_t::tile_t tile;
		tile.type = mp2tile.tileIndex;
		tile.subtype = mp2tile.shape;

		//if(mp2tile.objectName1 & 0xf0)
		if(mp2tile.objectName1 != 0)
			{
			object_t obj;
			obj.draw_layer = mp2tile.quantity1;
			obj.level = 0;
			obj.is_animated = (mp2tile.objectName1 & ANIMATION_MASK);
			obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(
				MP2::obj_type_e(mp2tile.objectName1),														MP2::obj_type_e(mp2tile.indexName1)
				);
			obj.map_x = i % (_map.width);
			obj.map_y = i / (_map.width);

			_map.objects.push_back(new object_t(obj));
			_map.map_tiles[i].objects.push_back(obj);
			}

		if(mp2tile.objectName2 != 0)
			{
			object_t obj;
			obj.draw_layer = mp2tile.quantity1;
			obj.level = 1;
			obj.is_animated = (mp2tile.objectName2 & ANIMATION_MASK);
			obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(
				MP2::obj_type_e(mp2tile.objectName2), MP2::obj_type_e(mp2tile.indexName2)
				);
			obj.map_x = i % (_map.width);
			obj.map_y = i / (_map.width);

			_map.objects.push_back(new object_t(obj));
			_map.map_tiles[i].objects.push_back(obj);
			}

		//tile.type = sprite;
		//tile.subtype = shape;
		_map.terrain.push_back(tile);
		}
	/*
	// data map: mp2ext, part2
	// count blocks: 4 byte
	sprites.resize(map.readLE32());

	for(QVector<mp2ext_t>::iterator
		it = sprites.begin(); it != sprites.end(); ++it)
		{
		QDataStream ds(map.read(15));
		ds >> (*it);
		}

		QDomElement & operator>> (QDomElement & el, MapTileExt & ext)
		{
		ext.spriteICN = el.attribute("icn").toInt();
		ext.spriteExt = el.attribute("ext").toInt();
		ext.spriteIndex = el.attribute("index").toInt();
		ext.spriteLevelInt = el.attribute("level").toInt();
		ext.spriteUID = el.attribute("uid").toInt();

		return el;
		}
	*/

	uint32_t num_addons = f.read_uint32();

	std::vector<MP2::mp2addon_t> addons;
	addons.reserve(num_addons);

	for(int i = 0; i < num_addons; i++)
		{
		/*struct mapCellExtra
			{
			__int16 nextIdx;
			char _1_animatedObject_7_objTileset;
			signed __int8 objectIndex;
			char field_4_1_1_1_isShadow_5;
			char _1_animatedLateOverlay_1_hasLateOverlay_6_lateOverlayTileset;
			char overlayIndex;
			int objLink;
			int ovrLink;
			};
		*/
		MP2::mp2addon_t mp2addon;

		mp2addon.indexAddon = f.read_uint16();

		mp2addon.objectNameN1 = f.read_uint8();
		mp2addon.indexNameN1 = f.read_uint8();
		mp2addon.quantityN = f.read_uint8();
		mp2addon.objectNameN2 = f.read_uint8();
		mp2addon.indexNameN2 = f.read_uint8();

		mp2addon.uniqNumberN1 = f.read_uint32();
		mp2addon.uniqNumberN2 = f.read_uint32();

		addons.push_back(mp2addon);
		_map.h2_mp2_addon_tiles.push_back(mp2addon);

/*
		object_t obj;
		obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(MP2::obj_type_e(mp2addon.objectNameN1),														MP2::obj_type_e(mp2addon.objectNameN2));
		obj.map_x = i % (_map.width);
		obj.map_y = i / (_map.width);
		_map.objects.push_back(new object_t(obj));*/
		}

	int num_addons_referenced = 0;
	int num_addons_with_nextid = 0;
	for(int i = 0; i < num_blocks; i++)
		{
		int addindex = _map.h2_mp2_tiles[i].indexAddon;
		if(addindex == 0)
			continue;
		if(addindex >= num_addons)
			continue;

		int next_id = addindex;
		do
			{
			MP2::mp2addon_t& mp2addon = addons[next_id];
			if(mp2addon.objectNameN1 != 0)
				{
				object_t obj;
				obj.draw_layer = mp2addon.quantityN;
				obj.level = 0;
				obj.is_animated = (mp2addon.objectNameN1 & ANIMATION_MASK);
				obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(
					MP2::obj_type_e(mp2addon.objectNameN1 << 1), MP2::obj_type_e(mp2addon.indexNameN1)
					);
				obj.map_x = i % (_map.width);
				obj.map_y = i / (_map.width);

				_map.map_tiles[i].objects.push_back(obj);
				}
			if(mp2addon.objectNameN2 != 0)
				{
				object_t obj;
				obj.draw_layer = mp2addon.quantityN;
				obj.level = 1;
				obj.is_animated = (mp2addon.objectNameN2 & ANIMATION_MASK);
				obj.h2_obj_id = std::pair<MP2::obj_type_e, int>(
					MP2::obj_type_e(mp2addon.objectNameN2), MP2::obj_type_e(mp2addon.indexNameN2)
					);
				obj.map_x = i % (_map.width);
				obj.map_y = i / (_map.width);

				_map.map_tiles[i].objects.push_back(obj);
				}

			next_id = mp2addon.indexAddon;
			}
		while(next_id);

		}
	std::cout << "total addons: " << num_addons
		<< ", number addons referenced: " << num_addons_referenced 
		<< ", number with next_id :" << num_addons_with_nextid
		<< ", diff:" << num_addons - (num_addons_referenced + num_addons_with_nextid) 
		<< "\n";


	//
	f.close();

	return true;
	}

/*
bool MP2Format::loadMap(const QString & mapFile)
{
H2::File map(mapFile);

if(map.open(QIODevice::ReadOnly))
{
// 4 byte: orig ver
if(map.readLE32() != 0x0000005C)
{
qDebug() << "Incorrect map file: " << mapFile;
map.close();
return false;
}

// difficulty: 0: easy, 1: normal, 2: hard, 3: expert
difficulty = map.readLE16();

// width, height
size.setWidth(map.readByte());
size.setHeight(map.readByte());

// kingdom color: blue, gree, red, yellow, orange, purple
for(int ii = 0; ii < 6; ++ii)
kingdomColor[ii] = map.readByte();

// allow human: blue, gree, red, yellow, orange, purple
for(int ii = 0; ii < 6; ++ii)
humanAllow[ii] = map.readByte();

// allow comp: blue, gree, red, yellow, orange, purple
for(int ii = 0; ii < 6; ++ii)
compAllow[ii] = map.readByte();

// wins
map.seek(0x1D);
conditionWins = map.readByte();

// data wins
conditionWinsData1 = map.readByte();
conditionWinsData2 = map.readByte();
conditionWinsData3 = map.readLE16();
map.seek(0x2C);
conditionWinsData4 = map.readLE16();

// loss
map.seek(0x22);
conditionLoss = map.readByte();
// data loss
conditionLossData1 = map.readLE16();
map.seek(0x2E);
conditionLossData2 = map.readLE16();

// start with hero
map.seek(0x25);
startWithHero = (0 == map.readByte());

// race color
for(int ii = 0; ii < 6; ++ii)
raceColor[ii] = map.readByte();

// name
map.seek(0x3A);
name = map.readString(16);

// description
map.seek(0x76);
description = map.readString(143);

// data map: width, heigth
map.seek(0x01A4);
if(static_cast<int>(map.readLE32()) != size.width())
{
qDebug() << "MP2Format::loadMap:" << "incorrect size";
return false;
}
if(static_cast<int>(map.readLE32()) != size.height())
{
qDebug() << "MP2Format::loadMap:" << "incorrect size";
return false;
}

// data map: mp2tile, part1
// count blocks: width * heigth
tiles.resize(size.width() * size.height());

for(QVector<mp2til_t>::iterator
it = tiles.begin(); it != tiles.end(); ++it)
{
QDataStream ds(map.read(20));
ds >> (*it);
}

// data map: mp2ext, part2
// count blocks: 4 byte
sprites.resize(map.readLE32());

for(QVector<mp2ext_t>::iterator
it = sprites.begin(); it != sprites.end(); ++it)
{
QDataStream ds(map.read(15));
ds >> (*it);
}

// cood castles
QVector<mp2pos_t> townPosBlocks;
townPosBlocks.reserve(72);

// 72 x 3 byte (px, py, id)
for(int ii = 0; ii < 72; ++ii)
{
mp2pos_t twn;

twn.posx = map.readByte();
twn.posy = map.readByte();
twn.type = map.readByte();

if(0xFF != twn.posx && 0xFF != twn.posy)
townPosBlocks.push_back(twn);
}

// cood resource kingdoms
QVector<mp2pos_t> resourcePosBlocks;
resourcePosBlocks.reserve(144);

// 144 x 3 byte (px, py, id)
for(int ii = 0; ii < 144; ++ii)
{
mp2pos_t res;

res.posx = map.readByte();
res.posy = map.readByte();
res.type = map.readByte();

if(0xFF != res.posx && 0xFF != res.posy)
resourcePosBlocks.push_back(res);
}

// byte: numObelisks
map.readByte();

// find count latest blocks: unknown byte ?? ?? ?? LO HI 00 00
int blocksCount = 0;

while(1)
{
quint8 lo = map.readByte();
quint8 hi = map.readByte();

if(0 == hi && 0 == lo)
break;
else
blocksCount = 256 * hi + lo - 1;
}

// read latest blocks
for(int ii = 0; ii < blocksCount; ++ii)
{
// parse block
QByteArray block = map.readBlock(map.readLE16());
QDataStream data(block);
data.setByteOrder(QDataStream::LittleEndian);
const QPoint posBlock = positionExtBlockFromNumber(ii + 1);
const int posMapIndex = posBlock.x() < 0 ? -1 : size.width() * posBlock.y() + posBlock.x();

if(0 <= posMapIndex && posMapIndex < tiles.size())
{
switch(tiles[posMapIndex].objectID)
{
case 0x82: // sign,bottle block: 10 byte
case 0xDD:
if(10 <= block.size() && 0x01 == block.at(0))
{
mp2sign_t sign; data >> sign;
signs.push_back(H2::SignPos(sign, posBlock));
}
break;

case 0x93: // map event block: 50 byte
if(50 <= block.size() && 0x01 == block.at(0))
{
mp2mapevent_t event; data >> event;
mapEvents.push_back(H2::EventPos(event, posBlock));
}
break;

case 0xA3: // castle, rnd town, rnd castle block: 70 byte
case 0xB0:
case 0xB1:
if(block.size() == 70)
{
mp2town_t castle; data >> castle;
castles.push_back(H2::TownPos(castle, posBlock));
}
break;

case 0xB7: // hero, jail block: 76 byte
case 0xFB:
if(block.size() == 76)
{
mp2hero_t hero; data >> hero;
heroes.push_back(H2::HeroPos(hero, posBlock));
}
break;

case 0xCF: // sphinx block: 138 byte
if(138 <= block.size() && 0 == block.at(0))
{
mp2sphinx_t sphinx; data >> sphinx;
sphinxes.push_back(H2::SphinxPos(sphinx, posBlock));
}
break;

default: break;
}
}
else
if(block.at(0) == 0)
{
// day event block: 50 byte
if(50 <= block.size() && 0x01 == block.at(42))
{
mp2dayevent_t event; data >> event;
dayEvents.push_back(event);
}
else
// rumor block: 9 byte
if(9 <= block.size())
{
mp2rumor_t rumor; data >> rumor;
if(rumor.text.isEmpty())
qDebug() << "MP2Format::loadMap:" <<"skip empty rumor, block: " << ii;
else
rumors.push_back(rumor);
}
else
qCritical() << "MP2Format::loadMap:" <<"unknown block: " << ii << ", size: " << block.size();
}
else
qCritical() << "MP2Format::loadMap:" <<"unknown block: " << ii << ", size: " << block.size() << ", byte: " << block[0];
}

uniq = map.readLE32();
map.close();

//
return true;
}

return false;
}
*/