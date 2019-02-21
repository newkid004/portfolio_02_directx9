#include "inGame_field.h"

#include "staticMesh.h"
#include "enemyBase.h"
#include "survivorBase.h"
#include "weaponBase.h"
#include "mapObject.h"

#include "inGame_grape.h"

inGame_field::inGame_field()
{
	_list.vSpawnPos.push_back(D3DXVECTOR3(0, 0, 20));
}

inGame_field::~inGame_field()
{
}

void inGame_field::update(void)
{
	for (auto i : _list.vUpdateable)
		i->update();
}

void inGame_field::draw(void)
{
	for (auto i : _list.vRenderable)
		i->draw();
}
