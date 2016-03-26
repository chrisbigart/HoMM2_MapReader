#include "game_window.h"

game_window_t::game_window_t(CL_GUIManager& manager, const CL_DisplayWindowDescription& desc)
	: CL_Window(&manager, desc)
	//, _ui(this),
	//_dragging(false), _map_xoff(0), _map_yoff(0), _drag_x(0), _drag_y(0), _day(0)
	{
	//func_render().set(this, &game_window_t::on_render);
	//CL_Slot slot_mouse_move = (get_ic().get_mouse().sig_pointer_move().connect(this, &game_window_t::on_mouse_move));
	//CL_Slot slot_mouse_down = (get_ic().get_mouse().sig_key_down().connect(this, &game_window_t::on_mouse_down));
	//CL_Slot slot_mouse_up = (get_ic().get_mouse().sig_key_up().connect(this, &game_window_t::on_mouse_up));
	
	}
/*
void game_window_t::on_render(CL_GraphicContext& gc, const CL_Rect& clip_rect)
	{
	gc.clear();
	_map_draw.set_offsets(_map_xoff, _map_yoff);
	_map_draw.draw(gc, _map);
	_ui.draw(gc);
	
	//factor this out to somewhere else...
	CL_Font_System text(gc, "Arial", 18);
	const string& objname = _map.get_object_name_at((get_ic().get_mouse().get_x() - _map_xoff) / _tile_size, 
													(get_ic().get_mouse().get_y() - _map_yoff) / _tile_size); //fixme
	text.draw_text(gc, 0, get_height() - 20, objname);
	}
*/
/*
void game_window_t::on_mouse_down(const CL_InputEvent& event, const CL_InputState& state)
	{
	//map.set_terrain(1, 1, 1);
	int mx = (event.mouse_pos.x - _map_xoff)/ _tile_size;
	int my = (event.mouse_pos.y - _map_yoff)/ _tile_size;
	//map.set_terrain(mx, my, 1);
	if(event.id == CL_MOUSE_MIDDLE && event.type == CL_InputEvent::pressed)
		{
		_dragging = true;
		_drag_x = event.mouse_pos.x - _map_xoff;
		_drag_y = event.mouse_pos.y - _map_yoff;
		}
	else
		{
		//path = map.get_path(player.hero.get_mapx(), player.hero.get_mapy(), mx, my);
		//player.hero.walk_path(path);
		}
	}

void game_window_t::on_mouse_up(const CL_InputEvent& event, const CL_InputState& state)
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
	}
	
void game_window_t::on_mouse_move(const CL_InputEvent& event, const CL_InputState& state)
	{
	int mx = (event.mouse_pos.x - _map_xoff)/ _tile_size;
	int my = (event.mouse_pos.y - _map_yoff)/ _tile_size;
	//map.set_terrain(mx, my, 1);
	if(_dragging)
		{
		_map_xoff = event.mouse_pos.x - _drag_x;
		_map_yoff = event.mouse_pos.y - _drag_y;
		if(map_xoff > 0)
			map_xoff = 0;
		if(map_xoff > _tile_size * (_tile_width - 30))
			map_xoff = _tile_size - 1 * (_tile_width - 30);
		if(map_yoff > _tile_size * _tile_height)
			map_yoff = _tile_size * _tile_height;
		if(map_yoff > 0)
			map_yoff = 0;
		}
	}
*/
