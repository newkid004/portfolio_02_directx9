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
	addMapObject("stairs1_1", "resource/mesh/L4D1/map/wall/stairs1_1.x", effectFilePath);
	addMapObject("stairs1_2", "resource/mesh/L4D1/map/wall/stairs1_2.x", effectFilePath);
	addMapObject("stairs1_3", "resource/mesh/L4D1/map/wall/stairs1_3.x", effectFilePath);
	addMapObject("stairs1_4", "resource/mesh/L4D1/map/wall/stairs1_4.x", effectFilePath);
	addMapObject("stairs1_5", "resource/mesh/L4D1/map/wall/stairs1_5.x", effectFilePath);
	addMapObject("stairs1_6", "resource/mesh/L4D1/map/wall/stairs1_6.x", effectFilePath);
	addMapObject("stairs1_7", "resource/mesh/L4D1/map/wall/stairs1_7.x", effectFilePath);
	addMapObject("stairs1_8", "resource/mesh/L4D1/map/wall/stairs1_8.x", effectFilePath);
	addMapObject("stairs1_9", "resource/mesh/L4D1/map/wall/stairs1_9.x", effectFilePath);
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

	scaleMap(D3DXVECTOR3(0.0254f, 0.0254f, 0.0254f));

	setMapObjectPosition("floorTopWall",			D3DXVECTOR3(0.0f,		10.5f, 39.5f));
	setMapObjectPosition("floorLeftWall",			D3DXVECTOR3(-39.5f,		10.5f, 0.0f));
	setMapObjectPosition("floorRightWall",			D3DXVECTOR3(39.5f,		10.5f, -0.5f));
	setMapObjectPosition("floorBottomWall",			D3DXVECTOR3(-5, 5,		39.5f));
	setMapObjectPosition("floorBottomWall2",		D3DXVECTOR3(-0.5f,		15.48f, -39.5f));
	setMapObjectPosition("floor1_room1_top",		D3DXVECTOR3(-1.3493729, 8.578998, -22.287859));
	setMapObjectPosition("floor1_room1_right",		D3DXVECTOR3(12.650627,  8.578998, -28.287859));
	setMapObjectPosition("floor1_room1_right2",		D3DXVECTOR3(12.650627,  8.578998, -45.287857));
	setMapObjectPosition("floor1_room1_doorLoop",	D3DXVECTOR3(12.650627,  4.0789976, -36.787857));
	setMapObjectPosition("floor1_room2_bottom",		D3DXVECTOR3(56.650627,  8.578998, -41.287857));
	setMapObjectPosition("floor1_room2_bottom2",	D3DXVECTOR3(34.150627,  8.578998, -41.287857));
	setMapObjectPosition("floor1_room2_top",		D3DXVECTOR3(42.650627,  8.578998, -12.287859));
	setMapObjectPosition("floor1_room2_doorLoop",	D3DXVECTOR3(48.150627,  4.0789976, -41.287857));
	setMapObjectPosition("floor1_room2_left",		D3DXVECTOR3(23.650627,  8.578998, -26.787859));
	setMapObjectPosition("floor1_room3_bottom",		D3DXVECTOR3(-1.3493729, 8.578998, -11.287859));
	setMapObjectPosition("floor1_room3_bottom2",	D3DXVECTOR3(12.650627,  8.578998, -6.287859));
	setMapObjectPosition("floor1_room3_bottom3",	D3DXVECTOR3(28.650627,  8.578998, -1.287859));
	setMapObjectPosition("floor1_room3_bottom4",	D3DXVECTOR3(56.650627,  8.578998, -1.287859));
	setMapObjectPosition("floor1_room3_doorLoop",	D3DXVECTOR3(48.150627,  4.0789976, -1.287859));
	setMapObjectPosition("stairs1_1",				D3DXVECTOR3(-6.599373,  13.328998, 24.712141));
	setMapObjectPosition("stairs1_2",				D3DXVECTOR3(-7.099373,  13.078998, 24.712141));
	setMapObjectPosition("stairs1_3",				D3DXVECTOR3(-7.599373,  12.828998, 24.712141));
	setMapObjectPosition("stairs1_4",				D3DXVECTOR3(-8.099373,  12.578998, 24.712141));
	setMapObjectPosition("stairs1_5",				D3DXVECTOR3(-8.599373,  12.328998, 24.712141));
	setMapObjectPosition("stairs1_6",				D3DXVECTOR3(-9.099373,  12.078998, 24.712141));
	setMapObjectPosition("stairs1_7",				D3DXVECTOR3(-9.599373,  11.828998, 24.712141));
	setMapObjectPosition("stairs1_8",				D3DXVECTOR3(-10.099373, 11.578998, 24.712141));
	setMapObjectPosition("stairs1_9",				D3DXVECTOR3(-10.599373, 11.328998, 24.712141));
	setMapObjectPosition("stairs1_10",				D3DXVECTOR3(-13.349373, 11.078998, 24.712141));
	setMapObjectPosition("stairs1_11",				D3DXVECTOR3(-13.599373, 11.078998, 19.712141));
	setMapObjectPosition("stairs1_12",				D3DXVECTOR3(-11.099373, 8.328998, 19.712141));
	setMapObjectPosition("stairs1_13",				D3DXVECTOR3(-10.599373, 8.078998, 19.712141));
	setMapObjectPosition("stairs1_14",				D3DXVECTOR3(-10.099373, 7.5789976, 19.712141));
	setMapObjectPosition("stairs1_15",				D3DXVECTOR3(-9.599373,  7.0789976, 19.712141));
	setMapObjectPosition("stairs1_16",				D3DXVECTOR3(-9.099373,  6.5789976, 19.712141));
	setMapObjectPosition("stairs1_17",				D3DXVECTOR3(-8.599373,  6.0789976, 19.712141));
	setMapObjectPosition("stairs1_18",				D3DXVECTOR3(-8.099373,  5.5789976, 19.712141));
	setMapObjectPosition("stairs1_19",				D3DXVECTOR3(-7.599373,  5.0789976, 19.712141));
	setMapObjectPosition("stairs1_20",				D3DXVECTOR3(-7.099373,  4.5789976, 19.712141));
	setMapObjectPosition("stairs1_21",				D3DXVECTOR3(-6.599373,  4.0789976, 19.702));
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
