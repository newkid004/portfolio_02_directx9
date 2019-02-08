#pragma once
#include "kGlobalDefine.h"

class renderObject;

class staticMesh;
class skinnedMesh;

class maptool_data_catalog
{
public :
// ----- enum ----- //
	enum baseType
	{
		BUMP	= 1 << 5,
		FILE	= 1 << 4,
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
			virtual ~BASE() {}	// ������ ���� (dynamic_cast)
		};

		struct PROP : public BASE
		{
			renderObject* _object = nullptr;

			PROP() { _baseType |= baseType::PROP; }
			~PROP();
		};

		struct CHAR : public PROP
		{
			CHAR() { _baseType |= baseType::CHAR; }
		};

		struct EVENT : public BASE
		{
			EVENT() { _baseType |= baseType::EVENT; }
		};

		struct FILE : public BASE
		{
			FILE() { _baseType |= baseType::FILE; }
		};

		struct BUMP : public PROP
		{
			BUMP() { _baseType |= baseType::BUMP; }
		};

		OBJ() {};
		~OBJ() {};
	};

public :
	static void create(OBJ::PROP** out, void * param);
	static void create(OBJ::BUMP** out, void * param);
	static void create(OBJ::CHAR** out, void * param);

public :
	static void duplicate(staticMesh** outObject, OBJ::PROP* targetObject);
	static void duplicate(staticMesh** outObject, OBJ::BUMP* targetObject);
	static void duplicate(skinnedMesh** outObject, OBJ::CHAR* targetObject);
	// static void duplicate(OBJ::EVENT** outObject, OBJ::EVENT* targetObject);

private :
	static void applyObject(renderObject* target, renderObject* own);

private :
	maptool_data_catalog() {};
	~maptool_data_catalog() {};
};
