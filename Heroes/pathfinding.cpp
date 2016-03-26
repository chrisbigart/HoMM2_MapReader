#include "game.h"

#include <string>
#include <sstream>
#include <set>
#include <list>

#include "path.h"

/*
struct node_t
	{
	node_t(int fcost_ = -1, int gcost_ = -1, int pos_ = -1, int parent_ = -1) : 
			gcost(gcost_), fcost(fcost_), pos(pos_), parent(parent_) { }
	int cost() const { return fcost + gcost; }
	int fcost, gcost, pos, parent;
	bool operator<(const node_t& right) const { return pos < right.pos; }
	};*/
	
int _mh_dist(int xi, int yi, int xf, int yf)
	{
	int xlen = abs(xi- xf);
	int ylen = abs(yi - yf);
	return 10 * (xlen + ylen);
	}

path_t game_t::_compute_hero_path(int xi, int yi, int xf, int yf)
	{  //we can reimplement this more efficiently later if need be
	std::list<node_t> path;
	std::set<node_t> open;
	std::set<node_t> closed;
	
	node_t start(xi, yi);
	start.hcost = _mh_dist(xi, yi, xf, yf);
	node_t end(xf, yf);
	
	//return empty path if destination unreachable
	if(!_map.is_visitable(end.x(), end.y()) && !_map.is_walkable(end.x(), end.y()))	
		return path;
	
	open.insert(node_t(xi, yi));
	
	while(!open.empty())
		{
		node_t cur = *open.begin();
		//find lowest fcost node on the open list
		for(std::set<node_t>::iterator it = open.begin(); it != open.end(); it++)
			{
			if((*it).fcost() < cur.fcost())
				cur = *it;
			}
		//move it to the closed list
		open.erase(cur);
		closed.insert(cur);
		
		node_t adj[8];
		
		adj[0]._x = cur.x() - 1;	adj[0]._y = cur.y();	 //to the left;
		adj[1]._x = cur.x() + 1;	adj[1]._y = cur.y();	 //to the right;
		adj[2]._x = cur.x();		adj[2]._y = cur.y() + 1; //top;
		adj[3]._x = cur.x();		adj[3]._y = cur.y() - 1; //below;
		adj[4]._x = cur.x() - 1;	adj[4]._y = cur.y() + 1; //to the top left;
		adj[5]._x = cur.x() + 1;	adj[5]._y = cur.y() + 1; //to the top right;
		adj[6]._x = cur.x() - 1;	adj[6]._y = cur.y() - 1; //bottom left;
		adj[7]._x = cur.x() + 1;	adj[7]._y = cur.y() - 1; //bottom right;
		
		for(int i = 0; i < 8; i++)
			{
			if(adj[i].x() < 0 || adj[i].x() > _map.width || adj[i].y() < 0 || adj[i].y() > _map.height)
				continue;
			
			if(closed.count(adj[i]))
				continue;
			
			
			if(adj[i] != end)
				{
				if(!_map.is_walkable(adj[i].x(), adj[i].y()))
					continue;
				}
			else
				{//problem:  some objects are 'visitable' only from a certain direction (usually bottom)
				if(!_map.is_visitable(adj[i].x(), adj[i].y()))
					continue;
				}
			
			adj[i]._parent_x = cur.x();
			adj[i]._parent_y = cur.y();			
			
			
			if(open.count(adj[i]))
				{
				set<node_t>::iterator it = open.find(adj[i]);
				node_t nt = *it;
				if(it->gcost > cur.gcost + (i < 4 ? 10 : 14))
					{
					nt.gcost = cur.gcost + (i < 4 ? 10 : 14);
					nt._parent_x = cur.x();
					nt._parent_y = cur.y();
					}
				open.insert(it, nt);
				open.erase(it);
				}
			else
				{				
				adj[i].gcost = cur.gcost + (i < 4 ? 10 : 14);
				adj[i].hcost = _mh_dist(adj[i].x(), adj[i].y(), end.x(), end.y());
				
				open.insert(adj[i]);				
				}
			
			if(adj[i] == end)
				{
				node_t nd = adj[i];
				while(!(nd == start))
					{
					path.push_front(nd);
					if(closed.count(nd.parent()))
						nd = (*closed.find(nd.parent()));
					else if(open.count(nd.parent()))
						nd = (*open.find(nd.parent()));
					else
						return path; //we have a problem
					}
				return path;
				}
			
			
			}	
		}
	return path;
	}
