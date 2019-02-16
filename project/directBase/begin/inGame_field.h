#pragma once
#include "kGlobalDefine.h"

class baseObject;
class renderObject;
class staticMesh;
class enemyBase;
class playerableBase;
class weaponBase;
class mapObject;

class triggerBase;

class inGame_grape;

class inGame_field
{
public :
	template<typename T>
	using vList = std::vector<T>;

public :
	struct list_set
	{
		vList<renderObject*>	vTotalObject;

		vList<baseObject*>		vUpdateable;
		vList<renderObject*>	vRenderable;

		vList<staticMesh*>		vProp;
		vList<staticMesh*>		vWall;

		vList<playerableBase*>	vSurvivor;
		vList<enemyBase*>		vEnemy;
		vList<weaponBase*>		vWeapon;
		vList<triggerBase*>		vTrigger;
	};

	struct member_set
	{
		inGame_grape*	grape = nullptr;
		mapObject*		mapObject = nullptr;
	};

private :
	list_set _list;
	member_set _member;

public :
	void update(void);
	void draw(void);

public :
	list_set & getList(void)		{ return _list; }
	member_set & getMember(void)	{ return _member; }

public:
	inGame_field();
	~inGame_field();
};

