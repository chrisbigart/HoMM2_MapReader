#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <Windows.h>
#include <Clanlib/display.h>
#include <Clanlib/core.h>
#include <Clanlib/gui.h>

/*
#include "ui.h"
#include "map.h"
#include "map_draw.h"*/

using std::vector;
using std::string;


class game_window_t : public CL_Window
	{
	
	public:
		game_window_t(CL_GUIManager& manager, const CL_DisplayWindowDescription& desc);
		
			
	protected:
		/*void on_render(CL_GraphicContext& gc, const CL_Rect& clip_rect);
		void on_mouse_move(const CL_InputEvent& button, const CL_InputState& state);
		void on_mouse_down(const CL_InputEvent& button, const CL_InputState& state);
		void on_mouse_up(const CL_InputEvent& button, const CL_InputState& state);*/
		
	/*private:
		ui_t _ui;
		map_t _map;
		map_draw_t _map_draw;
	
	private:
		int _map_xoff, _map_yoff;
		bool _dragging;
		int _drag_x, _drag_y;
		int _day;*/
	};

#endif
