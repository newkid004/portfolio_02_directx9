#include "triggerBase.h"

#include "managerList.h"
#include "gFunc.h"
#include "pickRay.h"

#include "sceneBase.h"
#include "camera.h"

#include "maptool_render.h"

#include "staticMesh.h"

void triggerBase::update(void)
{
	_isPick = pickCheck();

	if (_isPick && MN_KEY->keyPress(DIK_E) && _active)
		_active(this);
}

void triggerBase::draw(void)
{
	if (_isPick)
		SGT_GAME->getSet().map_render->drawOutLine(_bindMesh);
}

bool triggerBase::pickCheck(void)
{
	pick::ray pRay;
	pick::createPickRay(&pRay);

	if (100.0f < gFunc::Vec3Distance(_bindMesh->getPosition(), pRay.origin))
		return false;

	pick::ray postRay;
	pick::applyMatrix(&postRay, &pRay, &_bindMesh->getMatrixFinal());

	if (pick::chkPick(&postRay, &_bindMesh->getBoundingSphere()))
	{
		pick::info pInfo;
		pick::chkPick(&pInfo, &postRay, _bindMesh->getMeshSet()->mesh);

		return pInfo.isHit == TRUE;
	}

	return false;
}

triggerBase::triggerBase(staticMesh * bindMesh) :
	_bindMesh(bindMesh)
{
	if (bindMesh) bindMesh->refBind() = this;
}
