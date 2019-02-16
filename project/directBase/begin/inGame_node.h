#pragma once
#include "kGlobalDefine.h"

class aStar_node;

class staticMesh;
class characterBase;

class inGame_node
{
public :
	struct listSet
	{
		std::list<staticMesh*> wall;
		std::list<staticMesh*> prop;
		std::list<characterBase*> enemy;
		std::list<characterBase*> survivor;
	};

protected :
	D3DXVECTOR3		_position;
	float			_radius = 1.0f;

	listSet _listSet;

public :
	constexpr D3DXVECTOR3 & getPosition(void) { return _position; }
	constexpr float getRadius(void) { return _radius; }

	constexpr listSet & getListSet(void) { return _listSet; }

public :
	static inGame_node* getData(aStar_node* node);

public :
	inGame_node(D3DXVECTOR3 & position, float radius = 1.0f) : 
		_position(position), _radius(radius) {};
	virtual ~inGame_node() {};
};