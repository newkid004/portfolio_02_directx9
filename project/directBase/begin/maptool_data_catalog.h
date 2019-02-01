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
public :
	class OBJ
	{
	public :
		struct BASE
		{
			int _baseType = baseType::BASE;

			LPDIRECT3DTEXTURE9 _standImage = nullptr;
		};

		struct PROP : public BASE
		{

			PROP() { _baseType |= baseType::PROP; }
		};

		struct CHAR : public PROP
		{
			CHAR() { _baseType |= baseType::CHAR; }
		};

		struct EVENT : public BASE
		{
			EVENT() { _baseType |= baseType::EVENT; }
		};

		OBJ() {};
		~OBJ() {};
	};

	~maptool_data_catalog() {};
private :
	maptool_data_catalog() {};
};

