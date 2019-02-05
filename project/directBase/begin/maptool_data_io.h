#pragma once
#include "kGlobalDefine.h"

class maptool_data
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
	struct base
	{
		int _baseType = baseType::BASE;

		std::array<float, 3> _position;
	};

	struct prop : public base
	{
		std::string _source;

		std::array<float, 3> _scale;

		std::array<float, 3> _rotateX;
		std::array<float, 3> _rotateY;
		std::array<float, 3> _rotateZ;

		prop() { _baseType |= baseType::PROP; }
	};

	struct wall : public base
	{
		std::array<float, 3> _normal;

		wall() { _baseType |= baseType::WALL; }
	};

// ----- prop ----- //
	struct field : public prop
	{
		std::array<int, 2> _mapSize;
		std::array<float, 2> _tileSize;

		field() { _baseType |= baseType::FIELD; }
	};

	struct character : public prop
	{
		character() { _baseType |= baseType::CHAR; }
	};

public :
	void write(json & in_Json, base & input);
	void write(json & in_Json, prop & input);
	void write(json & in_Json, field & input);
	void write(json & in_Json, character & input);

private:
	maptool_data() {};
	~maptool_data() {};
};

