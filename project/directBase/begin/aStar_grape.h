#pragma once
#include "kGlobalDefine.h"
#include "pathfind_grape.h"

class aStar_node;
class aStar_runner;

class aStar_grape : public pathfind_grape
{
public :
	typedef std::vector<aStar_node*> LIST;

public :
	struct info_distance
	{
		float F = 0.0f;
		float G = 0.0f;
		float H = 0.0f;
	};

protected :
	LIST _vNodeList;

	// test
	aStar_node* _currentNode = nullptr;
	aStar_node* _destNode = nullptr;

public :
	void addNode(aStar_node* input);

	void pathfind(std::stack<aStar_runner> & out_path, aStar_node* sour, aStar_node* dest);

public :
	static float calDistance(aStar_node* n1, aStar_node* n2);
	static float calDistance(aStar_node* n1, D3DXVECTOR3 & pos);

public :
	constexpr aStar_node* & operator[](int index) { _vNodeList[index]; }

public :
	constexpr LIST & getNodeList(void) { return _vNodeList; }

	// test
	aStar_node* getCurrentNode(void) { return _currentNode; }
	aStar_node* getDestNode(void) { return _destNode; }

public:
	aStar_grape() {};
	~aStar_grape();
};
