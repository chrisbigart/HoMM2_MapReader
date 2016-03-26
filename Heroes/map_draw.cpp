#include "game.h"

#include <map>
#include <sstream>


void game_t::on_map_resize(CL_Slider* slider)
	{
	_map_scale = slider->get_position() / 1000.f;
	//_resize_ui();
	}


bool object_t::operator<(const object_t& other) const
	{
	if(level == other.level)
		{
		if((draw_layer & 0x0f) == (other.draw_layer & 0x0f))
			return draw_layer < other.draw_layer;
		else
			return (draw_layer & 0x0f) < (other.draw_layer & 0x0f);
		}

	return level < other.level;
	}

void game_t::_draw_map_objects()
	{
	int xbound = 1500;
	int ybound = 900;

	int _xoff = _map_xoff;
	int _yoff = _map_yoff;
	
	_tile_size = _map_scale * 128;

	for(int i = 0; i < (int)_map.map_tiles.size(); i++)
		{
		const int s = _tile_size;
		int x = i % (_map.width);
		int y = i / (_map.width);

		if(x*s + _xoff < -1 * s || y*s + _yoff < -1 * s ||
			x*s + _xoff > xbound || y*s + _yoff > ybound)
			continue;

		std::sort(_map.map_tiles[i].objects.begin(), _map.map_tiles[i].objects.end());
		for(int n = 0; n < _map.map_tiles[i].objects.size(); n++)
			{
			const object_t& obj = _map.map_tiles[i].objects[n];

			std::pair<int, int> h2id = obj.h2_obj_id;
		
			if(!_h2_objects.count(h2id))
				{
				if(!_load_h2_object(h2id.first, h2id.second))
					continue;
				}

			if(!_draw_debug_flags[0] && obj.level == 0)
				continue;
			if(!_draw_debug_flags[1] && obj.level == 1)
				continue;
			if(!_draw_debug_flags[2] && obj.level == 10)
				continue;
			if(!_draw_debug_flags[3] && obj.level == 11)
				continue;

			if(!_draw_debug_flags[5])
				_h2_objects[h2id].set_alpha(0.6f);
			else
				_h2_objects[h2id].set_alpha(1.0f);

			_h2_objects[h2id].set_scale(_map_scale, _map_scale);
			_h2_objects[h2id].draw(_gc, _xoff + obj.map_x * _tile_size,
								   _yoff + obj.map_y * _tile_size);
			}
		
		/*
		if(_draw_overlay_boxes)
			CL_Draw::box(_gc, CL_Rect(_xoff + _map.overlay_objects[i]->map_x * _tile_size,
			_yoff + _map.overlay_objects[i]->map_y * _tile_size, CL_Size(_tile_size, _tile_size)), (_map.overlay_objects[i]->layer == 0 ? CL_Colorf::red : CL_Colorf::yellow));*/
		}
	}


