#include "mapObjectBase.h"
#include "managerList.h"

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
	

	addMapObject("floorTopWall",	 "resource/mesh/L4D1/map/wall/floorTopWall.x", effectFilePath);
	addMapObject("floorLeftWall",	 "resource/mesh/L4D1/map/wall/floorLeftWall.x", effectFilePath);
	addMapObject("floorRightWall",	 "resource/mesh/L4D1/map/wall/floorRightWall.x", effectFilePath);
	addMapObject("floorBottomWall",  "resource/mesh/L4D1/map/wall/floorBottomWall.x", effectFilePath);
	addMapObject("floorBottomWall2", "resource/mesh/L4D1/map/wall/floorBottomWall2.x", effectFilePath);
	
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
	/*
	addMapObject("stairs1_1",  "resource/mesh/L4D1/map/wall/stairs1_1.x", effectFilePath);
	addMapObject("stairs1_2",  "resource/mesh/L4D1/map/wall/stairs1_2.x", effectFilePath);
	addMapObject("stairs1_3",  "resource/mesh/L4D1/map/wall/stairs1_3.x", effectFilePath);
	addMapObject("stairs1_4",  "resource/mesh/L4D1/map/wall/stairs1_4.x", effectFilePath);
	addMapObject("stairs1_5",  "resource/mesh/L4D1/map/wall/stairs1_5.x", effectFilePath);
	addMapObject("stairs1_6",  "resource/mesh/L4D1/map/wall/stairs1_6.x", effectFilePath);
	addMapObject("stairs1_7",  "resource/mesh/L4D1/map/wall/stairs1_7.x", effectFilePath);
	addMapObject("stairs1_8",  "resource/mesh/L4D1/map/wall/stairs1_8.x", effectFilePath);
	addMapObject("stairs1_9",  "resource/mesh/L4D1/map/wall/stairs1_9.x", effectFilePath);
	addMapObject("stairs1_10", "resource/mesh/L4D1/map/wall/stairs1_10.x", effectFilePath);
	addMapObject("stairs1_11", "resource/mesh/L4D1/map/wall/stairs1_11.x", effectFilePath);
	addMapObject("stairs1_12", "resource/mesh/L4D1/map/wall/stairs1_12.x", effectFilePath);
	addMapObject("stairs1_13", "resource/mesh/L4D1/map/wall/stairs1_13.x", effectFilePath);
	addMapObject("stairs1_14", "resource/mesh/L4D1/map/wall/stairs1_14.x", effectFilePath);
	addMapObject("stairs1_15", "resource/mesh/L4D1/map/wall/stairs1_15.x", effectFilePath);
	addMapObject("stairs1_16", "resource/mesh/L4D1/map/wall/stairs1_16.x", effectFilePath);
	addMapObject("stairs1_17", "resource/mesh/L4D1/map/wall/stairs1_17.x", effectFilePath);
	addMapObject("stairs1_18", "resource/mesh/L4D1/map/wall/stairs1_18.x", effectFilePath);
	addMapObject("stairs1_19", "resource/mesh/L4D1/map/wall/stairs1_19.x", effectFilePath);
	addMapObject("stairs1_20", "resource/mesh/L4D1/map/wall/stairs1_20.x", effectFilePath);
	addMapObject("stairs1_21", "resource/mesh/L4D1/map/wall/stairs1_21.x", effectFilePath);

	addMapObject("stairWall_in1",  "resource/mesh/L4D1/map/wall/stairWall_in1.x", effectFilePath);
	addMapObject("stairWall_in2",  "resource/mesh/L4D1/map/wall/stairWall_in2.x", effectFilePath);
	addMapObject("stairWall_in3",  "resource/mesh/L4D1/map/wall/stairWall_in3.x", effectFilePath);
	addMapObject("stairWall_in4",  "resource/mesh/L4D1/map/wall/stairWall_in4.x", effectFilePath);
	addMapObject("stairWall_in5",  "resource/mesh/L4D1/map/wall/stairWall_in5.x", effectFilePath);
	addMapObject("stairWall_in6",  "resource/mesh/L4D1/map/wall/stairWall_in6.x", effectFilePath);
	addMapObject("stairWall_in7",  "resource/mesh/L4D1/map/wall/stairWall_in7.x", effectFilePath);
	addMapObject("stairWall_in8",  "resource/mesh/L4D1/map/wall/stairWall_in8.x", effectFilePath);
	addMapObject("stairWall_in9",  "resource/mesh/L4D1/map/wall/stairWall_in9.x", effectFilePath);
	addMapObject("stairWall_in10", "resource/mesh/L4D1/map/wall/stairWall_in10.x", effectFilePath);
	addMapObject("stairWall_out1", "resource/mesh/L4D1/map/wall/stairWall_out1.x", effectFilePath);
	addMapObject("stairWall_out2", "resource/mesh/L4D1/map/wall/stairWall_out2.x", effectFilePath);
	addMapObject("stairWall_out3", "resource/mesh/L4D1/map/wall/stairWall_out3.x", effectFilePath);
	addMapObject("stairWall_out4", "resource/mesh/L4D1/map/wall/stairWall_out4.x", effectFilePath);
	addMapObject("stairWall_out5", "resource/mesh/L4D1/map/wall/stairWall_out5.x", effectFilePath);
	addMapObject("stairWall_out6", "resource/mesh/L4D1/map/wall/stairWall_out6.x", effectFilePath);
	addMapObject("stairWall_out7", "resource/mesh/L4D1/map/wall/stairWall_out7.x", effectFilePath);
	addMapObject("stairWall_out8", "resource/mesh/L4D1/map/wall/stairWall_out8.x", effectFilePath);
	addMapObject("stairWall_out9", "resource/mesh/L4D1/map/wall/stairWall_out9.x", effectFilePath);
	addMapObject("stairWall_out10", "resource/mesh/L4D1/map/wall/stairWall_out10.x", effectFilePath);
	*/
	scaleMap(D3DXVECTOR3(0.0254f, 0.0254f, 0.0254f));

	setMapObjectPosition("floorTopWall",			D3DXVECTOR3(0.0f,	10.5f, 39.5f));
	setMapObjectPosition("floorLeftWall",			D3DXVECTOR3(-39.5f,	10.5f, 0.0f));
	setMapObjectPosition("floorRightWall",			D3DXVECTOR3(39.5f,	10.5f, -0.5f));
	setMapObjectPosition("floorBottomWall",			D3DXVECTOR3(-5, 5,	-39.5f));
	setMapObjectPosition("floorBottomWall2",		D3DXVECTOR3(-0.5f,	15.48f, -39.5f));
	setMapObjectPosition("floor1_room1_top",		D3DXVECTOR3(-24.5, 5, -10.5));
	setMapObjectPosition("floor1_room1_right",		D3DXVECTOR3(-10.5, 5, -16.5));
	setMapObjectPosition("floor1_room1_right2",		D3DXVECTOR3(-10.5, 5, -33.5));
	setMapObjectPosition("floor1_room1_doorLoop",	D3DXVECTOR3(-10.5, 9.5, -25));
	setMapObjectPosition("floor1_room2_bottom",		D3DXVECTOR3(33.5, 5, -29.499998));
	setMapObjectPosition("floor1_room2_bottom2",	D3DXVECTOR3(11, 5, -29.499998));
	setMapObjectPosition("floor1_room2_top",		D3DXVECTOR3(19.5, 5, -0.5));
	setMapObjectPosition("floor1_room2_doorLoop",	D3DXVECTOR3(25, 9.5, -29.499998));
	setMapObjectPosition("floor1_room2_left",		D3DXVECTOR3(0.5, 5, -15));
	setMapObjectPosition("floor1_room3_bottom",		D3DXVECTOR3(-24.5, 5, 0.5));
	setMapObjectPosition("floor1_room3_bottom2",	D3DXVECTOR3(-10.5, 5, 5.5));
	setMapObjectPosition("floor1_room3_bottom3",	D3DXVECTOR3(5.5, 5, 10.5));
	setMapObjectPosition("floor1_room3_bottom4",	D3DXVECTOR3(33.5, 5, 10.5));
	setMapObjectPosition("floor1_room3_doorLoop",	D3DXVECTOR3(25, 9.5, 10.5));
	/*
	setMapObjectPosition("stairs1_1",				D3DXVECTOR3(-29.75, 0.25, 36.5));
	setMapObjectPosition("stairs1_2",				D3DXVECTOR3(-30.25, 0.5, 36.5));
	setMapObjectPosition("stairs1_3",				D3DXVECTOR3(-30.75, 0.75, 36.5));
	setMapObjectPosition("stairs1_4",				D3DXVECTOR3(-31.25, 1, 36.5));
	setMapObjectPosition("stairs1_5",				D3DXVECTOR3(-31.75, 1.25, 36.5));
	setMapObjectPosition("stairs1_6",				D3DXVECTOR3(-32.25, 1.5, 36.5));
	setMapObjectPosition("stairs1_7",				D3DXVECTOR3(-32.75, 1.75, 36.5));
	setMapObjectPosition("stairs1_8",				D3DXVECTOR3(-33.25, 2, 36.5));
	setMapObjectPosition("stairs1_9",				D3DXVECTOR3(-33.75, 2.25, 36.5));
	setMapObjectPosition("stairs1_10",				D3DXVECTOR3(-36.5, 2.5, 36.5));
	setMapObjectPosition("stairs1_11",				D3DXVECTOR3(-36.75, 2.5, 31.5));
	setMapObjectPosition("stairs1_12",				D3DXVECTOR3(-34.25, 5.25, 31.5));
	setMapObjectPosition("stairs1_13",				D3DXVECTOR3(-33.75, 5.5, 31.5));
	setMapObjectPosition("stairs1_14",				D3DXVECTOR3(-33.25, 6, 31.5));
	setMapObjectPosition("stairs1_15",				D3DXVECTOR3(-32.75, 6.5, 31.5));
	setMapObjectPosition("stairs1_16",				D3DXVECTOR3(-32.25, 7, 31.5));
	setMapObjectPosition("stairs1_17",				D3DXVECTOR3(-31.75, 7.5, 31.5));
	setMapObjectPosition("stairs1_18",				D3DXVECTOR3(-31.25, 8, 31.5));
	setMapObjectPosition("stairs1_19",				D3DXVECTOR3(-30.75, 8.5, 31.5));
	setMapObjectPosition("stairs1_20",				D3DXVECTOR3(-30.25, 9, 31.5));
	setMapObjectPosition("stairs1_21",				D3DXVECTOR3(-29.75, 9.5, 31.489859));

	setMapObjectPosition("stairWall_in1",   D3DXVECTOR3(-36.75, 7.5, 29));
	setMapObjectPosition("stairWall_in2",   D3DXVECTOR3(-34.25, 7.5, 29));
	setMapObjectPosition("stairWall_in3",   D3DXVECTOR3(-33.75, 7.75, 29));
	setMapObjectPosition("stairWall_in4",   D3DXVECTOR3(-33.25, 8, 29));
	setMapObjectPosition("stairWall_in5",   D3DXVECTOR3(-32.75, 8.25, 29));
	setMapObjectPosition("stairWall_in6",   D3DXVECTOR3(-32.25, 8.5, 29));
	setMapObjectPosition("stairWall_in7",   D3DXVECTOR3(-31.75, 8.75, 29));
	setMapObjectPosition("stairWall_in8",   D3DXVECTOR3(-31.25, 9, 29));
	setMapObjectPosition("stairWall_in9",   D3DXVECTOR3(-30.75, 9.25, 29));
	setMapObjectPosition("stairWall_in10",  D3DXVECTOR3(-30.25, 9.5, 29));
	setMapObjectPosition("stairWall_out1",  D3DXVECTOR3(-36.75, 7.5, 28.99));
	setMapObjectPosition("stairWall_out2",  D3DXVECTOR3(-34.25, 7.5, 28.99));
	setMapObjectPosition("stairWall_out3",  D3DXVECTOR3(-33.75, 7.75, 28.99));
	setMapObjectPosition("stairWall_out4",  D3DXVECTOR3(-33.25, 8, 28.99));
	setMapObjectPosition("stairWall_out5",  D3DXVECTOR3(-32.75, 8.25, 28.99));
	setMapObjectPosition("stairWall_out6",  D3DXVECTOR3(-32.25, 8.5, 28.99));
	setMapObjectPosition("stairWall_out7",  D3DXVECTOR3(-31.75, 8.75, 28.99));
	setMapObjectPosition("stairWall_out8",  D3DXVECTOR3(-31.25, 9, 28.99));
	setMapObjectPosition("stairWall_out9",  D3DXVECTOR3(-30.75, 9.25, 28.99));
	setMapObjectPosition("stairWall_out10",	D3DXVECTOR3(-30.25, 9.5, 28.99));
	*/
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
