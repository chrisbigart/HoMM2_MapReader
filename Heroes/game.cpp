#include "game.h"

#include <ctime>
#include <sstream>

game_t::game_t(CL_GUIManager& manager, const CL_DisplayWindowDescription& desc)
	: _window(manager, desc),
	_gc(_window.get_gc()),
	_resources("resources.xml"),
	_text(_gc, "Arial", 18),
	_end_turn_button(&_window), _move_hero_button(&_window), _cast_spell_button(&_window),
			_adventure_options_button(&_window), _system_options_button(&_window), _kingdom_overview_button(&_window),
			_ui_scale_slider(&_window),	_map_scale_slider(&_window),
			_hero_listview(&_window),
	_ui_scale(1.0f), _map_scale(1.0f), _tile_size(32), _game_state(adventure_map),
	_hero_move_speed(6.0f), _num_players(1)
	{
	_window.func_render().set(this, &game_t::on_render);
	
	CL_Slot slot_mouse_move = (_window.get_ic().get_mouse().sig_pointer_move().connect(this, &game_t::on_mouse_move));
	CL_Slot slot_mouse_down = (_window.get_ic().get_mouse().sig_key_down().connect(this, &game_t::on_mouse_down));
	CL_Slot slot_mouse_double_clicked = (_window.get_ic().get_mouse().sig_key_dblclk().connect(this, &game_t::on_mouse_down));
	CL_Slot slot_mouse_up = (_window.get_ic().get_mouse().sig_key_up().connect(this, &game_t::on_mouse_up));

	
	CL_Slot slot_key_down = (_window.get_ic().get_keyboard().sig_key_down().connect(this, &game_t::on_key_down));
	
	_new_game();
	
	_adventure_options_button.set_text("Adv Opt");
	_system_options_button.set_text("Sys Opt");
	_cast_spell_button.set_text("Cast");
	_kingdom_overview_button.set_text("Kingdom");
	_move_hero_button.set_text("Move");	
	
	
	_cast_spell_button.func_clicked().set(this, &game_t::on_cast_spell_clicked, &_cast_spell_button);
	_end_turn_button.func_clicked().set(this, &game_t::on_end_turn_clicked, &_end_turn_button);
	_move_hero_button.func_clicked().set(this, &game_t::on_move_hero_clicked, &_move_hero_button);
	_system_options_button.func_clicked().set(this, &game_t::on_system_options_clicked, &_system_options_button);
	
	_ui_scale_slider.set_geometry(CL_Rect(0, 30, 200, 20));
	_ui_scale_slider.func_value_changed().set(this, &game_t::on_ui_resize, &_ui_scale_slider);
	_map_scale_slider.set_geometry(CL_Rect(0, 0, 500, 30));
	_map_scale_slider.set_ranges(100, 1000, 900, 1);
	_map_scale_slider.func_value_changed().set(this, &game_t::on_map_resize, &_map_scale_slider);

	_resize_ui();
	_window.func_resized().set(this, &game_t::_resize_ui);
	
	_window.set_constant_repaint(true);
	manager.exec();
	}

void game_t::on_render(CL_GraphicContext& gc, const CL_Rect& clip_rect)
	{	
	gc.clear(CL_Colorf::gray);
	
	_update_hero();
	
	if(_game_state == adventure_map)
		{
		_draw_terrain();
		_draw_ui();
		}
	else if(_game_state == town_screen)
		{
		_draw_town_screen();
		_draw_resources_ui();
		}
	else if(_game_state == battle_screen)
		{
		_update_battle();
		_draw_battle_screen();
		}
	
	CL_System::sleep(100);
	}
	
void game_t::on_key_down(const CL_InputEvent& key, const CL_InputState& state)
	{
	if(key.id == CL_KEY_SPACE)
		{
		if(_current_hero < 0 || _current_hero >= _get_current_player().heroes.size())
			return;
		
		hero_t& hero = _get_current_player().heroes[_current_hero];
		int pos = hero.mapx + (hero.mapy * _map.width);
		_visit_object(pos);
		}
	if(key.id == CL_KEY_TAB)
		{
		_draw_overlay_boxes = !_draw_overlay_boxes;
		}
	if(key.id == CL_KEY_1)
		{
		_draw_terrain_tiles = !_draw_terrain_tiles;
		}
	if(key.id == CL_KEY_2)
		{
		_draw_map_objects_flag = !_draw_map_objects_flag;
		}
	if(key.id == CL_KEY_3)
		{
		_draw_map_overlays = !_draw_map_overlays;
		}
	if(key.id == CL_KEY_4)
		{
		_draw_debug_flags[0] = !_draw_debug_flags[0];
		}
	if(key.id == CL_KEY_5)
		{
		_draw_debug_flags[1] = !_draw_debug_flags[1];
		}
	if(key.id == CL_KEY_6)
		{
		_draw_debug_flags[2] = !_draw_debug_flags[2];
		}
	if(key.id == CL_KEY_7)
		{
		_draw_debug_flags[3] = !_draw_debug_flags[3];
		}
	if(key.id == CL_KEY_8)
		{
		_draw_debug_flags[4] = !_draw_debug_flags[4];
		}
	if(key.id == CL_KEY_9)
		{
		_draw_debug_flags[5] = !_draw_debug_flags[5];
		}
	}

