#include "mapObject.h"
#include "staticMesh.h"

mapObject::mapObject()
{
}

mapObject::~mapObject()
{

}

void mapObject::init(void)
{
	mapObjectBase::init();

	//scaleMap(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
}

void mapObject::update(void)
{
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->update();
	}
}

void mapObject::draw(void)
{
	for (auto rValue : m_oMapObjectList)
	{
		rValue.second->draw();
	}
}

MAPLIST & mapObject::getMapList(void)
{
	return m_oMapObjectList;
}


