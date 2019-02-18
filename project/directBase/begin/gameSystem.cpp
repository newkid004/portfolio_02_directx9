#include "gameSystem.h"

#include "maptool_render.h"
#include "inGame_io.h"
#include "inGame_field.h"

gameSystem::gameSystem()
{
	_set.map_render = new maptool_render();

	_set.field = inGame_io::createField2File(0);
}

gameSystem::~gameSystem()
{
	SAFE_DELETE(_set.map_render);
}

void gameSystem::update(void)
{
	_set.field->update();
}

void gameSystem::draw(void)
{
	_set.field->draw();
}
