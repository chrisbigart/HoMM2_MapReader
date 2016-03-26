#include "game.h"

#include <sstream>
#include <ctime>

/*
ui_t::ui_t(game_window_t* parent) : _parent(*parent), 
			_end_turn(parent), _move_hero(parent), _cast_spell(parent),
			_adventure_options(parent), _system_options(parent), _kingdom_overview(parent),
			_ui_ui_scale(parent), 
			//_sys_options_window(&parent->get_gui_manager(), CL_DisplayWindowDescription("System Options", CL_Rect(0,0, 100, 100), false)),
			_ui_scale(1.0f)
	{
	//_end_turn.set_text("End Turn");
	_end_turn.set_icon(CL_Image(_parent.get_gc(), "hourglass-icon.png"));
	_end_turn.func_clicked().set(this, &ui_t::on_end_turn_clicked, &_end_turn);
	
	_adventure_options.set_text("Adv Opt");
	_system_options.set_text("Sys Opt");
	_cast_spell.set_text("Cast");
	_kingdom_overview.set_text("Kingdom");
	_move_hero.set_text("Move");
	
	
	//_resource_icons = new CL_Sprite(_parent.get_gc(), "Resources", &_resources);
	
	_ui_ui_scale.set_geometry(CL_Rect(0,0, 200, 20));
	_ui_ui_scale.func_value_changed().set(this, &ui_t::on_ui_resize, &_ui_ui_scale);
	
	_parent.func_resized().set(this, &ui_t::_resize);
	
	_resize();
	}
	*/
void game_t::on_ui_resize(CL_Slider* slider)
	{
	_ui_scale = slider->get_position() / 50.f;
	_resize_ui();
	}

void game_t::_resize_ui()
	{
	CL_Rect sz = _window.get_client_area();
	int ww = sz.get_width();
	int wh = sz.get_height();
	int w = (int) (32 * _ui_scale);
	int h = (int) (32 * _ui_scale);
	
	int y = wh - (h * 4 + 50);
	
	int pad = (int) (10 * _ui_scale);
	
	_end_turn_button.set_geometry(CL_Rect(ww - pad - w, wh - pad - h, ww - pad, wh - pad));
	
	_adventure_options_button.set_geometry(CL_Rect(ww - 2*pad - w*2, y, ww - 2*pad - w, y + h));
	_system_options_button.set_geometry(CL_Rect(ww - pad - w, y, ww - pad, y + h));
	
	_cast_spell_button.set_geometry(CL_Rect(ww - 2*pad - w*2, y + pad + h, ww - 2*pad - w, y + pad + h*2));
	_kingdom_overview_button.set_geometry(CL_Rect(ww - pad - w, y + pad + h, ww - pad, y + pad + h*2));
	
	_move_hero_button.set_geometry(CL_Rect((int) (ww - 1.5*pad - w*1.5f), y + 2*pad + h*2,
									(int) (ww - 1.5*pad - w*.5f), y + 2*pad + h*3));
	
	/*_hero_listview.set_geometry(CL_Rect(100, 100, 150, 250));
	_hero_listview.set_cliprect(_gc, CL_Rect(80, 80, 100, 200));
	CL_Sprite spr;
	_hero_listview.add_item(CL_Sprite(_gc, "sandro.png"), 0, CL_String(), 0);
	_hero_listview.add_item(CL_Sprite(_gc, "craghack.png"), 0, CL_String(), 0);
	*/
	}
	
void game_t::_fade_out()
	{
	//todo
	}
	
void game_t::_draw_resources_ui()
	{
	CL_Rect sz = _window.get_client_area();
	int ww = sz.get_width();
	int wh = sz.get_height();
	
	CL_RoundedRect res_outline(CL_Sizef(645, 47), 10.f);
	res_outline.fill(_gc, CL_Pointf(5, wh - 50), CL_Colorf(.2f, .2f, .6f, .7f));
		
	for(int type = 0; type < 7; type++)
		{
		int m = 85;
		int xoff = 10;
		int yoff = wh - 50;
		int value = 0;
		int p = _current_player;
		switch(type)
			{
			case 0:	value = _players[p].wood; break;
			case 1: value = _players[p].ore; break;
			case 2: value = _players[p].mercury; break;
			case 3: value = _players[p].sulfur; break;
			case 4: value = _players[p].crystal; break;
			case 5: value = _players[p].gems; break;
			case 6: value = _players[p].gold; break;
			}
		//_resource_icons->set_frame(i);
		//_resource_icons->draw(gc, xoff + m * type, yoff);
		std::stringstream strm;
		strm << value;
		_text.draw_text(_gc, xoff + m * type + 42, yoff + 20, strm.str());
		}
	}

