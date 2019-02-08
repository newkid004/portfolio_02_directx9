#include "labelBase.h"

#include "managerList.h"

#include "sceneBase.h"
#include "spriteBase.h"

labelBase::labelBase(const std::string & text, float size) :
	_text(text)
{
	_font = createFont(size);
}

labelBase::~labelBase()
{
	SAFE_RELEASE(_font);
}

void labelBase::drawDoUI(void)
{
	RECT rcText = { (LONG)_position.x , (LONG)_position.y, 0, 0 };

	_font->DrawTextA(
		GET_SPRITE(),
		_text.c_str(),
		-1,
		&rcText,
		_align | DT_CALCRECT,
		_diffuseColor);

	_font->DrawTextA(
		GET_SPRITE(),
		_text.c_str(),
		-1,
		&rcText,
		_align,
		_diffuseColor);

	/*
	RECT rcText = { (LONG)_position.x , (LONG)_position.y, 0, 0 };

	gFunc::runRenderTarget(_renderTarget, NULL, _depthStensil, [&](void) -> void {

		_font->DrawTextA(
			NULL,
			_text.c_str(),
			-1,
			&rcText,
			_align | DT_CALCRECT,
			_diffuseColor);

		_font->DrawTextA(
			NULL,
			_text.c_str(),
			-1,
			&rcText,
			_align,
			_diffuseColor);

	}, true, COLOR_BLACK(0));

	D3DXVECTOR2 pos = D3DXVECTOR2(rcText.left, rcText.top);
	D3DXVECTOR2 size = D3DXVECTOR2(rcText.right - rcText.left, rcText.bottom - rcText.top);
	RECT clipRect = {
		rcText.left,
		rcText.top,
		GET_WINDOW_SIZE().cx - rcText.right,
		GET_WINDOW_SIZE().cy - rcText.bottom };

	gFunc::drawSprite(
		_renderTarget,
		pos,
		size,
		D3DXVECTOR2(1.0f, 1.0f),
		1.0f,
		NULL,
		&clipRect);
	*/
}

LPD3DXFONT labelBase::createFont(float size)
{
	LPD3DXFONT result = nullptr;
	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(fontDesc));

	fontDesc.Height = size;
	fontDesc.Weight = 1000;

	D3DXCreateFontIndirect(
		MN_DEV,
		&fontDesc,
		&result);

	return result;
}