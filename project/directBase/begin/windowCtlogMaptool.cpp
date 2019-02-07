#include "windowCtlogMaptool.h"

windowCtlogMaptool::windowCtlogMaptool(const uiInfo & info, D3DXVECTOR2 & range) :
	windowMvCatalog(info, range)
{
}

windowCtlogMaptool::~windowCtlogMaptool()
{
}

LPDIRECT3DTEXTURE9 windowCtlogMaptool::putTexture2button(int dataIndex)
{
	return _vData[dataIndex]->_standImage;
}
