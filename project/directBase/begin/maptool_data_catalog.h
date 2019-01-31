#pragma once
#include "kGlobalDefine.h"

class maptool_data_catalog
{
public :
// ----- enum ----- //
	enum baseType
	{
		EVENT	= 1 << 2,
		CHAR	= 1 << 1,
		PROP	= 1 << 0,
		BASE	= 0 << 0
	};

// ----- base ----- //
	struct base
	{
		int _baseType = baseType::BASE;

		LPDIRECT3DTEXTURE9 _standImage = nullptr;
	};

	struct prop : public base
	{
		prop() { _baseType |= baseType::PROP; }
	};

	struct character : public prop
	{
		character() { _baseType |= baseType::CHAR; }
	};

private:
	maptool_data_catalog() {};
	~maptool_data_catalog() {};
};

