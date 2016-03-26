#ifndef GAME_H
#define GAME_H

#include <Windows.h>

#include "battle.h"
#include "game_window.h"
#include "map.h"
#include "player.h"

#include <Clanlib/display.h>
#include <Clanlib/core.h>
#include <Clanlib/gui.h>
//#include <ClanLib/sound.h>

class game_t
	{
	public:
		game_t(CL_GUIManager& manager, const CL_DisplayWindowDescription& desc);
		
		static std::string _get_monster_name(int type);
		
	protected:		
		bool _load_sprites();
		bool _load_h2_tiles(const std::string& filename);
		bool _load_h2_objects();
		bool _load_h2_object(int, int);
		int _get_number_of_animation_frames(const object_t& obj);
		
		bool _load_map();
		void _load_monsters();
		bool _load_heroes3_map(const std::string& filename);
		bool _load_heroes2_map(const std::string& filename);
		void _compute_passability(unsigned char arr[6], int objx, int objy, object_t* obj);
		
		void _draw_terrain();
		void _draw_map_objects();
		void _draw_terrain_level1(bool over);
		void _draw_terrain_level2(bool over);
		void _draw_town_screen();
		void _draw_battle_screen();
		void _visit_object(int pos);
		void _set_status(std::string status);
		
	protected: //game functions
		void _end_turn();
		void _new_game();
		
		void _hire_hero();
		player_t& _get_current_player();
		void _update_hero();
		path_t _compute_hero_path(int xi, int yi, int xf, int yf);
		//int _mh_dist(int st, int end);
		void _init_battle();//battle_e type, army_t attacker, army_t defender);
		void _update_battle();
		void _battle_screen_click(int mx, int my);
		
	protected: //ui functions
		void _resize_ui();
		void _draw_ui();
		void _draw_resources_ui();
		void _fade_out();
		
	//ui callbacks
		void on_end_turn_clicked(CL_PushButton* button);
		void on_move_hero_clicked(CL_PushButton* button);
		void on_cast_spell_clicked(CL_PushButton* button);
		void on_adventure_options_clicked(CL_PushButton* button);
		void on_system_options_clicked(CL_PushButton* button);
		void on_kingdom_overview_clicked(CL_PushButton* button);
		
		void on_ui_resize(CL_Slider* slider);
		void on_map_resize(CL_Slider* slider);
		
		void on_render(CL_GraphicContext& gc, const CL_Rect& clip_rect);
		
		void on_mouse_move(const CL_InputEvent& button, const CL_InputState& state);
		void on_mouse_down(const CL_InputEvent& button, const CL_InputState& state);
		void on_mouse_up(const CL_InputEvent& button, const CL_InputState& state);
		
		void on_key_down(const CL_InputEvent& key, const CL_InputState& state);
		
	private:
		game_window_t _window;
		map_t _map;
	
	//ClanLib classes
		CL_GraphicContext& _gc;
		CL_ResourceManager _resources;
		CL_Font_System _text;
	
	//UI data/controls
		float _ui_scale;
		float _map_scale;
		std::string _status;
		CL_PushButton _end_turn_button, _move_hero_button, _cast_spell_button,
			_adventure_options_button, _system_options_button, _kingdom_overview_button;
			
		CL_ToolBar _hero_listview;
			
		CL_Slider _ui_scale_slider;
		CL_Slider _map_scale_slider;
		CL_Sprite* _resource_icons;
		CL_Sprite* _topleft_ui;
		CL_Cursor* _cursors[10];
		
	//sprites		
		CL_Sprite* _tiles[10];
		std::vector<CL_Sprite> _h2_tiles;
		std::map<std::pair<int, int>, CL_Sprite> _h2_objects;
		CL_Sprite* _castles;
		CL_Sprite* _town_screen[10];
		
	//audio
		//CL_SoundBuffer* _audio[10];

	//debug drawing options
		bool _draw_terrain_tiles;
		bool _draw_map_objects_flag;
		bool _draw_map_overlays;
		bool _draw_overlay_boxes;
		bool _draw_debug_flags[10];

	//stuff
		int _tile_size;
		int _map_xoff, _map_yoff;
		bool _dragging;
		int _drag_x, _drag_y;
		int _mouse_xtile, _mouse_ytile;
		float _hero_move_speed, _enemy_move_speed;
		int _status_time;
		enum game_state_e
			{
			adventure_map, town_screen, battle_screen
			} _game_state;
		enum battle_state_e
			{
			waiting, spell_cast, creature_moving, creature_attacking, creature_retaliating
			} _battle_state;
	
	//game variables
		int _day;
		int _num_players;
		int _current_player, _current_hero;
		player_t _players[8];
		battle_t _battle;
	};


#endif
