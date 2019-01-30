#include "cameraControlable.h"
#include "managerList.h"

cameraControlable::cameraControlable(float aspect, float fov, float maxDistance)
	: camera(aspect, fov, maxDistance)
{
	ZeroMemory(&_mousePrevPosition, sizeof(POINT));

	_velocity = 7.5;

	_defObject = new baseObject(); _defObject->setScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	_defVertexBuffer = createDefVertex();
};

cameraControlable::~cameraControlable()
{
	SAFE_DELETE(_defObject);
	SAFE_RELEASE(_defVertexBuffer);
}

void cameraControlable::update(void)
{
	updateControl();
	camera::update();

	_defObject->setPosition(_position);
	_defObject->rotateBillboard(true);
	_defObject->rotateZ(180.0f);
	_defObject->moveY(0.3f, false);
	_defObject->update();
}

void cameraControlable::draw(void)
{
	if (_mOffset(3, 2) != 0)
	{
		MN_DEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		MN_DEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		MN_DEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		MN_DEV->SetRenderState(D3DRS_LIGHTING, false);

		MN_DEV->SetTransform(D3DTS_WORLD, &_defObject->getMatrixWorld());

		GET_DEVICE_MANAGER()->getDevice()->SetStreamSource(0, _defVertexBuffer, 0, sizeof(vertex));

		GET_DEVICE_MANAGER()->getDevice()->SetFVF(vertex::FVF);
		GET_DEVICE_MANAGER()->getDevice()->DrawPrimitive(
			D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
			0, 1);

		MN_DEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		MN_DEV->SetRenderState(D3DRS_LIGHTING, true);
	}
}

void cameraControlable::updateControl(void)
{
	if (MN_KEY->getClickIgnore()) return;

	// view
	if (MN_KEY->mousePress(EMouseInput::RIGHT))	
		_mousePrevPosition = MN_KEY->getMousePos();

	else if (MN_KEY->mouseDown(EMouseInput::RIGHT))
	{
		// mouse
		POINT mousePos = MN_KEY->getMousePos();

		POINT mouseMove = {
			mousePos.x - _mousePrevPosition.x,
			mousePos.y - _mousePrevPosition.y };

		bool isLocal = false;
		if (MN_KEY->keyDown(DIK_SPACE)) isLocal = true;

		if (MN_KEY->mouseDown(EMouseInput::LEFT) && _isMoveable)
		{
			float moveDiv = 10.0f;

			if (MN_KEY->keyDown(DIK_LCONTROL))	moveDiv *= 5;
			if (MN_KEY->keyDown(DIK_LSHIFT))	moveDiv /= 5;

			moveX(mouseMove.x / moveDiv, !isLocal);
			moveY(-mouseMove.y / moveDiv, !isLocal);
		}
		else
		{
			rotateX(mouseMove.y / 8.0f);
			rotateY(mouseMove.x / 8.0f, false);
		}

		MN_KEY->setMousePos(_mousePrevPosition);

		// scroll
		if (MN_KEY->wheelUp())
			_mOffset(3, 2) = max(0.0f, _mOffset(3, 2) - 1);
		if (MN_KEY->wheelDown())
			_mOffset(3, 2) += 1;
		if (MN_KEY->mouseDown(EMouseInput::MIDDLE))
			_mOffset(3, 2) = 0;

		// move
		if (_isMoveable)
		{
			if (MN_KEY->keyDown(DIK_W)) moveZ(MN_TIME->getDeltaTime() * _velocity, isLocal);
			if (MN_KEY->keyDown(DIK_S)) moveZ(-MN_TIME->getDeltaTime() * _velocity, isLocal);
			if (MN_KEY->keyDown(DIK_A)) moveX(-MN_TIME->getDeltaTime() * _velocity, isLocal);
			if (MN_KEY->keyDown(DIK_D)) moveX(MN_TIME->getDeltaTime() * _velocity, isLocal);
			if (MN_KEY->keyDown(DIK_R)) moveY(MN_TIME->getDeltaTime() * _velocity, isLocal);
			if (MN_KEY->keyDown(DIK_F)) moveY(-MN_TIME->getDeltaTime() * _velocity, isLocal);
		}

		// velocity
		if (MN_KEY->keyUp(DIK_LSHIFT) || MN_KEY->keyUp(DIK_LCONTROL)) _velocity = 7.5f;
		if (MN_KEY->keyDown(DIK_LSHIFT)) _velocity += MN_TIME->getDeltaTime() * 3.0f;
		if (MN_KEY->keyDown(DIK_LCONTROL)) _velocity = 7.5f / 3.0f;
	}
}

LPDIRECT3DVERTEXBUFFER9 cameraControlable::createDefVertex(void)
{

	LPDIRECT3DVERTEXBUFFER9 result = NULL;


	MN_DEV->CreateVertexBuffer(
		sizeof(vertex) * 3,
		D3DUSAGE_WRITEONLY,
		vertex::FVF,
		D3DPOOL_MANAGED,
		&result,
		NULL);

	vertex* v;
	if (SUCCEEDED(result->Lock(0, 0, (void**)&v, 0)))
	{
		v[0].pos = D3DXVECTOR3(-1, -1, 0);
		v[1].pos = D3DXVECTOR3(0, 1, 0);
		v[2].pos = D3DXVECTOR3(1, -1, 0);

		v[0].diffuse = D3DCOLOR_XRGB(0, 255, 255);
		v[1].diffuse = D3DCOLOR_XRGB(0, 255, 255);
		v[2].diffuse = D3DCOLOR_XRGB(0, 255, 255);

		result->Unlock();
	}

	return result;
}