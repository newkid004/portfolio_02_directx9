#pragma once
#include "kGlobalDefine.h"

#include "terrain.h"

class baseObject;
class staticMesh;
class skinnedMesh;
class mapObject;

class maptool_data_io
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

		BASE	= 0 << 0
	};

// ----- base ----- //
	class OBJ
	{
	public :
		struct BASE
		{
			int _baseType = baseType::BASE;

			std::array<float, 3> _position = { 0, };

			virtual void write(json & in_Json);
		};

		struct PROP : public BASE
		{
			std::string _source = "";
			std::string _effect = "";

			std::array<float, 3> _scale = { 1, };

			std::array<float, 3> _rotateZ = { 0, };
			std::array<float, 3> _rotateY = { 0, };
			std::array<float, 3> _rotateX = { 0, };

			virtual void write(json & in_Json);

			PROP() { _baseType |= baseType::PROP; }
		};

		struct WALL : public BASE
		{
			std::array<float, 3> _normal = { 0, };

			virtual void write(json & in_Json);

			WALL() { _baseType |= baseType::WALL; }
		};

		// ----- prop ----- //
		struct CHAR : public PROP
		{
			virtual void write(json & in_Json);

			CHAR() { _baseType |= baseType::CHAR; }
		};

		struct BUMP : public PROP
		{
			virtual void write(json & in_Json);

			BUMP() { _baseType |= baseType::BUMP; }
		};

		struct FIELD : public BASE
		{
			std::unordered_map<std::string, BUMP> _wall;

			PROP _ceil;
			terrain::params _terrain;

			virtual void write(json & in_Json);

		private :
			virtual void writeTerrain(json & in_Json);

		public :
			FIELD() { _baseType |= baseType::FIELD; }
		};

	private :
		OBJ() {}
		~OBJ() {}
	};

public :	// ----- parse ----- //
	static bool parse(OBJ::BASE* own, json & j_in);
	static bool parse(OBJ::PROP* own, json & j_in);
	static bool parse(OBJ::CHAR* own, json & j_in);
	static bool parse(OBJ::BUMP* own, json & j_in);
	static bool parse(OBJ::FIELD* own, json & j_in);
	static bool parse(terrain::params* own, json & j_in);

public :	// ----- apply ----- //
	static void apply(OBJ::BASE* in,	baseObject* obj);
	static void apply(OBJ::PROP* in,	staticMesh* obj);
	static void apply(OBJ::CHAR* in,	skinnedMesh* obj);
	static void apply(OBJ::BUMP* in,	staticMesh* obj);
	static void apply(OBJ::FIELD* in,	mapObject* obj);
	static void apply(OBJ::FIELD* in, terrain::params* obj);

	static void apply(baseObject* in,	OBJ::BASE* data);
	static void apply(staticMesh* in,	OBJ::PROP* data);
	static void apply(skinnedMesh* in,	OBJ::CHAR* data);
	static void apply(staticMesh* in,	OBJ::BUMP* data);
	static void apply(mapObject* in,	OBJ::FIELD* data);
	static void apply(terrain::params* in,	OBJ::FIELD* data);

public :	// ----- creater ----- //
	static void create(OBJ::BASE** out, baseObject* obj);
	static void create(OBJ::PROP** out, staticMesh* obj);
	static void create(OBJ::CHAR** out, skinnedMesh* obj);
	static void create(OBJ::BUMP** out, staticMesh* obj);
	static void create(OBJ::FIELD** out, mapObject* obj);

	static void create(staticMesh** out, OBJ::PROP* data);
	static void create(staticMesh** out, OBJ::BUMP* data);
	static void create(mapObject** out, OBJ::FIELD* data);

private:
	maptool_data_io() {};
	~maptool_data_io() {};
};

