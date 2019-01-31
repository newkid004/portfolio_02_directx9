#include "windowCtlogMaptool.h"

windowCtlogMaptool::windowCtlogMaptool(const uiInfo & info) :
	windowMvCatalog(info)
{
}

windowCtlogMaptool::~windowCtlogMaptool()
{
}

LPDIRECT3DTEXTURE9 windowCtlogMaptool::putTexture2button(int dataIndex)
{
	return _vData[dataIndex]->_standImage;
}