void game_t::_draw_ui()
	{
	_draw_resources_ui();
	
	CL_Rect sz = _window.get_client_area();
	int ww = sz.get_width();
	int wh = sz.get_height();	
	
	//_topleft_ui->draw(_gc, CL_Rectf(0, 0, 100 * _ui_scale, 100 * _ui_scale));
	
	//draw mini-map
	CL_RoundedRect minimap_outline(CL_Sizef(135 * _ui_scale, 135 * _ui_scale), 10.f);
	minimap_outline.fill(_gc, CL_Pointf(ww - 140 * _ui_scale, 10), CL_Colorf(.2f, .2f, .6f, .7f));
	
	int px = ww - (130 * _ui_scale);
	int py = 20;
	for(int x = 0; x < _map.width; x++)
		for(int y = 0; y < _map.height; y++)
			{ //probably a much much better way to do this, but...
			//dirt, sand, grass, snow, 
			//swamp, rough, subterrainian, lava, water
			float tcolors[9][3] = {
			{.8, .8, .8f},		{1.f, 1.f, 1.f},	{0, 1.f, 0},	{1.f, 1.f, 1.f},
			{.2f, 0, 0},		{1.f, 1.f, 1.f},	{1.f, 1.f, 1.f},	{1.f, 1.f, 1.f}, 	{0, 0, 1.f}
			};
			
			map_t::tile_t ter = _map.get_terrain(x, y);
			CL_Colorf c(tcolors[ter.type][0], tcolors[ter.type][1], tcolors[ter.type][2], .8f);
			//CL_Draw::point(gc, x + px, y + py, c);
			float s = 4 * _ui_scale;
			CL_Draw::fill(_gc, x*s + px, y*s + py, x*s+s + px, y*s+s + py, c);
			}
	
	//draw hero list
	CL_RoundedRect hero_outline(CL_Sizef(197, 247), 10.f);
	hero_outline.fill(_gc, CL_Pointf(ww - 200, wh - 500), CL_Colorf(.2f, .2f, .6f, .7f));
	for(int i = 0; i < (int)_players[_current_player].heroes.size(); i++)
		{
		hero_t& hero = _players[_current_player].heroes[i];
		int x = ww - 190;
		int y = wh - 490 + i * 60;
		
		CL_Draw::box(_gc, x, y, x + 40, y + 40, i == _current_hero ? CL_Colorf::orange : CL_Colorf::blueviolet);
		CL_Draw::fill(_gc, x-5, y + 1.6*(hero.max_movement - hero.movement_left), x-2, y + 40, CL_Colorf(0.0f, 1.f, 0.0f, 1.f));
		_text.draw_text(_gc, ww - 190, wh - 490 + i * 60, hero.name);
		}
	
	//draw hero/troop/castle/etc info
	CL_RoundedRect info_outline(CL_Sizef(197, 127), 10.f);
	info_outline.fill(_gc, CL_Pointf(ww - 200, wh - 250), CL_Colorf(.2f, .2f, .6f, .7f));
	if(_players[_current_player].heroes.size())
		{
		hero_t& hero = _players[_current_player].heroes[_current_hero];
		std::stringstream strm;
		strm << "A: " << hero.attack << "  D: " << hero.defense << "  P: " << hero.power << "  K: " << hero.knowledge;
		_text.draw_text(_gc, ww - 190, wh - 240, strm.str());
		}
	
	//draw status text
	int timediff = (clock() - _status_time);
	if(timediff < 5 * 1000)
		{
		float alpha = ((4 * 1000) - timediff) / 1000.f;
		CL_Size text_size = _text.get_text_size(_gc, _status);
		text_size += CL_Size(10, 10);
		CL_RoundedRect res_outline(text_size, 10.f);
		res_outline.fill(_gc, CL_Pointf(5, wh - 80), CL_Colorf(0.0f, 0.0f, 0.0f, alpha));
		_text.draw_text(_gc, 10, _window.get_height() - 60, _status, CL_Colorf(1.0f, 1.0f, 1.0f, alpha));		
		}
	}
