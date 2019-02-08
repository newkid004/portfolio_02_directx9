#include "maptool_data_io.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "terrain.h"

void maptool_data_io::OBJ::BASE::write(json & in_Json)
{
	in_Json["baseType"] = _baseType;
	in_Json["position"] = _position;
}

void maptool_data_io::OBJ::PROP::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	in_Json["source"] = _source.c_str();
	in_Json["effect"] = _effect.c_str();
	in_Json["scale"] = _scale;

	in_Json["rotate"] = {
		_rotateX,
		_rotateY,
		_rotateZ };
}

void maptool_data_io::OBJ::WALL::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	in_Json["normal"] = _normal;
}

void maptool_data_io::OBJ::FIELD::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
	in_Json["mapSize"] = _mapSize;
	in_Json["tileSize"] = _tileSize;

	in_Json["wallSource"] = _wallSource;
	in_Json["wallEffect"] = _wallEffect;

	in_Json["ceilSource"] = _ceilSource;
	in_Json["ceilEffect"] = _ceilEffect;
}

void maptool_data_io::OBJ::CHAR::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::OBJ::BUMP::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::parse(OBJ::BASE * own, json & j_in)
{
	j_in["baseType"].get_to<int>(own->_baseType);
	j_in["position"].get_to<std::array<float, 3>>(own->_position);
}

void maptool_data_io::parse(OBJ::PROP * own, json & j_in)
{
	parse((OBJ::BASE*)own, j_in);

	j_in["source"].get_to<std::string>(own->_source);
	j_in["effect"].get_to<std::string>(own->_effect);
	j_in["scale"].get_to<std::array<float, 3>>(own->_scale);

	j_in["rotate"][0].get_to<std::array<float, 3>>(own->_rotateX);
	j_in["rotate"][1].get_to<std::array<float, 3>>(own->_rotateY);
	j_in["rotate"][2].get_to<std::array<float, 3>>(own->_rotateZ);
}

void maptool_data_io::parse(OBJ::CHAR * own, json & j_in)
{
	parse((OBJ::PROP*)own, j_in);
}

void maptool_data_io::parse(OBJ::FIELD * own, json & j_in)
{
	parse((OBJ::PROP*)own, j_in);

	j_in["mapSize"].get_to<std::array<int, 2>>(own->_mapSize);
	j_in["tileSize"].get_to<std::array<float, 2>>(own->_tileSize);

	j_in["wallSource"].get_to<std::string>(own->_wallSource);
	j_in["wallEffect"].get_to<std::string>(own->_wallEffect);

	j_in["ceilSource"].get_to<std::string>(own->_ceilSource);
	j_in["ceilEffect"].get_to<std::string>(own->_ceilEffect);
}

void maptool_data_io::parse(OBJ::BUMP * own, json & j_in)
{
	parse((OBJ::PROP*)own, j_in);
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

void maptool_data_io::apply(OBJ::BUMP * in, staticMesh * obj)
{
	apply((OBJ::PROP*)in, obj);
}

void maptool_data_io::apply(baseObject * in, OBJ::BASE * data)
{
	CopyMemory(&in->getPosition(), &data->_position.front(), sizeof(D3DXVECTOR3));
}

void maptool_data_io::apply(staticMesh * in, OBJ::PROP * data)
{
	apply((baseObject*)in, (OBJ::BASE*)data);

	in->getMakeParam().meshFilePath = data->_source;
	in->getMakeParam().effectFilePath = data->_effect;

	CopyMemory(&in->getScale(), &data->_scale.front(), sizeof(D3DXVECTOR3));

	CopyMemory(&in->getDirectForward(),	&data->_rotateZ.front(), sizeof(D3DXVECTOR3));
	CopyMemory(&in->getDirectUp(),		&data->_rotateY.front(), sizeof(D3DXVECTOR3));
	CopyMemory(&in->getDirectRight(),	&data->_rotateX.front(), sizeof(D3DXVECTOR3));
}

void maptool_data_io::apply(skinnedMesh * in, OBJ::CHAR * data)
{
	apply((baseObject*)in, (OBJ::BASE*)data);

	in->getMakeParam().filePath = data->_source;
	in->getMakeParam().effectFilePath = data->_effect;

	CopyMemory(&in->getScale(), &data->_scale.front(), sizeof(D3DXVECTOR3));

	CopyMemory(&in->getDirectForward(), &data->_rotateZ.front(), sizeof(D3DXVECTOR3));
	CopyMemory(&in->getDirectUp(), &data->_rotateY.front(), sizeof(D3DXVECTOR3));
	CopyMemory(&in->getDirectRight(), &data->_rotateX.front(), sizeof(D3DXVECTOR3));
}

void maptool_data_io::apply(terrain * in, OBJ::FIELD * data)
{
}

void maptool_data_io::apply(staticMesh * in, OBJ::BUMP * data)
{
	apply((staticMesh*)in, (OBJ::PROP*)data);
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

void maptool_data_io::create(OBJ::BUMP ** out, staticMesh * obj)
{
	OBJ::BUMP* result = new OBJ::BUMP();
	apply(result, obj);
	*out = result;
}
