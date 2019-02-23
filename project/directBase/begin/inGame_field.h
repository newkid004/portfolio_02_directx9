#pragma once
#include "kGlobalDefine.h"

class iUpdateble;
class iRenderable;

class baseObject;
class renderObject;
class staticMesh;
class enemyBase;
class playerableBase;
class weaponBase;

class triggerBase;
class nodeMesh;

class inGame_grape;

class mapObject;
class quadTree_Frustum;

class inGame_field
{
public :
	template<typename T>
	using vList = std::vector<T>;

public :
	struct list_set
	{
		vList<renderObject*>	vTotalObject;

		vList<iUpdateble*>		vUpdateable;
		vList<iRenderable*>		vRenderable;

		vList<staticMesh*>		vProp;
		vList<staticMesh*>		vWall;

		vList<playerableBase*>	vSurvivor;
		vList<enemyBase*>		vEnemy;
		vList<weaponBase*>		vWeapon;

		vList<triggerBase*>		vTrigger;
		vList<nodeMesh*>		vSpawnPos;
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