void game_t::_new_game()
	{
	_load_sprites();
	//_map.load("multi3");
	//_load_heroes3_map("multi3");
	//_load_heroes2_map("MapTest2.MX2");
	_load_heroes2_map("h2maptest02");
	//_load_heroes2_map("2water.mx2");
	
	//_load_h2_objects();
	
	enum difficulty_e 
		{
		easy = 0, normal, hard, expert, impossible
		} difficulty;
		
	enum initial_resources_e 
		{
		plentiful = 0, adequate, scarce, meagre, none
		} initial_resources;
	
	difficulty = normal;
	initial_resources = adequate;
	
	int starting_resources[][7] = {
		{50, 50, 20, 20, 20, 20, 50000},
		{20, 20, 10, 10, 10, 10, 15000},
		{15, 15, 7, 7, 7, 7, 10000},
		{7, 7, 3, 3, 3, 3, 5000},
		{0, 0, 0, 0, 0, 0, 0},
	};
	
	int num_players = 2;
	
	for(int i = 0; i < num_players; i++)
		{
		int d = (int)initial_resources;
		_players[i].wood = starting_resources[d][0];
		_players[i].ore = starting_resources[d][1];
		_players[i].crystal = starting_resources[d][2];
		_players[i].gems = starting_resources[d][3];
		_players[i].mercury = starting_resources[d][4];
		_players[i].sulfur = starting_resources[d][5];
		_players[i].gold = starting_resources[d][6];
		}
	
	_day = 0;
	_map_xoff = 0;
	_map_yoff = 0;
	_drag_x = 0;
	_drag_y = 0;
	_dragging = false;
	_current_player = 0;
	_current_hero = 0; 
	}
	
void game_t::_end_turn()
	{
	int num_players = 1;
	for(int i = 0; i < num_players; i++)
		{
		_players[i].gold += 1000;
		for(std::set<mine_t*>::iterator it = _players[i].flagged_mines.begin();
			it != _players[i].flagged_mines.end(); it++)
			{
			int p = _current_player;
			switch((*it)->mine_type)
				{
				case wood:		_players[p].wood += 2; break;
				case ore:		_players[p].ore += 2; break;
				case mercury:	_players[p].mercury += 1; break;
				case sulfur:	_players[p].sulfur += 1; break;
				case crystal:	_players[p].crystal += 1; break;
				case gems:		_players[p].gems += 1; break;
				case gold:		_players[p].gold += 1000; break;
				}
			}
		for(int n = 0; n < (int)_players[i].heroes.size(); n++)
			{
			_players[i].heroes[n].movement_left = _players[i].heroes[n].max_movement;
			if(_players[i].heroes[n].current_mana < _players[i].heroes[n].max_mana)
				_players[i].heroes[n].current_mana += 1;
			}
		}
	
	_day++;
	}

void game_t::_hire_hero()
	{
	hero_t hero;
	hero.level = 1;
	hero.experience = 50 + rand() % 100;
	hero.max_movement = 25;
	hero.movement_left = hero.max_movement;
	hero.attack = 8;
	hero.defense = 0;
	hero.power = 3;
	hero.knowledge = 2;
	hero.max_mana = hero.knowledge * 10;
	hero.current_mana = hero.max_mana;
	hero.mapx = 3;
	hero.mapy = 5;
	hero.drawx = 3.f * _tile_size;
	hero.drawy = 5.f * _tile_size;
	hero.name = _players[_current_player].heroes.size() ? "Crag Hack" : "Sandro";
	
	monster_t m;
	m.type = 1;
	m.attack = 3;
	m.defense = 1;
	m.max_hp = 4;
	m.min_damage = 1;
	m.max_damage = 3;
	m.speed = 6;
	m.count = 14;
	
	hero.army[0] = m;
	_players[_current_player].heroes.push_back(hero);	
	}

