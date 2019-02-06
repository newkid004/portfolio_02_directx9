#pragma once
#include "kGlobalDefine.h"

class baseObject;
class terrain;
class staticMesh;
class skinnedMesh;

class maptool_data_io
{
public :
// ----- enum ----- //
	enum baseType
	{
		PROP	= 1 << 0,
		WALL	= 1 << 1,
		FIELD	= 1 << 2,
		CHAR	= 1 << 3,

		BASE	= 0 << 0
	};

// ----- base ----- //
	class OBJ
	{
	public :
		struct BASE
		{
			int _baseType = baseType::BASE;

			std::array<float, 3> _position;

			virtual void write(json & in_Json);
		};

		struct PROP : public BASE
		{
			std::string _source;
			std::string _effect;

			std::array<float, 3> _scale;

			std::array<float, 3> _rotateZ;
			std::array<float, 3> _rotateY;
			std::array<float, 3> _rotateX;

			virtual void write(json & in_Json);

			PROP() { _baseType |= baseType::PROP; }
		};

		struct WALL : public BASE
		{
			std::array<float, 3> _normal;

			virtual void write(json & in_Json);

			WALL() { _baseType |= baseType::WALL; }
		};

		// ----- prop ----- //
		struct FIELD : public PROP
		{
			std::array<int, 2> _mapSize;
			std::array<float, 2> _tileSize;

			virtual void write(json & in_Json);

			FIELD() { _baseType |= baseType::FIELD; }
		};

		struct CHAR : public PROP
		{
			virtual void write(json & in_Json);

			CHAR() { _baseType |= baseType::CHAR; }
		};

	private :
		OBJ() {}
		~OBJ() {}
	};

public :	// ----- parse ----- //
	static void parse(OBJ::BASE* own, json & j_in);
	static void parse(OBJ::PROP* own, json & j_in);
	static void parse(OBJ::CHAR* own, json & j_in);

public :	// ----- apply ----- //
	static void apply(OBJ::BASE* in,	baseObject* obj);
	static void apply(OBJ::PROP* in,	staticMesh* obj);
	static void apply(OBJ::CHAR* in,	skinnedMesh* obj);
	static void apply(OBJ::FIELD* in,	terrain* obj);

	static void apply(baseObject* in,	OBJ::BASE* data);
	static void apply(staticMesh* in,	OBJ::PROP* data);
	static void apply(skinnedMesh* in,	OBJ::CHAR* data);
	static void apply(terrain* in,		OBJ::FIELD* data);

public :	// ----- creater ----- //
	static void create(OBJ::BASE** out, baseObject* obj);
	static void create(OBJ::PROP** out, staticMesh* obj);
	static void create(OBJ::CHAR** out, skinnedMesh* obj);
	static void create(OBJ::FIELD** out, terrain* obj);

private:
	maptool_data_io() {};
	~maptool_data_io() {};
};

