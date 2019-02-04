#pragma once
#include "kGlobalDefine.h"

class renderObject;

class maptool_data_catalog
{
public :
// ----- enum ----- //
	enum baseType
	{
		EVENT	= 1 << 3,
		CHAR	= 1 << 2,
		PROP	= 1 << 1,
		BASE	= 1 << 0,
		
		NONE	= 0
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
			renderObject* _object = nullptr;

			PROP() { _baseType |= baseType::PROP; }
			~PROP() { SAFE_DELETE(_object); }
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
