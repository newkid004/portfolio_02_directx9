#include "maptool_data_io.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "terrain.h"

void maptool_data_io::OBJ::BASE::write(json & in_Json)
{
	in_Json["baseType"] = _baseType;
	in_Json["position"] = { _position };
}

void maptool_data_io::OBJ::PROP::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	in_Json["source"] = _source.c_str();
	in_Json["effect"] = _effect.c_str();
	in_Json["scale"] = { _scale };

	in_Json["rotate"] = {
		_rotateX,
		_rotateY,
		_rotateZ };
}

void maptool_data_io::OBJ::WALL::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	in_Json["normal"] = { _normal };
}

void maptool_data_io::OBJ::FIELD::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
	in_Json["mapSize"] = { _mapSize };
	in_Json["tileSize"] = { _tileSize };
}

void maptool_data_io::OBJ::CHAR::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::apply(OBJ::BASE * in, baseObject * obj)
{
	CopyMemory(&in->_position.front(), &obj->getPosition(), sizeof(D3DXVECTOR3));
}

void maptool_data_io::apply(OBJ::PROP * in, staticMesh * obj)
{
	apply((OBJ::BASE*)in, (baseObject*)obj);

	in->_source = obj->getMakeParam().meshFilePath;
	in->_effect = obj->getMakeParam().effectFilePath;

	CopyMemory(&in->_scale.front(), &obj->getScale(), sizeof(D3DXVECTOR3));

	CopyMemory(&in->_rotateZ.front(), &obj->getDirectForward(),	sizeof(D3DXVECTOR3));
	CopyMemory(&in->_rotateY.front(), &obj->getDirectUp(),		sizeof(D3DXVECTOR3));
	CopyMemory(&in->_rotateX.front(), &obj->getDirectRight(),	sizeof(D3DXVECTOR3));
}

void maptool_data_io::apply(OBJ::CHAR * in, skinnedMesh * obj)
{
	apply((OBJ::BASE*)in, (baseObject*)obj);

	in->_source = obj->getMakeParam().filePath;
	in->_effect = obj->getMakeParam().effectFilePath;

	CopyMemory(&in->_scale.front(), &obj->getScale(), sizeof(D3DXVECTOR3));

	CopyMemory(&in->_rotateZ.front(), &obj->getDirectForward(),	sizeof(D3DXVECTOR3));
	CopyMemory(&in->_rotateY.front(), &obj->getDirectUp(),		sizeof(D3DXVECTOR3));
	CopyMemory(&in->_rotateX.front(), &obj->getDirectRight(),	sizeof(D3DXVECTOR3));
}

void maptool_data_io::apply(OBJ::FIELD * in, terrain * obj)
{
}

void maptool_data_io::create(OBJ::BASE ** out, baseObject * obj)
{
	OBJ::BASE* result = new OBJ::BASE();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::PROP ** out, staticMesh * obj)
{
	OBJ::PROP* result = new OBJ::PROP();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::CHAR ** out, skinnedMesh * obj)
{
	OBJ::CHAR* result = new OBJ::CHAR();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::FIELD ** out, terrain * obj)
{
	OBJ::FIELD* result = new OBJ::FIELD();
	apply(result, obj);
	*out = result;
}