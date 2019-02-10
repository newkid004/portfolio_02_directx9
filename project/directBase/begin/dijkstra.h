#pragma once
#include "kGlobalDefine.h"

constexpr float MAX_DIST = FLT_MAX;

template<typename type_pos>
class dijkstra
{
public :
	class node
	{
	public :
		type_pos pos;

	public :
		node(type_pos & position) : pos(position) {}
		~node() {}
	};

private :
	virtual float distance(node & n1, node & n2) = 0;
	virtual bool compare(node & n1, node & n2) = 0;

public:
	dijkstra() {};
	~dijkstra() {};
};

