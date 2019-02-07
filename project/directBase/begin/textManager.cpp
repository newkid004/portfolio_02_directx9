#include "textManager.h"

#include "managerList.h"
#include "gFunc.h"
#include "gMng.h"

textManager::textManager()
{
	_renderTarget = gFunc::createRenderTarget();
	_depthStensil = gFunc::createDepthStensil();
}

textManager::~textManager()
{
	for (auto & i : _mText)
		SAFE_RELEASE(i.second);

	SAFE_RELEASE(_renderTarget);
	SAFE_RELEASE(_depthStensil);
}

void textManager::draw(std::string & text, D3DXVECTOR2 & pos)
{
	// auto result = add(text);
	// 
	// D3DXMATRIXA16 mWorld;
	// D3DXMatrixTranslation(&mWorld, pos.x, pos.y, 1.0f);
	// 
	// MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);
	// 
	// MN_DEV->SetRenderState(D3DRS_ZENABLE, true);
	// MN_DEV->SetRenderState(D3DRS_LIGHTING, false);
	// 
	// result->DrawSubset(0);
	// 
	// MN_DEV->SetRenderState(D3DRS_ZENABLE, false);
	// MN_DEV->SetRenderState(D3DRS_LIGHTING, true);
}

LPD3DXMESH textManager::add(std::string & text)
{
	LPD3DXMESH result = nullptr;
	if (gMng::findif(text, _mText, (std::function<void(LPD3DXMESH)>)[&](LPD3DXMESH found)->void { result = found; }))
		return result;

	HDC hdc = CreateCompatibleDC(NULL);

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWeight = 500;
	lf.lfCharSet = DEFAULT_CHARSET;
	strcpy(lf.lfFaceName, TEXT("¸¼Àº°íµñ"));

	HFONT hFont = CreateFontIndirect(&lf);
	HFONT oFont = (HFONT)SelectObject(hdc, hFont);

	HRESULT r = D3DXCreateText(
		MN_DEV,
		hdc,
		text.c_str(),
		0.001f,
		0.4f,
		&result,
		NULL,
		NULL);

	SelectObject(hdc, oFont);
	DeleteObject(hFont);
	DeleteDC(hdc);

	return result;
}
