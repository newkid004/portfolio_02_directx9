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
		_active();
}

void triggerBase::draw(void)
{
	if (_isPick)
		SGT_GAME->getSet().map_render->drawOutLine(_bindMesh);
}

bool triggerBase::pickCheck(void)
{
	pick::ray pRay;
	pick::createPickRay(&pRay, &_bindMesh->getMatrixFinal());

	if (pick::chkPick(&pRay, &_bindMesh->getBoundingSphere()))
	{
		pick::info pInfo;
		pick::chkPick(&pInfo, &pRay, _bindMesh->getMeshSet()->mesh);

		return pInfo.isHit == TRUE && pInfo.distance < 50.0f;
	}

	return false;
}