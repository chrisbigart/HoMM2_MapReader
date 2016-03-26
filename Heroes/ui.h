#ifndef UI_H
#define UI_H

#include <Clanlib/gui.h>

class game_window_t;

class ui_t
	{
	public:
		ui_t(game_window_t* parent);
		void draw(CL_GraphicContext& gc);
		void show_system_options();
	
	protected:
		void on_end_turn_clicked(CL_PushButton* button);
		void on_move_hero_clicked(CL_PushButton* button);
		void on_cast_spell_turn_clicked(CL_PushButton* button);
		void on_adventure_options_clicked(CL_PushButton* button);
		void on_system_options_clicked(CL_PushButton* button);
		void on_kingdom_overview_clicked(CL_PushButton* button);
		
		void on_ui_resize(CL_Slider* slider);
		
	protected:
		void _resize();
		
	private:
		float _scale;
		game_window_t& _parent;
		CL_PushButton _end_turn, _move_hero, _cast_spell,
			_adventure_options, _system_options, _kingdom_overview;
			
		CL_Slider _ui_scale;
		CL_Sprite* _resource_icons;
		//CL_Window _sys_options_window;
	};


#endif
