#include "direct3dApplication.h"
#include "renderObject.h"
#include "managerList.h"
#include "gFunc.h"
#include "camera.h"
#include "frustum.h"
#include "debugGizmo.h"
#include "debugDraw.h"

#include "sceneBase.h"

renderObject::renderObject() :
	_isVisible(true)
{
}

renderObject::~renderObject()
{
}

void renderObject::update(void)
{
	baseObject::update();

	_isCull = false;
	_isCull |= cullFrustum();

}

void renderObject::draw(void)
{
	if (_isVisible)
	{
		if (!_isCull)
		{
			drawPre();
			drawDo();
			drawPost();
		}

		for (auto child : _vChildren)
		{
			auto rObject = dynamic_cast<renderObject*>(child);

			if (rObject != nullptr)
				rObject->draw();
		}
	}
}

bool renderObject::cullFrustum(void)
{
	return GET_FRUSTUM()->isCull(_position);
}

void renderObject::getBoundingBoxFinal(boundingBox * out)
{
	// 이동
	D3DXMATRIXA16 mTranslation;
	D3DXMatrixTranslation(&mTranslation,
		_position.x,
		_position.y,
		_position.z);

	// 척도
	D3DXMATRIXA16 mScalse;
	D3DXMatrixScaling(&mScalse,
		_scale.x,
		_scale.y,
		_scale.z);

	// 회전
	D3DXMATRIXA16 mRotation;
	D3DXMatrixIdentity(&mRotation);

	CopyMemory(&mRotation(0, 0), &_directionRight, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(1, 0), &_directionUp, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(2, 0), &_directionForward, sizeof(D3DXVECTOR3));

	// world
	_mWorld = _mOffset * mScalse * mRotation * mTranslation;

	D3DXVec3TransformCoord(
		&out->min,
		&out->min,
		&_mWorld);

	D3DXVec3TransformCoord(
		&out->max,
		&out->max,
		&_mWorld);
}

void renderObject::getBoundingSphereFinal(boundingSphere * out)
{
	D3DXMATRIXA16 mWorld = getMatrixFinal();

	D3DXVec3TransformCoord(
		&out->center,
		&_bSphere.center,
		&mWorld);

	out->radius = _bSphere.radius *
		max(max(
			mWorld(0, 0),
			mWorld(1, 1)),
			mWorld(2, 2));
}

void renderObject::getObjectBox(objectBox * out)
{
	ZeroMemory(out, sizeof(objectBox));

	D3DXMATRIXA16 mWorldF = this->getMatrixFinal();
	boundingBox bound;
	this->getBoundingBoxFinal(&bound);

	// 중점
	out->center = (bound.min + bound.max) / 2.0f;

	// 축
	CopyMemory(out->direction + 0, &mWorldF(0, 0), sizeof(D3DXVECTOR3));
	CopyMemory(out->direction + 1, &mWorldF(1, 0), sizeof(D3DXVECTOR3));
	CopyMemory(out->direction + 2, &mWorldF(2, 0), sizeof(D3DXVECTOR3));

	D3DXVec3Normalize(out->direction + 0, out->direction + 0);
	D3DXVec3Normalize(out->direction + 1, out->direction + 1);
	D3DXVec3Normalize(out->direction + 2, out->direction + 2);

	// 길이
	for (int i = 0; i < 3; ++i)
	{
		auto distance = bound.max - bound.min;
		auto & wDir = out->direction[i];

		out->halfLength[i] = fabsf(D3DXVec3Dot(&distance, &wDir) / 2.0f);
	}
}

void renderObject::setDebugEnable(bool input, EDebugDrawType drawType)
{
	if (_isDebugEnable != input)
	{
		_isDebugEnable = input;

		if (!_isDebugEnable)
		{
			removeChild(_debugDraw);
			SAFE_DELETE(_debugDraw);
		}
		else
		{
			_debugDraw = new debugDraw(this, drawType);
			_debugDraw->setPosition(D3DXVECTOR3(0, 0, 0));

			addChild(_debugDraw);
		}
	}
}