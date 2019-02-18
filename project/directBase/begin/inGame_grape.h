#pragma once
#include "kGlobalDefine.h"
#include "aStar_grape_bind.h"

class inGame_node;

class inGame_grape : public aStar_grape_bind<inGame_node>
{
public :
	//	< listInterval >
	//	- 0 : wall		staticMesh
	//	- 1 : prop		staticMesh
	//	- 2 : enemy		characterBase
	//	- 3 : survivor	characterBase
	template<typename T>
	void putData(T & data, int listInterval, D3DXVECTOR3 & position, float radius);

public:
	inGame_grape() {};
	~inGame_grape() {};
};

#include "inGame_grape.hpp"
