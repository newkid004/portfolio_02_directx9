#pragma once

#include "kGlobalDefine.h"

#include "wallMesh.h"

class mapObjectBase
{
public :
	typedef unordered_map<std::string, wallMesh*> MAPLIST;
	
	struct STVertex
	{
		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
		D3DXVECTOR3 m_stBinormal;
		D3DXVECTOR3 m_stTangent;
		D3DXVECTOR2 m_stUV;
	};
protected:
	
	virtual void init(void);
	void addMapObject(std::string key, std::string meshFilePath, std::string effectFilePath, 
		string textureFilePath, string normalTextureFilePath);

	void setMeshUVOffset(string key, float offsetX, float offsetY);

	void setMapObjectScale(std::string key, const D3DXVECTOR3 & a_rstScale);
	void setMapObjectRotation(std::string key, const D3DXVECTOR3 & a_rstRotation);
	void setMapObjectPosition(std::string key, const D3DXVECTOR3 & a_rstPosition);
	
	void scaleMap(const D3DXVECTOR3 & a_rstScale);
	void rotateMap(const D3DXVECTOR3 & a_rstRotation);
	void moveMap(const D3DXVECTOR3 & a_rstMove);

public:

	mapObjectBase();
	virtual ~mapObjectBase();

protected:

	MAPLIST m_oMapObjectList;
	vector<wallMesh*> m_vMapList;
};