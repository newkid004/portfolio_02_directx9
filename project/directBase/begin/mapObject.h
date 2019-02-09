#pragma once

#include "mapObjectBase.h"

class terrain;
class staticMesh;

class mapObject : public mapObjectBase
{
protected :
	terrain* _terrain = nullptr;
	staticMesh* _ceilObject = nullptr;

public:

	virtual void init(void) override;
	void update(void);
	void draw(void);

public:
	staticMesh*& getCeilObject(void);
	MAPLIST & getMapList(void);
	terrain*& getTerrain(void);

	void setDebugEnable(bool input, EDebugDrawType type = EDebugDrawType::BOX);

public:

	mapObject();
	virtual ~mapObject();

private:
};