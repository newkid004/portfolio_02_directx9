#pragma once
#include "kGlobalDefine.h"

class renderObject;

class staticMesh;
class skinnedMesh;
class nodeMesh;
class triggerMesh;
class spawner;

class maptool_data_catalog
{
public :
// ----- enum ----- //
	enum baseType
	{
		PROP	= 1 << 0,
		WALL	= 1 << 1,
		CHAR	= 1 << 2,
		BUMP	= 1 << 3,
		FIELD	= 1 << 4,
		NODE	= 1 << 5,
		PATH	= 1 << 6,
		TRIGGER	= 1 << 7,
		SPAWNER = 1 << 8,
		
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

		struct BUMP : public PROP
		{
			BUMP() { _baseType |= baseType::BUMP; }
		};

		struct TRIGGER : public PROP
		{
			int _triggerType = 0;
			TRIGGER() { _baseType |= baseType::TRIGGER; }
		};

		struct SPAWNER : public NODE
		{
			SPAWNER() { _baseType |= baseType::SPAWNER; }
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
	static void create(OBJ::SPAWNER** out, void * param);

public :
	static void duplicate(staticMesh**	outObject, OBJ::PROP* targetObject);
	static void duplicate(staticMesh**	outObject, OBJ::BUMP* targetObject);
	static void duplicate(skinnedMesh**	outObject, OBJ::CHAR* targetObject);
	static void duplicate(nodeMesh**	outObject, OBJ::NODE* targetObject);
	static void duplicate(triggerMesh**	outObject, OBJ::TRIGGER* targetObject);
	static void duplicate(spawner**		outObject, OBJ::SPAWNER* targetObject);

private :
	static void applyObject(renderObject* target,	renderObject* own);
	static void applyObject(nodeMesh* target,		nodeMesh* own);
	static void applyObject(triggerMesh* target,	triggerMesh* own);
	static void applyObject(spawner* target,		spawner* own);

private :
	maptool_data_catalog() {};
	~maptool_data_catalog() {};
};
