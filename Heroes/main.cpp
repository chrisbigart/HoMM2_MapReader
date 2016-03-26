#include <ClanLib/application.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/gui.h>
//#include <ClanLib/sound.h>

//#include "ui.h"
#include "game.h"

/*
int main()
	{
	map_t m;
	m.load("mr.h3m");
	getchar();
	return 0;
	}*/


class game_app_t
	{
	public:
	static int main(const std::vector<CL_String>& args)
		{		
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;
		CL_SetupGUI setup_gui;
		//CL_SetupSound setup_sound;

		CL_GUIManager gui;
		CL_ResourceManager resources("GUIThemeAero/resources.xml");
		
		CL_GUIWindowManagerSystem wm;
		gui.set_window_manager(wm);
		
		CL_GUIThemeDefault theme;
		theme.set_resources(resources);
		gui.set_theme(theme); 
		gui.set_css_document("GUIThemeAero/theme.css");
		
		CL_DisplayWindowDescription desc("Heroes");
		desc.set_size(CL_Size(800, 600), true);
		desc.set_allow_resize(true);
		
		game_t game(gui, desc);
		
		return 0;
	}
};

CL_ClanApplication app(&game_app_t::main);

int main(int, char**)
	{
	return game_app_t::main(std::vector<CL_String>());
	}