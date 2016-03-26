#ifndef PATH_H
#define PATH_H

#include <list>

struct node_t
	{
	node_t(int x = 0, int y = 0) :
		_x(x), _y(y), _parent_x(-1), _parent_y(-1), gcost(0), hcost(0) { }
	node_t(int x, int y, const node_t& parent) :
		_x(x), _y(y), _parent_x(parent.x()), _parent_y(parent.y()), gcost(0), hcost(0) { }
		
	int fcost() const { return hcost + gcost; }
	int x() const { return _x; }
	int y() const { return _y; }
	int _x, _y;
	int gcost, hcost;
	int _parent_x, _parent_y;
	node_t parent() { return node_t(_parent_x, _parent_y); }
	bool operator<(const node_t& right) const
		{
		if(_x != right._x)
			return _x < right._x;
		else
			return _y < right._y;
		}
	bool operator==(const node_t& right) const
		{
		return (_x == right._x && _y == right._y);
		}
	bool operator!=(const node_t& right) const { return !(operator==(right)); }
	};
	
typedef std::list<node_t> path_t;

#endif
