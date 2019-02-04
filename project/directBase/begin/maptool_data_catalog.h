#pragma once
#include "kGlobalDefine.h"

class renderObject;

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
			renderObject* _object;

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

public :
	static void duplicate(OBJ::BASE** outObject, OBJ::BASE* targetObject);
	static void duplicate(OBJ::PROP** outObject, OBJ::PROP* targetObject);
	static void duplicate(OBJ::CHAR** outObject, OBJ::CHAR* targetObject);
	static void duplicate(OBJ::EVENT** outObject, OBJ::EVENT* targetObject);

	~maptool_data_catalog() {};
private :
	maptool_data_catalog() {};
};
