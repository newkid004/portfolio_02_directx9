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
	std::string effectFilePath = "resource/effect/wall.fx";
	
	// FLOOR LAST
	addMapObject("floor3TopWall", "resource/mesh/L4D1/map/floorLast/floor3TopWall.x", effectFilePath, "resource/texture/map/drainage_brickwall.tga",
		"resource/texture/map/drainage_brickwall_normal.png");
	addMapObject("floor3LeftWall", "resource/mesh/L4D1/map/floorLast/floor3LeftWall.x", effectFilePath, "resource/texture/map/drainage_brickwall.tga",
		"resource/texture/map/drainage_brickwall_normal.png");
	addMapObject("floor3RightWall", "resource/mesh/L4D1/map/floorLast/floor3RightWall.x", effectFilePath, "resource/texture/map/drainage_brickwall.tga",
		"resource/texture/map/drainage_brickwall_normal.png");
	addMapObject("floor3BottomWall", "resource/mesh/L4D1/map/floorLast/floor3BottomWall.x", effectFilePath, "resource/texture/map/drainage_brickwall.tga",
		"resource/texture/map/drainage_brickwall_normal.png");

	addMapObject("floor3Wall_1", "resource/mesh/L4D1/map/floorLast/floor3Wall_1.x", effectFilePath, "resource/texture/map/urban_brickwall_03a.tga",
		"resource/texture/map/urban_brickwall_03a_normal.png");
	addMapObject("floor3Wall_2", "resource/mesh/L4D1/map/floorLast/floor3Wall_2.x", effectFilePath, "resource/texture/map/urban_brickwall_03a.tga",
		"resource/texture/map/urban_brickwall_03a_normal.png");
	addMapObject("floor3Wall_3", "resource/mesh/L4D1/map/floorLast/floor3Wall_3.x", effectFilePath, "resource/texture/map/urban_brickwall_03a.tga",
		"resource/texture/map/urban_brickwall_03a_normal.png");
	addMapObject("floor3Stairs", "resource/mesh/L4D1/map/floorLast/floor3Stairs.x", effectFilePath, "resource/texture/map/drainage_brickwall_02b.tga",
		"resource/texture/map/drainage_brickwall_02b_normal.png");
	addMapObject("floor3GateWall", "resource/mesh/L4D1/map/floorLast/floor3GateWall.x", effectFilePath, "resource/texture/map/drainage_brickwall_02b.tga",
		"resource/texture/map/drainage_brickwall_02b_normal.png");

	//addMapObject("building", "resource/mesh/L4D1/map/building.x", effectFilePath, "resource/texture/map/drainage_brickwall_02b.tga",
	//	"resource/texture/map/drainage_brickwall_02b.tga");

	//scaleMap(D3DXVECTOR3(0.0254f, 0.0254f, 0.0254f));
	scaleMap(D3DXVECTOR3(0.0508f, 0.0508f, 0.0508f));
	setMapObjectRotation("floor3Stairs", D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	setMapObjectRotation("floor3GateWall", D3DXVECTOR3(0.0f, 180.0f, 0.0f));

	setMapObjectPosition("floor3TopWall", D3DXVECTOR3(40.0f, 5, 59.5f) * 2);
	setMapObjectPosition("floor3LeftWall", D3DXVECTOR3(-59.5f, 5, -40.0f) * 2);
	setMapObjectPosition("floor3RightWall", D3DXVECTOR3(59.5f, 5, -0.5f) * 2);
	setMapObjectPosition("floor3BottomWall", D3DXVECTOR3(0.0f, 5, -59.5f) * 2);

	setMapObjectPosition("floor3Wall_1", D3DXVECTOR3(36.5, 4, 4) * 2);
	setMapObjectPosition("floor3Wall_2", D3DXVECTOR3(39.26, 4, -15.01) * 2);
	setMapObjectPosition("floor3Wall_3", D3DXVECTOR3(39.26, 4, 23.01) * 2);
	setMapObjectPosition("floor3Stairs", D3DXVECTOR3(5, -2.5, -37.25) * 2);
	setMapObjectPosition("floor3GateWall", D3DXVECTOR3(5, 5, -36) * 2);

	//setMapObjectPosition("building", D3DXVECTOR3(0.3, -129.6, 0) * 2);

	//"resource/texture/map/drainage_brickwall.tga", 
	//"resource/texture/map/drainage_brickwall_height_ssbump.tga",


	setMeshUVOffset("floor3TopWall", 2, 1.0f);
	setMeshUVOffset("floor3LeftWall", 2, 1.0f);
	setMeshUVOffset("floor3RightWall", 8, 1.0f);
	setMeshUVOffset("floor3BottomWall", 8, 1.0f);
	setMeshUVOffset("floor3Wall_1", 4, 1.0f);

	// FLOOR 1
	//addMapObject("floor1TopWall",	 "resource/mesh/L4D1/map/wall/floor1TopWall.x", effectFilePath);
	//addMapObject("floor1LeftWall",	 "resource/mesh/L4D1/map/wall/floor1LeftWall.x", effectFilePath);
	//addMapObject("floor1RightWall",	 "resource/mesh/L4D1/map/wall/floor1RightWall.x", effectFilePath);
	//addMapObject("floor1BottomWall",  "resource/mesh/L4D1/map/wall/floor1BottomWall.x", effectFilePath);
	//
	//addMapObject("floor1_room1_top", "resource/mesh/L4D1/map/wall/floor1_room1_top.x", effectFilePath);
	//addMapObject("floor1_room1_right", "resource/mesh/L4D1/map/wall/floor1_room1_right.x", effectFilePath);
	//addMapObject("floor1_room1_right2", "resource/mesh/L4D1/map/wall/floor1_room1_right2.x", effectFilePath);
	//addMapObject("floor1_room1_doorLoop", "resource/mesh/L4D1/map/wall/floor1_room1_doorLoop.x", effectFilePath);
	//addMapObject("floor1_room2_bottom", "resource/mesh/L4D1/map/wall/floor1_room2_bottom.x", effectFilePath);
	//addMapObject("floor1_room2_bottom2", "resource/mesh/L4D1/map/wall/floor1_room2_bottom2.x", effectFilePath);
	//addMapObject("floor1_room2_top", "resource/mesh/L4D1/map/wall/floor1_room2_top.x", effectFilePath);
	//addMapObject("floor1_room2_doorLoop", "resource/mesh/L4D1/map/wall/floor1_room2_doorLoop.x", effectFilePath);
	//addMapObject("floor1_room2_left", "resource/mesh/L4D1/map/wall/floor1_room2_left.x", effectFilePath);
	//addMapObject("floor1_room3_bottom", "resource/mesh/L4D1/map/wall/floor1_room3_bottom.x", effectFilePath);
	//addMapObject("floor1_room3_bottom2", "resource/mesh/L4D1/map/wall/floor1_room3_bottom2.x", effectFilePath);
	//addMapObject("floor1_room3_bottom3", "resource/mesh/L4D1/map/wall/floor1_room3_bottom3.x", effectFilePath);
	//addMapObject("floor1_room3_bottom4", "resource/mesh/L4D1/map/wall/floor1_room3_bottom4.x", effectFilePath);
	//addMapObject("floor1_room3_doorLoop", "resource/mesh/L4D1/map/wall/floor1_room3_doorLoop.x", effectFilePath);
	//
	//addMapObject("stairs1", "resource/mesh/L4D1/map/wall/stairs1.x", effectFilePath);
	//addMapObject("stairWall", "resource/mesh/L4D1/map/wall/stairWall.x", effectFilePath);
	

	//setMapObjectRotation("stairs1", D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	//setMapObjectRotation("stairWall", D3DXVECTOR3(0.0f, 180.0f, 0.0f));

	//setMapObjectPosition("floor1TopWall",			D3DXVECTOR3(0.0f,	5, 59.5f));
	//setMapObjectPosition("floor1LeftWall",			D3DXVECTOR3(-59.5f,	5, 0.0f));
	//setMapObjectPosition("floor1RightWall",			D3DXVECTOR3(59.5f,	5, -0.5f));
	//setMapObjectPosition("floor1BottomWall",		D3DXVECTOR3(-5, 5,	-59.5f));
	//setMapObjectPosition("floor1_room1_top",		D3DXVECTOR3(-34.5, 5, -10.5));
	//setMapObjectPosition("floor1_room1_right",		D3DXVECTOR3(-10.5, 5, -16.5));
	//setMapObjectPosition("floor1_room1_right2",		D3DXVECTOR3(-10.5, 5, -44.5));
	//setMapObjectPosition("floor1_room1_doorLoop",	D3DXVECTOR3(-10.5, 9.5, -26));
	//setMapObjectPosition("floor1_room2_bottom",		D3DXVECTOR3(54, 5, -49.5));
	//setMapObjectPosition("floor1_room2_bottom2",	D3DXVECTOR3(25.5, 5, -49.5));
	//setMapObjectPosition("floor1_room2_top",		D3DXVECTOR3(34.5, 5, -0.5));
	//setMapObjectPosition("floor1_room2_doorLoop",	D3DXVECTOR3(45, 9.5, -49.5));
	//setMapObjectPosition("floor1_room2_left",		D3DXVECTOR3(9.5, 5, -25));
	//setMapObjectPosition("floor1_room3_bottom",		D3DXVECTOR3(-34.5, 5, 0.5));
	//setMapObjectPosition("floor1_room3_bottom2",	D3DXVECTOR3(-10.5, 5, 5.5));
	//setMapObjectPosition("floor1_room3_bottom3",	D3DXVECTOR3(14.5, 5, 10.5));
	//setMapObjectPosition("floor1_room3_bottom4",	D3DXVECTOR3(53.5, 5, 10.5));
	//setMapObjectPosition("floor1_room3_doorLoop",	D3DXVECTOR3(44, 9.5, 10.5));
	//
	//setMapObjectPosition("stairs1",	D3DXVECTOR3(-54.5, 5, 54));
	//setMapObjectPosition("stairWall",D3DXVECTOR3(-54.5, 7.5, 49));
}

