#include "mapObjectBase.h"
#include "managerList.h"

typedef mapObjectBase::MAPLIST MAPLIST;

mapObjectBase::mapObjectBase()
{
}

mapObjectBase::~mapObjectBase()
{
	for (auto rValue : m_oMapObjectList)
	{
		SAFE_DELETE(rValue.second);
	}
}

void mapObjectBase::init(void)
{
	std::string effectFilePath = "resource/effect/example_16.fx";
	

	addMapObject("floor1TopWall",	 "resource/mesh/L4D1/map/wall/floor1TopWall.x", effectFilePath);
	addMapObject("floor1LeftWall",	 "resource/mesh/L4D1/map/wall/floor1LeftWall.x", effectFilePath);
	addMapObject("floor1RightWall",	 "resource/mesh/L4D1/map/wall/floor1RightWall.x", effectFilePath);
	addMapObject("floor1BottomWall",  "resource/mesh/L4D1/map/wall/floor1BottomWall.x", effectFilePath);
	
	addMapObject("floor1_room1_top", "resource/mesh/L4D1/map/wall/floor1_room1_top.x", effectFilePath);
	addMapObject("floor1_room1_right", "resource/mesh/L4D1/map/wall/floor1_room1_right.x", effectFilePath);
	addMapObject("floor1_room1_right2", "resource/mesh/L4D1/map/wall/floor1_room1_right2.x", effectFilePath);
	addMapObject("floor1_room1_doorLoop", "resource/mesh/L4D1/map/wall/floor1_room1_doorLoop.x", effectFilePath);
	addMapObject("floor1_room2_bottom", "resource/mesh/L4D1/map/wall/floor1_room2_bottom.x", effectFilePath);
	addMapObject("floor1_room2_bottom2", "resource/mesh/L4D1/map/wall/floor1_room2_bottom2.x", effectFilePath);
	addMapObject("floor1_room2_top", "resource/mesh/L4D1/map/wall/floor1_room2_top.x", effectFilePath);
	addMapObject("floor1_room2_doorLoop", "resource/mesh/L4D1/map/wall/floor1_room2_doorLoop.x", effectFilePath);
	addMapObject("floor1_room2_left", "resource/mesh/L4D1/map/wall/floor1_room2_left.x", effectFilePath);
	addMapObject("floor1_room3_bottom", "resource/mesh/L4D1/map/wall/floor1_room3_bottom.x", effectFilePath);
	addMapObject("floor1_room3_bottom2", "resource/mesh/L4D1/map/wall/floor1_room3_bottom2.x", effectFilePath);
	addMapObject("floor1_room3_bottom3", "resource/mesh/L4D1/map/wall/floor1_room3_bottom3.x", effectFilePath);
	addMapObject("floor1_room3_bottom4", "resource/mesh/L4D1/map/wall/floor1_room3_bottom4.x", effectFilePath);
	addMapObject("floor1_room3_doorLoop", "resource/mesh/L4D1/map/wall/floor1_room3_doorLoop.x", effectFilePath);
	
	addMapObject("stairs1", "resource/mesh/L4D1/map/wall/stairs1.x", effectFilePath);
	addMapObject("stairWall", "resource/mesh/L4D1/map/wall/stairWall.x", effectFilePath);
		
	scaleMap(D3DXVECTOR3(0.0254f, 0.0254f, 0.0254f));
	setMapObjectRotation("stairs1", D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	setMapObjectRotation("stairWall", D3DXVECTOR3(0.0f, 180.0f, 0.0f));

	setMapObjectPosition("floor1TopWall",			D3DXVECTOR3(0.0f,	5, 59.5f));
	setMapObjectPosition("floor1LeftWall",			D3DXVECTOR3(-59.5f,	5, 0.0f));
	setMapObjectPosition("floor1RightWall",			D3DXVECTOR3(59.5f,	5, -0.5f));
	setMapObjectPosition("floor1BottomWall",		D3DXVECTOR3(-5, 5,	-59.5f));
	setMapObjectPosition("floor1_room1_top",		D3DXVECTOR3(-34.5, 5, -10.5));
	setMapObjectPosition("floor1_room1_right",		D3DXVECTOR3(-10.5, 5, -16.5));
	setMapObjectPosition("floor1_room1_right2",		D3DXVECTOR3(-10.5, 5, -44.5));
	setMapObjectPosition("floor1_room1_doorLoop",	D3DXVECTOR3(-10.5, 9.5, -26));
	setMapObjectPosition("floor1_room2_bottom",		D3DXVECTOR3(54, 5, -49.5));
	setMapObjectPosition("floor1_room2_bottom2",	D3DXVECTOR3(25.5, 5, -49.5));
	setMapObjectPosition("floor1_room2_top",		D3DXVECTOR3(34.5, 5, -0.5));
	setMapObjectPosition("floor1_room2_doorLoop",	D3DXVECTOR3(45, 9.5, -49.5));
	setMapObjectPosition("floor1_room2_left",		D3DXVECTOR3(9.5, 5, -25));
	setMapObjectPosition("floor1_room3_bottom",		D3DXVECTOR3(-34.5, 5, 0.5));
	setMapObjectPosition("floor1_room3_bottom2",	D3DXVECTOR3(-10.5, 5, 5.5));
	setMapObjectPosition("floor1_room3_bottom3",	D3DXVECTOR3(14.5, 5, 10.5));
	setMapObjectPosition("floor1_room3_bottom4",	D3DXVECTOR3(53.5, 5, 10.5));
	setMapObjectPosition("floor1_room3_doorLoop",	D3DXVECTOR3(44, 9.5, 10.5));
	
	setMapObjectPosition("stairs1",	D3DXVECTOR3(-54.5, 5, 54));
	setMapObjectPosition("stairWall",D3DXVECTOR3(-54.5, 7.5, 49));
}

void mapObjectBase::addMapObject(string key, string meshFilePath, string effectFilePath)
{
	staticMesh::mParam stParameters;
	stParameters.meshFilePath = meshFilePath;
	stParameters.effectFilePath = effectFilePath;

	m_oMapObjectList.insert(MAPLIST::value_type(key, new staticMesh(stParameters)));
}

void mapObjectBase::setMapObjectScale(string key, const D3DXVECTOR3 & a_rstScale)
{
	MAPLIST::iterator iter = m_oMapObjectList.find(key);

	if (iter != m_oMapObjectList.end())
	{
		iter->second->setScale(a_rstScale);
	}
}

void mapObjectBase::setMapObjectRotation(string key, const D3DXVECTOR3 & a_rstRotation)
{
	MAPLIST::iterator iter = m_oMapObjectList.find(key);

	if (iter != m_oMapObjectList.end())
	{
		iter->second->setRotation(a_rstRotation);
	}
}

void mapObjectBase::setMapObjectPosition(string key, const D3DXVECTOR3 & a_rstPosition)
{
	MAPLIST::iterator iter = m_oMapObjectList.find(key);

	if (iter != m_oMapObjectList.end())
	{
		iter->second->setPosition(a_rstPosition);
	}
}

void mapObjectBase::scaleMap(const D3DXVECTOR3 & a_rstScale)
{
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->setScale(a_rstScale);
	}
}

void mapObjectBase::rotateMap(const D3DXVECTOR3 & a_rstRotation)
{
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->rotateX(a_rstRotation.x);
		rValue.second->rotateY(a_rstRotation.y);
		rValue.second->rotateZ(a_rstRotation.z);
	}
}

void mapObjectBase::moveMap(const D3DXVECTOR3 & a_rstMove)
{
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->moveX(a_rstMove.x);
		rValue.second->moveY(a_rstMove.y);
		rValue.second->moveZ(a_rstMove.z);
	}
}
