#pragma once
#include "kGlobalDefine.h"

class renderObject;

class staticMesh;
class skinnedMesh;
class nodeMesh;

class maptool_data_catalog
{
public :
// ----- enum ----- //
	enum baseType
	{
		TRIGGER	= 1 << 6,
		BUMP	= 1 << 5,
		FILE	= 1 << 4,
		NODE	= 1 << 3,
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
			virtual ~BASE() {}	// 다형성 보장 (dynamic_cast)
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

		struct NODE : public PROP
		{
			NODE() { _baseType |= baseType::NODE; }
		};

		struct FILE : public BASE
		{
			FILE() { _baseType |= baseType::FILE; }
		};

		struct BUMP : public PROP
		{
			BUMP() { _baseType |= baseType::BUMP; }
		};

		struct TRIGGER : public PROP
		{
			TRIGGER() { _baseType |= baseType::BUMP; }
		};

		OBJ() {};
		~OBJ() {};
	};

public :
	static void create(OBJ::PROP** out, void * param);
	static void create(OBJ::BUMP** out, void * param);
	static void create(OBJ::CHAR** out, void * param);
	static void create(OBJ::NODE** out, void * param);
	static void create(OBJ::TRIGGER** out, void * param);

public :
	static void duplicate(staticMesh**	outObject, OBJ::PROP* targetObject);
	static void duplicate(staticMesh**	outObject, OBJ::BUMP* targetObject);
	static void duplicate(skinnedMesh**	outObject, OBJ::CHAR* targetObject);
	static void duplicate(nodeMesh**	outObject, OBJ::NODE* targetObject);
	static void duplicate(staticMesh**	outObject, OBJ::TRIGGER* targetObject);

private :
	static void applyObject(renderObject* target, renderObject* own);
	static void applyObject(nodeMesh* target, nodeMesh* own);

private :
	maptool_data_catalog() {};
	~maptool_data_catalog() {};
};
