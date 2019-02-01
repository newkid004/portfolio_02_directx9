#pragma once
#include "kGlobalDefine.h"
#include "windowMvCatalog.h"

#include "maptool_data_catalog.h"

class windowCtlogMaptool : public windowMvCatalog<maptool_data_catalog::OBJ::BASE*>
{
protected :
	LPDIRECT3DTEXTURE9 putTexture2button(int dataIndex) override;

public:
	windowCtlogMaptool(const uiInfo & info);
	~windowCtlogMaptool();
};

