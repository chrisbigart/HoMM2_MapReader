#include "game.h"

#include <sstream>

 #define Floor2 (X) (((X) >= 0) ? ((X>>1) : (((X)-1)/2))
    #define Ceil2 (X) (((X) >= 0) ? (((X)+1)>>1) : ((X)/2))
    
template<typename T> T floor2(const T& x)
	{
	if(x >= 0)
		return x / 2;
	else
		return (x-1)/2;
	}

template<typename T> T ceil2(const T& x)
	{
	if(x >= 0)
		return (x+1) / 2;
	else
		return x/2;
	}
	

template<typename T> T _hex_dist(const T& sx, const T& sy, const T& ex, const T& ey)
	{
	T ax = sx - floor2(sy);
	T ay = sx + ceil2(sy);
	T bx = ex - floor2(ey);
	T by = ex + ceil2(ey);
	
	T dx = bx - ax;
	T dy = by - ay;
	
	return (abs (dx) + abs (dy) + abs (dx-dy)) / 2;
	}


void game_t::_draw_battle_screen()
	{
	//could be castle battle or other battle...
	//hero.army[0];
	
	static CL_Image hex(_gc, "interface/hex32t.png");
	static CL_Image hexl(_gc, "interface/hex32tl.png");
	static CL_Image hexd(_gc, "interface/hex32td.png");
	
	int sx = (*_battle.attacker_troops.begin()).x;
	int sy = (*_battle.attacker_troops.begin()).y;
	int ss = (*_battle.attacker_troops.begin()).monster.speed;
	
	int mx = _window.get_ic().get_mouse().get_x();
	int my = _window.get_ic().get_mouse().get_y();
	
	
	//strm << mx << ", " << my;
	//_text.draw_text(_gc, 300, 300, strm.str());
	
	//h2 is 9x11
	//h3 is 
	for(int y = 0; y < 16; y++)
		{
		for(int x = 0; x < 22; x++)
			{		
			//CL_Draw::box(_gc, 70+x*30.f, 70 + y*30.f, 70 + (x+1)*30.f, 70 + (y+1)*30.f, CL_Colorf::green);
			hex.draw(_gc, ((y &0x1) ? 83 :70) +x*26.f, 70 + y*24.f);
			//if(abs((x - sx) + (y - sy)) <= ss)
			if(_hex_dist(sx, sy, x, y) <= ss)
				hexl.draw(_gc, ((y &0x1) ? 83 :70) +x*26.f, 70 + y*24.f);
			
			std::stringstream strm;
			strm << _hex_dist(sx, sy, x, y);
			_text.draw_text(_gc, ((y &0x1) ? 83 :70) +x*26.f, 90 + y*24.f, strm.str());
				//CL_Draw::fill(_gc, 70+x*30.f, 70 + y*30.f, 70 + (x+1)*30.f, 70 + (y+1)*30.f, CL_Colorf(0,0,0,.4f));
			if(mx > ((y &0x1) ? 83 :70) + x*26 && mx <= ((y &0x1) ? 109 : 96) + x*26 && my > 70 + y*24.f && my <= 94 + y*24.f)
				hexd.draw(_gc, ((y &0x1) ? 83 :70) +x*26.f, 70 + y*24.f);
			//	CL_Draw::fill(_gc, 70+x*30.f, 70 + y*30.f, 70 + (x+1)*30.f, 70 + (y+1)*30.f, CL_Colorf(0,0,0,.8f));			
			
			}
		}
	
	
	//CL_Image img(_gc, "
	//for(int i = 0; i < 5; i++)
	for(deque<troop_t>::const_iterator it = _battle.attacker_troops.begin(); it != _battle.attacker_troops.end(); it++)
		{
		std::stringstream strm;
		strm << _get_monster_name(it->monster.type) << (it->monster.count > 1 ? "s" : "") << " ("<< it->monster.count << ")";
		CL_Draw::circle(_gc, ((it->y &0x1) ? 93 :78) +it->x*26.f, 78 + it->y*24.f, 10, CL_Colorf(0.0f,0.0f,1.f,.7f));
		_text.draw_text(_gc, ((it->y &0x1) ? 83 :70) +it->x*26.f, 110 + it->y*24.f, strm.str());		
		}
	
	for(deque<troop_t>::const_iterator it = _battle.defender_troops.begin(); it != _battle.defender_troops.end(); it++)
		{
		std::stringstream strm;
		strm << _get_monster_name(it->monster.type) << (it->monster.count > 1 ? "s" : "") << " ("<< it->monster.count << ")";
		CL_Draw::circle(_gc, ((it->y &0x1) ? 93 :78) +it->x*26.f, 78 + it->y*24.f, 10, CL_Colorf(1.f,0.0f,0.0f,.7f));
		_text.draw_text(_gc, 60.f + (it->x * 30.f), 120.f + it->y * 30, strm.str());		
		}
		
	int n = 1, max_msgs = 2;
	for(deque<string>::const_iterator it = _battle.battle_log.begin(); it != _battle.battle_log.end(); it++)
		{
		if(n++ > max_msgs)
			break;
		
		_text.draw_text(_gc, 40, 450 + n*20, *it, CL_Colorf::black);			
		}
	}
