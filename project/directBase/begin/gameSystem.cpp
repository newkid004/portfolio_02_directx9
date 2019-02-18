#include "gameSystem.h"

#include "maptool_render.h"

gameSystem::gameSystem()
{
	_set.map_render = new maptool_render();
}

gameSystem::~gameSystem()
{
	SAFE_DELETE(_set.map_render);
}

void gameSystem::update(void)
{
}
