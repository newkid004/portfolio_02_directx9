#include "maptool_data_io.h"

void maptool_data::write(json & in_Json, base & input)
{
	in_Json["baseType"] = input._baseType;
	in_Json["position"] = { input._position };
}

void maptool_data::write(json & in_Json, prop & input)
{
	write(in_Json, (base&)input);
	in_Json["source"] = input._source;
	in_Json["scale"] = input._scale;

	in_Json["rotate"] = { 
		input._rotateX, 
		input._rotateY, 
		input._rotateZ };
}

void maptool_data::write(json & in_Json, field & input)
{
	write(in_Json, (prop&)input);
	in_Json["mapSize"] = input._mapSize;
	in_Json["tileSize"] = input._tileSize;
}

void maptool_data::write(json & in_Json, character & input)
{
	write(in_Json, (prop&)input);
}
