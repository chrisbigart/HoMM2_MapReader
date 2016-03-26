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
//typedef cl_uint8 uint8_t;
//typedef char uint8_t;


/*bool AGG::File::loadFile(const QString & fn)
{
    if(isOpen()) close();
    if(fn.isEmpty()) return false;

    setFileName(fn);
    if(open(QIODevice::ReadOnly))
    {
	qDebug() << "AGG::File::loadFile:" << qPrintable(fn);
	quint16 countItems = readLE16();

	qDebug() << "AGG::File::loadFile:" << "count items:" << countItems;
	const int sizeName = 15;

	for(int it = 0; it < countItems; ++it)
	{
	    int posname = size() - sizeName * (countItems - it);

	    Item & item = items[QString(readBlock(sizeName, posname))];

		seek(sizeof(countItems) + it * (3 * sizeof(quint32) // crcItem + offsetItem + sizeItem 
		));

		item.crc = readLE32();
		item.offset = readLE32();
		item.size = readLE32();
	}

	return true;
	}
	else
		qCritical() << "AGG::File::loadFile:" << "Can not read file " << qPrintable(fn);

		return false;
}
*/
bool game_t::_load_h2_tiles(const std::string& filename)
	{
	const int num_tiles = 432;
	_h2_tiles.reserve(432);
	for(int i = 0; i < num_tiles; i++)
		{
		std::stringstream strm;
		strm << "hr-" << std::setfill('0') << std::setw(3) << i << ".png";
		string fname = filename + "/" + strm.str();

		///!!
		//it is best to load the map file first, combine all individual tiles together
		//into one large bitmap, then run the hqx/xbrz algorithms, as they will cause
		//banding artifacts to appear when only done a single tile at a time
		///!!

		/*const int scale = 2;
		CL_PixelBuffer tile(fname);
		CL_PixelBuffer pbuf(tile.get_height() * scale, tile.get_width() * scale, cl_rgba8);
		
		if(pbuf.is_null())
			throw;

		//for(int i = 0; i < 256; i++)
		//	*((unsigned int*)pbuf.get_data()) = 0x77994433;
		///xbrz::nearestNeighborScale(tile.get_data_uint32(), tile.get_width(), tile.get_height(), (unsigned int*)pbuf.get_data(), pbuf.get_width(), pbuf.get_height());
		xbrz::scale(2, tile.get_data_uint32(), (unsigned int*)pbuf.get_data(), tile.get_width(), tile.get_height(), xbrz::ColorFormat::ARGB);
		
		//CL_Image img(_gc, pbuf, CL_Rect(0, 0, pbuf.get_width(), pbuf.get_height()));
		CL_SpriteDescription sd;
		sd.add_frame(pbuf);
		_h2_tiles.push_back(CL_Sprite(_gc, sd));*/
		_h2_tiles.push_back(CL_Sprite(_gc, fname));
		}
	return true;
	}