void game_t::_update_hero()
	{
	if(_players[_current_player].heroes.size() == 0)
		return;
	
	hero_t& hero = _players[_current_player].heroes[_current_hero];	
	
	if(hero.command != hero_t::stop && hero.movement_left > 0)
		{
		if(hero.path.size() == 0)
			{
			hero.moving = false;
			hero.command = hero_t::stop;
			return;
			}
		
		hero.moving = true;
		
		//int pos = hero.path.begin()->pos();
		//int mapx = pos % _map.width;
		//int mapy = pos / _map.height;
		int mapx = hero.path.begin()->x();
		int mapy = hero.path.begin()->y();
		int pos = mapx + (mapy * _map.width);
		
		
		float xt = mapx * _tile_size;
		float yt = mapy * _tile_size;
		
		if((abs(xt - hero.drawx) < _hero_move_speed) && (abs(yt - hero.drawy) < _hero_move_speed) ) //reached next tile in path
			{
			hero.path.pop_front();
			hero.mapx = mapx;
			hero.mapy = mapy;
			hero.drawx = xt;
			hero.drawy = yt;
			hero.movement_left--;
			if(hero.command == hero_t::finish_moving || hero.movement_left == 0)
				{//case where user has clicked to stop the hero, but it isn't done moving
				hero.command = hero_t::stop;
				hero.moving = false;
				}
			if(_map.get_object_at(pos) != 0)
				{
				_visit_object(pos);
				}
			}
		else
			{
			hero.drawx < xt ? hero.drawx += _hero_move_speed : 0;
			hero.drawx > xt ? hero.drawx -= _hero_move_speed : 0;
			hero.drawy < yt ? hero.drawy += _hero_move_speed : 0;
			hero.drawy > yt ? hero.drawy -= _hero_move_speed : 0;
			}
		
		//set camera to be centered on the hero:
		float targetx = (_window.get_width() / 2) - hero.drawx;
		float targety = (_window.get_height() / 2) - hero.drawy;
		if(_map_xoff != targetx)
			_map_xoff += (targetx - _map_xoff) * .2f;
		if(_map_yoff != targety)
			_map_yoff += (targety - _map_yoff) * .2f;
		}
	
	/*
	if(_walking)
		{
		if(_path->size() == 0)
			return;
		
		int pos = *(_path->begin());
		int x = pos % 36;
		int y = pos / 36;
		int xt = x * 32 - 32;
		int yt = y * 32 - 32;
		if(xt == _xpos && yt == _ypos) //we're at the target x and y coordinates
			{
			_path->pop_front();
			_mapx = x;
			_mapy = y;
			if(_path->empty()) //done walking the path
				_walking = false;
			else
				return update();
			}
			
		int speed = 2;
		
		_xpos < xt ? _xpos += speed : 0;
		_xpos > xt ? _xpos -= speed : 0;
		_ypos < yt ? _ypos += speed : 0;
		_ypos > yt ? _ypos -= speed : 0;
		}
	*/
	}

void game_t::_draw_town_screen()
	{
	_town_screen[0]->draw(_gc, CL_Rectf(0, 0, _window.get_width(), _window.get_height()));
	}

void game_t::_set_status(std::string status)
	{
	_status = status;
	_status_time = clock();
	}

bool game_t::_load_sprites()
	{
	_tiles[0] = new CL_Sprite(_gc, "Dirt", &_resources);
	_tiles[1] = new CL_Sprite(_gc, "Sand", &_resources);
	_tiles[2] = new CL_Sprite(_gc, "Grass", &_resources);
	_tiles[3] = new CL_Sprite(_gc, "Snow", &_resources);
	_tiles[4] = new CL_Sprite(_gc, "Swamp", &_resources);
	//_tiles[5] = new CL_Sprite(_gc, "Subterrainian", &_resources);
	_tiles[6] = new CL_Sprite(_gc, "Rough", &_resources);
	_tiles[7] = new CL_Sprite(_gc, "Lava", &_resources);
	_tiles[8] = new CL_Sprite(_gc, "Water", &_resources);
	
	_castles = new CL_Sprite(_gc, "Castles", &_resources);
	
	_resource_icons = new CL_Sprite(_gc, "Resources", &_resources);
	
	_town_screen[0] = new CL_Sprite(_gc, "Town_Screens", &_resources);

	_load_h2_tiles("h2tiles_hires");
	
	_topleft_ui = new CL_Sprite(_gc, "interface/topleft.png");
	
	CL_SpriteDescription desc;
	CL_PixelBuffer pb("interface/cursor1.png");
	desc.add_frame(pb);
	_cursors[0] = new CL_Cursor(_window.get_display_window(), desc, CL_Point(0, 0));
	
	//_audio[0] = new CL_SoundBuffer("audio/track18.mp3");
	
	return true;
	}
	
	
void game_t::on_end_turn_clicked(CL_PushButton* button)
	{
	_end_turn();
	}
	
void game_t::on_cast_spell_clicked(CL_PushButton* button)
	{
	_hire_hero();
	}

player_t& game_t::_get_current_player()
	{
	return _players[_current_player];
	}

