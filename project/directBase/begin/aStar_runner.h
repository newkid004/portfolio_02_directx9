#pragma once
#include "kGlobalDefine.h"

class aStar_node;
class aStar_grape;

class aStar_runner
{
public :
	struct info_distance
	{
		float F = 0.0f;
		float G = 0.0f;
		float H = 0.0f;
	};

	struct comparer
	{
		bool operator()(aStar_runner & p1, aStar_runner & p2);
	};

	struct member
	{
		aStar_runner* prevRunner = nullptr;		// parent

		aStar_node* placedNode = nullptr;
		aStar_node* prevNode = nullptr;

		info_distance distance;
	};

protected :
	member _member;

public :
	constexpr member & getMember(void) { return _member; }

public:
	aStar_runner(aStar_node* startNode) { _member.placedNode = startNode; }
	aStar_runner(aStar_runner & prevRunner, aStar_node* placedNode);
	~aStar_runner() {}
};

