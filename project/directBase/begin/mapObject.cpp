#include "mapObject.h"

#include "terrain.h"
#include "staticMesh.h"

typedef mapObjectBase::MAPLIST MAPLIST;

mapObject::mapObject()
{
}

mapObject::~mapObject()
{
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_ceilObject);
}

void mapObject::init(void)
{
	mapObjectBase::init();

	//scaleMap(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
}

void mapObject::update(void)
{
	if (_terrain) _terrain->update();
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->update();
	}
	if (_ceilObject) _ceilObject->update();
}

void mapObject::setDebugEnable(bool input, EDebugDrawType type)
{
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->setDebugEnable(input, type);
	}
}

void mapObject::draw(void)
{
	if (_terrain) _terrain->draw();
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->draw();
	}
	if (_ceilObject) _ceilObject->draw();
}

staticMesh *& mapObject::getCeilObject(void)
{
	return _ceilObject;
}

MAPLIST & mapObject::getMapList(void)
{
	return m_oMapObjectList;
}

terrain *& mapObject::getTerrain(void)
{
	return _terrain;
}