void game_t::_draw_terrain()
	{
	float tcolors[9][3] = {
	{.8f, .8f, .8f},		{1.f, 1.f, 1.f},	{0, 1.f, 0},	{1.f, 1.f, 1.f},
	{.2f, 0, 0},		{1.f, 1.f, 1.f},	{1.f, 1.f, 1.f},	{1.f, 1.f, 1.f}, 	{0, 0, 1.f}
	};
	
	int xbound = 1500;
	int ybound = 900;
	
	int _xoff = _map_xoff;
	int _yoff = _map_yoff;

	_tile_size = _map_scale * 128;

	static std::map<std::pair<int, int>, CL_Sprite> rotated_sprites_cache;
	
	if(_draw_terrain_tiles)
	for(int y = 0; y < _map.height; y++)
		{
		for(int x = 0; x < _map.width; x++)
			{
			const int s = _tile_size;
			if(x*s + _xoff < -1 * s || y*s + _yoff < -1 * s ||
				x*s + _xoff > xbound || y*s + _yoff > ybound)
				continue;
			
			int type = _map.terrain[y*_map.height + x].type;
			int subtype = _map.terrain[y*_map.height + x].subtype;

			const bool h2mode = true;
			if(h2mode)
				{
				if(subtype == 0)
					{//not rotated
					_h2_tiles[type].set_scale(_map_scale, _map_scale);
					_h2_tiles[type].draw(_gc, _xoff + x * _tile_size, _yoff + y * _tile_size);
					}
				else
					{ //some type of rotation
					std::pair<int, int> p(type, subtype);//std::make_pair<int, int>(type, subtype)
					if(!rotated_sprites_cache.count(p))
						{
						CL_Sprite rs;
						if(type >= _h2_tiles.size())
							{
							continue;
							}
						rs.clone(_h2_tiles[type]);// = _h2_tiles[type].clone();
						/* 
						tileShape = rotate % 4;

						QPixmap sprite = EditorTheme::getImageTIL("GROUND32.TIL", tileSprite);

						switch(tileShape)
							{
							case 1: setPixmap(sprite.transformed(QTransform().scale( 1, -1))); break;
							case 2: setPixmap(sprite.transformed(QTransform().scale(-1,  1))); break;
							case 3: setPixmap(sprite.transformed(QTransform().scale(-1, -1))); break;
							default: setPixmap(sprite); break;
							}
						if(subtype == 1 || subtype == 3) //if(subtype & 0x01)
							rs.set_angle_yaw(CL_Angle(180.0f, cl_degrees));//rs.rotate(CL_Angle(180.0f, cl_degrees));
						else if(subtype == 2 || //subtype == 4 || 
								subtype == 6) //else if(subtype & 0x10)
							rs.rotate(CL_Angle(-180.0f, cl_degrees));
						else if(subtype == 5)
							rs.set_angle_pitch(CL_Angle(180.0f, cl_degrees));//rs.set_scale(1.0f, -1.0f);
							*/
						if(subtype & 0x01)
							rs.set_angle_pitch(CL_Angle(180.0f, cl_degrees));
						if(subtype & 0x02)
							rs.set_angle_yaw(CL_Angle(180.0f, cl_degrees));
						rotated_sprites_cache[p] = rs;
						}

					rotated_sprites_cache[p].set_scale(_map_scale, _map_scale);
					rotated_sprites_cache[p].draw(_gc, _xoff + x * _tile_size, _yoff + y * _tile_size);

					static bool draw_debug2 = false;
					if(draw_debug2)
						{
						CL_Draw::box(_gc, CL_Rect(_xoff + x * _tile_size, _yoff + y * _tile_size, CL_Size(_tile_size, _tile_size)), CL_Colorf::pink);
						const int xt = 0, yt = 0;
						std::stringstream strm;
						strm << (int)subtype;
						_text.draw_text(_gc, _xoff + x*_tile_size + xt,
										_yoff + y*_tile_size + _tile_size + yt, strm.str());
						}
					}

				}
			else //h3tiles
				{
				_tiles[type]->set_frame(subtype);
				//_tiles[type]->set_scale(_tiles[type]->get_scale())
				_tiles[type]->set_scale(_map_scale, _map_scale);
				_tiles[type]->draw(_gc, _xoff + x * _tile_size, _yoff + y * _tile_size);
				}
			
			CL_Colorf c(tcolors[type][0], tcolors[type][1], tcolors[type][2], .8f);
			float px = 0, py = 0;
					
			//CL_Draw::fill(_gc, x*s + px, y*s + py, x*s+s + px, y*s+s + py, c);			
			
			/*if(_map.terrain[y*_map.height + x].road)
				CL_Draw::line(_gc, x*s + px, _yoff + y*s + py, x*s+s + px, _yoff + y*s+s + py, CL_Colorf(0., 0., 0., 1.f));
			if(_map.terrain[y*_map.height + x].river)
				CL_Draw::line(_gc, x*s + px, _yoff + y*s + py, x*s+s + px, _yoff + y*s+s + py, CL_Colorf(.3f, .5f, .9f, 1.f));*/		
			}
		}


	_draw_map_objects();

		/*const object_t& obj = *_map.objects[i];
		if(obj.type == town_object)
		{
		town_t& town = *((town_t*)_map.objects[i]);
		_castles->set_frame((int)town.alignment);
		_castles->draw(_gc, _xoff + obj.draw_x * _tile_size, _yoff + obj.draw_y * _tile_size);
		}
		else
		{
		float x = (float) obj.map_x;
		float y = (float) obj.map_y;

		CL_Draw::fill(_gc, _xoff + x*_tile_size, _yoff + y*_tile_size, _xoff + x*_tile_size+_tile_size, _yoff + y*_tile_size+_tile_size, CL_Colorf(.1f, .1f, .8f, .4f));
		std::stringstream strm;
		strm << (int)obj.type;
		_text.draw_text(_gc, _xoff + x*_tile_size, _yoff + y*_tile_size + _tile_size, strm.str());
		}
		*/
	
	static bool draw_debug1 = true;

	if(draw_debug1)
		{
		int mx = _mouse_xtile;
		int my = _mouse_ytile;
		bool draw = true;
		if(mx < 0 || mx >= _map.width || my < 0 || my >= _map.height)
			draw = false;

		if(draw)
			{
			CL_Draw::box(_gc, CL_Rect(_map_xoff + mx * _tile_size, _map_yoff + my * _tile_size, CL_Size(_tile_size, _tile_size)), CL_Colorf::pink);
			const int xt = 0, yt = 0;
			std::stringstream strm;
			const MP2::mp2tile_t& tile = _map.h2_mp2_tiles[mx + _map.width * my];
			strm << "(" << mx << ", " << my << ") tileIndex:" << (int)tile.tileIndex
				<< "\nobjName1:\t" << (int)tile.objectName1
				<< "\tindName2:\t" << (int)tile.indexName1
				<< "\nquantity1:\t" << (int)tile.quantity1
				<< "\tquantity2:\t" << (int)tile.quantity2
				<< "\nobjName2:\t" << (int)tile.objectName2
				<< "\tindName2:\t" << (int)tile.indexName2
				<< "\nshape:\t" << (int)tile.shape
				<< "\ngenObj:\t" << (int)tile.generalObject
				<< "\nindexAddon:\t" << (int)tile.indexAddon
				<< "\nuniqNumber1:\t" << (int)tile.uniqNumber1
				<< "\nuniqNumber2:\t" << (int)tile.uniqNumber2
				;

			_text.draw_text(_gc, _map_xoff + mx*_tile_size + xt + 2,
							_map_yoff + my*_tile_size + _tile_size + yt + 2,
							strm.str(), CL_Colorf::black);
			_text.draw_text(_gc, _map_xoff + mx*_tile_size + xt,
							_map_yoff + my*_tile_size + _tile_size + yt, strm.str());

			int addon_index = tile.indexAddon;
			int xpos = 0;
			int ypos = 80;
			int n = 0;
			while(addon_index != 0)
				{
				const MP2::mp2addon_t& addon = _map.h2_mp2_addon_tiles[addon_index];
				std::stringstream strm;
				strm << "addon[" << n++ << "]:" << (int)addon.indexAddon
					<< "\nobjectNameN1 = " << (int)addon.objectNameN1
					<< "\nindexNameN1 = " << (int)addon.indexNameN1
					<< "\nquantityN = " << (int)addon.quantityN
					<< "\nobjectNameN2 = " << (int)addon.objectNameN2
					<< "\nindexNameN2 = " << (int)addon.indexNameN2
					;

				xpos += 160;
				_text.draw_text(_gc, xpos + _map_xoff + mx*_tile_size + xt + 2,
								ypos + _map_yoff + my*_tile_size + _tile_size + yt + 2,
								strm.str(), CL_Colorf::black);
				_text.draw_text(_gc, xpos + _map_xoff + mx*_tile_size + xt,
								ypos + _map_yoff + my*_tile_size + _tile_size + yt, strm.str());

				addon_index = addon.indexAddon;
				}
			}
		
		//return;
		}

	for(int i = 0; i < (int)_map.index.size(); i++)
		{
		
		object_t* obj = _map.index[i];
		if(!obj)
			continue;
		
		float x = (float) (int) (i % _map.width);
		float y = (float) (int) (i / _map.height);
		
		const int s = _tile_size;
		if(x*s + _xoff < -1 * s || y*s + _yoff < -1 * s ||
			x*s + _xoff > xbound || y*s + _yoff > ybound)
			continue;
		
		if(x == obj->map_x && y == obj->map_y)
			CL_Draw::fill(_gc, _xoff + x*_tile_size, _yoff + y*_tile_size, _xoff + x*_tile_size+_tile_size, _yoff + y*_tile_size+_tile_size, CL_Colorf(.8f, .8f, 0.0f, .2f));
		else
			CL_Draw::fill(_gc, _xoff + x*_tile_size, _yoff + y*_tile_size, _xoff + x*_tile_size+_tile_size, _yoff + y*_tile_size+_tile_size, CL_Colorf(.8f, 0.0f, 0.0f, .2f));
		
		if(obj->type == resource_object)
			{
			_resource_icons->set_frame(((resource_t*)obj)->res_type);
			_resource_icons->draw(_gc, _xoff + x * _tile_size, _yoff + y * _tile_size);
			}
		}
		
	
	//draw shroud / fog of war
	for(int y = 0; y < _map.height; y++)
		{
		for(int x = 0; x < _map.width; x++)
			{
			const int s = _tile_size;
			if(x*s + _xoff < -1 * s || y*s + _yoff < -1 * s ||
				x*s + _xoff > xbound || y*s + _yoff > ybound)
				continue;
			
			//if(
			}
		}
	
	
		
	//draw heros and their paths, if applicable		
	for(int i = 0; i < (int)_players[_current_player].heroes.size(); i++)
		{
		hero_t& hero = _players[_current_player].heroes[i];
		CL_Draw::circle(_gc, _xoff + hero.drawx + (_tile_size / 2), 
						_yoff + hero.drawy + (_tile_size / 2), 16, CL_Colorf(1.0f, 0.0f, 1.0f, 1.f));
		
		if(i != _current_hero)
			continue;
		
		int n = 0;
		for(path_t::iterator it = hero.path.begin(); it != hero.path.end(); it++)
			{
			n++;
			//int p = it->pos;
			float x = (float) (int) _xoff + (it->x() * _tile_size + (_tile_size / 2));
			float y = (float) (int) _yoff + (it->y() * _tile_size + (_tile_size / 2));
			
			if(n <= hero.movement_left)
				CL_Draw::circle(_gc, x, y, 8, CL_Colorf(0.0f, 1.0f, 0.0f, 1.f));
			else				
				CL_Draw::circle(_gc, x, y, 8, CL_Colorf(1.0f, 0.0f, 0.0f, 1.f));
				
			std::stringstream s;
			s << it->fcost();
			_text.draw_text(_gc, x - 12, y - 13, s.str());
			std::stringstream s1;
			s1 << it->gcost;
			_text.draw_text(_gc, x - 12, y - 3, s1.str());
			}
		}

	/*for(int i = 0; i < _map.objects.size(); i++)
		{
		const _map_t::object_t& obj = _map.objects[i];
		CL_String s;
		switch(obj.obj_class)
			{
			case 53: s = "Mine"; break;
			case 72: s = "L1 Monster"; break;
			case 98: case 77: s = "Town";
				{
				_castles[0]->draw(_gc, obj.x * _tile_size, obj.y * _tile_size);
				}
				break;
			case 79:
				s = "Res"; break;
			case 134:
			case 135:
			case 137:
			case 118: //trees?
				s = "Tree";
				break;
			default:
				s = "??"; break;
			
			}
		text.draw_text(_gc, obj.x * _tile_size, obj.y * _tile_size, s);
		}*/
	}