void mapObjectBase::addMapObject(string key, string meshFilePath, string effectFilePath, 
	string textureFilePath, string normalTextureFilePath)
{
	staticMesh::mParam stParameters;
	stParameters.meshFilePath = meshFilePath;
	stParameters.effectFilePath = effectFilePath;

	wallMesh* wall = new wallMesh(stParameters, textureFilePath, normalTextureFilePath);
	m_oMapObjectList.insert(MAPLIST::value_type(key, wall));
	m_vMapList.push_back(wall);
}

void mapObjectBase::setMeshUVOffset(string key, float offsetX, float offsetY)
{
	LPD3DXMESH & pMesh = m_oMapObjectList.find(key)->second->getMeshSet()->mesh;

	STVertex * pVertices = nullptr;

	if (SUCCEEDED(pMesh->LockVertexBuffer(NULL, (void **)&pVertices)))
	{
		for (int i = 0; i < 24; i++)
		{
			if (pVertices[i].m_stUV.x > 0.99 && pVertices[i].m_stUV.x < 1.01)
			{
				pVertices[i].m_stUV.x = offsetX;
			}

			if (pVertices[i].m_stUV.y > 0.99 && pVertices[i].m_stUV.y < 1.01)
			{
				pVertices[i].m_stUV.y = offsetY;
			}
		}

		pMesh->UnlockVertexBuffer();
	}
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
