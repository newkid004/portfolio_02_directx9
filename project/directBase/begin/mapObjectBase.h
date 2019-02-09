#pragma once

#include "kGlobalDefine.h"

#include "staticMesh.h"

class mapObjectBase
{
public :
	typedef unordered_map<std::string, staticMesh*> MAPLIST;

protected:
	
	virtual void init(void);
	void addMapObject(std::string key, std::string meshFilePath, std::string effectFilePath);

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
};