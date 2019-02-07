#pragma once

#include "mapObjectBase.h"

class mapObject : mapObjectBase
{
public:

	virtual void init(void) override;
	void update(void);
	void draw(void);

public:

	MAPLIST & getMapList(void);

public:

	mapObject();
	virtual ~mapObject();

private:
};