void game_t::on_system_options_clicked(CL_PushButton* button)
	{
	//_sys_options_window.set_visible(!_sys_options_window.is_visible());
	_current_hero++;
	if(_current_hero >= _get_current_player().heroes.size())
		_current_hero = 0;
	
	if(_get_current_player().heroes.size() == 0)
		return;
	
	const hero_t& hero = _get_current_player().heroes[_current_hero];
	//set camera to be centered on the hero:
	_map_xoff = (_window.get_width() / 2) - hero.drawx;
	_map_yoff = (_window.get_height() / 2) - hero.drawy;
	}

	
void game_t::on_move_hero_clicked(CL_PushButton* button)
	{
	if(_players[_current_player].heroes.size() == 0)
		return;
	
	hero_t& hero = _players[_current_player].heroes[_current_hero];
	
	if(hero.movement_left == 0 || hero.path.size() == 0)
		return;
			
	if(hero.command == hero_t::move)
		hero.command = hero_t::finish_moving;
	else if(hero.command == hero_t::stop)
		hero.command = hero_t::move;
	}

void game_t::on_mouse_down(const CL_InputEvent& event, const CL_InputState& state)
	{
	if(_game_state == battle_screen)
		{
		_battle_screen_click(event.mouse_pos.x, event.mouse_pos.y);
		return;
		}
	
	if(_window.get_component_at(event.mouse_pos) != &_window)
		return; //we hit one of the buttons or other ui elements
	
	//map.set_terrain(1, 1, 1);
	int mx = (event.mouse_pos.x - _map_xoff) / _tile_size;
	int my = (event.mouse_pos.y - _map_yoff) / _tile_size;
	//map.set_terrain(mx, my, 1);
	if(event.id == CL_MOUSE_MIDDLE && event.type == CL_InputEvent::pressed)
		{
		_dragging = true;
		_drag_x = event.mouse_pos.x - _map_xoff;
		_drag_y = event.mouse_pos.y - _map_yoff;
		}
	else
		{
		if(_players[_current_player].heroes.size() == 0)
			return;
		hero_t& hero = _players[_current_player].heroes[_current_hero];
		
		//if(hero.path.size() == 0 || mx != (hero.path.back().pos() % _map.width) || my != (hero.path.back().pos() / _map.height))
		if(1)
			{//recompute new path
			hero.path = _compute_hero_path(hero.mapx, hero.mapy, mx, my);
			if(hero.command == hero_t::move)
				hero.command = hero_t::finish_moving;
			}
		else if(hero.movement_left != 0)//move hero
			{
			if(hero.command == hero_t::move)
				hero.command = hero_t::finish_moving;
			else if(hero.command == hero_t::stop)
				hero.command = hero_t::move;
			}
		}
	}

void game_t::on_mouse_up(const CL_InputEvent& event, const CL_InputState& state)
	{
	//map.set_terrain(1, 1, 1);
	int mx = (event.mouse_pos.x - _map_xoff)/ _tile_size;
	int my = (event.mouse_pos.y - _map_yoff)/ _tile_size;
	//map.set_terrain(mx, my, 0);
	if(event.id == CL_MOUSE_MIDDLE && event.type == CL_InputEvent::released)
		{
		_dragging = false;
		_drag_x = event.mouse_pos.x - _map_xoff;
		_drag_y = event.mouse_pos.y - _map_yoff;
		}
	else if(event.id == CL_MOUSE_WHEEL_UP)
		{
		_map_scale *= 1.1f;
		}
	else if(event.id == CL_MOUSE_WHEEL_DOWN)
		{
		_map_scale *= 0.8f;
		}
	}
	
void game_t::on_mouse_move(const CL_InputEvent& event, const CL_InputState& state)
	{
	int mx = (event.mouse_pos.x - _map_xoff)/ _tile_size;
	int my = (event.mouse_pos.y - _map_yoff)/ _tile_size;
	//map.set_terrain(mx, my, 1);

	_mouse_xtile = mx;
	_mouse_ytile = my;
	
	if(_players[_current_player].heroes.size() > 0)
		{
		hero_t& hero = _players[_current_player].heroes[_current_hero];
		
		//if(_compute_hero_path(hero.mapx, hero.mapy, mx, my).size())
		//	_window.set_cursor(*_cursors[0]);
		//else
		//	_window.set_cursor(CL_StandardCursor::cl_cursor_arrow);
		}
		
	if(_window.get_ic().get_mouse().get_keycode(CL_MOUSE_MIDDLE))
		{
		_map_xoff = event.mouse_pos.x - _drag_x;
		_map_yoff = event.mouse_pos.y - _drag_y;
		/*if(_map_xoff > 0)
			_map_xoff = 0;
		if(_map_xoff > _tile_size * (_tile_size - 30))
			_map_xoff = _tile_size - 1 * (_tile_size - 30);
		if(_map_yoff > _tile_size * _tile_size)
			_map_yoff = _tile_size * _tile_size;
		if(_map_yoff > 0)
			_map_yoff = 0;*/
		}
	}
