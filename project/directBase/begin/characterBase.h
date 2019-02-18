#pragma once
#include "kGlobalDefine.h"
#include "patternMeshDup.h"

#include "inGame_struct.h"

class aStar_node;

class staticMesh;
class weaponBase;
class controllerBase;

class characterBase : public patternMeshDup
{
public :
	struct heapCompare { bool operator()(aStar_node* n1, aStar_node* n2); };

protected :
	aStar_node*		_placedNode		= nullptr;	// delete : disable (aStar_grape)
	weaponBase*		_weapon			= nullptr;	// delete : disable (weaponManager)
	controllerBase*	_controller		= nullptr;	// delete : enable

	character_set	_infoCharacter;
	move_set		_infoMove;

public :
	virtual void update(void);
	virtual void drawDo(void) override;

private :
	void updateLanding(void);
	void updateMove(void);

protected :
	virtual void updateGravity(void);
	virtual void updateFriction(void);
	virtual void updateCollision(void);
	virtual void updateVelocity(void);

private :
	void createCollisionNode(std::vector<aStar_node*> * out_list);
	void moveByCollision(staticMesh* wall);

public :
	// 주체 이동 : local always
	void moveDo(D3DXVECTOR3 & direction);

	// 외적 이동 : world always
	void moveBe(D3DXVECTOR3 & direction);

public :
	aStar_node* &		getPlacedNode(void)		{ return _placedNode; }
	weaponBase* &		getWeapon(void)			{ return _weapon; }
	controllerBase* &	getController(void)		{ return _controller; }

	character_set &		getInfoCharacter(void)	{ return _infoCharacter; }
	move_set &			getInfoMove(void)		{ return _infoMove; }

	void setController(controllerBase* input);

public :
	characterBase(patternMesh* duplicateTarget);
	virtual ~characterBase();
};

