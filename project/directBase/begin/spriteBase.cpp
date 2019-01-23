#include "spriteBase.h"

#include "managerList.h"
#include "direct3dApplication.h"

#include "sceneBase.h"

spriteBase::spriteBase(const string & filePath)
{
	setTexture(filePath);
}

void spriteBase::drawDoUI(void)
{
	// 행렬 설정
	D3DXMATRIXA16 mWorld;
	D3DXMatrixScaling(&mWorld, _scale.x, _scale.y, 1.0f);

	GET_SPRITE()->SetTransform(&mWorld);

	// 출력
	D3DSURFACE_DESC sDesc;
	_texture->GetLevelDesc(0, &sDesc);

	RECT rcTexture = { 0, 0, (LONG)sDesc.Width, (LONG)sDesc.Height };

	D3DXVECTOR3 pos = {
		_position.x * (1.0f / _scale.x),
		_position.y * (1.0f / _scale.y),
		_position.z };

	GET_SPRITE()->Draw(
		_texture,
		&rcTexture,
		&D3DXVECTOR3(rcTexture.right / 2.0f, rcTexture.bottom / 2.0f, 0.0f),
		&pos,
		_diffuseColor);
}

void spriteBase::setTexture(const string & filePath)
{
	_texture = MN_SRC->getSpriteTexture(filePath);
}
