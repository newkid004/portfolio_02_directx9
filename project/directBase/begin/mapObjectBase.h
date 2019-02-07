#pragma once

#include "kGlobalDefine.h"
#include "staticMesh.h"

typedef unordered_map<string, staticMesh*> MAPLIST;

class mapObjectBase
{
protected:
	
	virtual void init(void);
	void addMapObject(string key, string meshFilePath, string effectFilePath);

	void setMapObjectScale(string key, const D3DXVECTOR3 & a_rstScale);
	void setMapObjectRotation(string key, const D3DXVECTOR3 & a_rstRotation);
	void setMapObjectPosition(string key, const D3DXVECTOR3 & a_rstPosition);
	
	void scaleMap(const D3DXVECTOR3 & a_rstScale);
	void rotateMap(const D3DXVECTOR3 & a_rstRotation);
	void moveMap(const D3DXVECTOR3 & a_rstMove);

public:

	mapObjectBase();
	virtual ~mapObjectBase();

protected:

	MAPLIST m_oMapObjectList;
};