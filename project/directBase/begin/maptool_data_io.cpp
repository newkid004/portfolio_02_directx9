#include "maptool_data_io.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "terrain.h"
#include "mapObject.h"
#include "mapObjectBase.h"

void maptool_data_io::OBJ::BASE::write(json & in_Json)
{
	in_Json["baseType"] = _baseType;
	in_Json["position"] = _position;
}

void maptool_data_io::OBJ::PROP::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	in_Json["source"] = _source;
	in_Json["effect"] = _effect;
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

void maptool_data_io::OBJ::CHAR::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::OBJ::BUMP::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::OBJ::FIELD::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	
	for (auto i : _wall)
		i.second.write(in_Json["wall"][i.first]);

	_ceil.write(in_Json["ceil"]);
	writeTerrain(in_Json["terrain"]);
}

void maptool_data_io::OBJ::FIELD::writeTerrain(json & in_Json)
{
	in_Json["smoothLevel"] = _terrain.smoothLevel;
	in_Json["heightScale"] = _terrain.heightScale;

	in_Json["pathSplat"] = _terrain.pathSplat;
	in_Json["pathHeight"] = _terrain.pathHeight;
	in_Json["pathEffect"] = _terrain.pathEffect;

	in_Json["tileSize"] = { _terrain.tileSize.cx , _terrain.tileSize.cy };
	in_Json["mapSize"] = { _terrain.mapSize.cx , _terrain.mapSize.cy };

	for (int i = 0; i < _terrain.vPathTextureFile.size(); ++i)
		in_Json["texture"][i] = _terrain.vPathTextureFile[i];
}

bool maptool_data_io::parse(OBJ::BASE * own, json & j_in)
{
	if (j_in.empty()) 
		return false;

	j_in["baseType"].get_to<int>(own->_baseType);
	j_in["position"].get_to<std::array<float, 3>>(own->_position);

	return true;
}

bool maptool_data_io::parse(OBJ::PROP * own, json & j_in)
{
	if (!parse((OBJ::BASE*)own, j_in))
		return false;

	j_in["source"].get_to<std::string>(own->_source);
	j_in["effect"].get_to<std::string>(own->_effect);
	j_in["scale"].get_to<std::array<float, 3>>(own->_scale);

	j_in["rotate"][0].get_to<std::array<float, 3>>(own->_rotateX);
	j_in["rotate"][1].get_to<std::array<float, 3>>(own->_rotateY);
	j_in["rotate"][2].get_to<std::array<float, 3>>(own->_rotateZ);

	return true;
}

bool maptool_data_io::parse(OBJ::CHAR * own, json & j_in)
{
	return parse((OBJ::PROP*)own, j_in);
}

bool maptool_data_io::parse(OBJ::BUMP * own, json & j_in)
{
	return parse((OBJ::PROP*)own, j_in);
}

bool maptool_data_io::parse(OBJ::FIELD * own, json & j_in)
{
	if (!parse((OBJ::BASE*)own, j_in))
		return false;

	if (!parse((OBJ::PROP*)&own->_ceil, j_in["ceil"]))
		return false;

	if (!parse(&own->_terrain, j_in["terrain"]))
		return false;

	auto & jTarget = j_in["wall"];
	for (json::iterator i = jTarget.begin(); i != jTarget.end(); ++i)
	{ 
		OBJ::BUMP viewWall; /* = */ parse(&viewWall, i.value());
		own->_wall.insert(decltype(own->_wall)::value_type(i.key(), viewWall));
	}

	return true;
}

bool maptool_data_io::parse(terrain::params * own, json & j_in)
{
	if (j_in.empty())
		return false;

	j_in["smoothLevel"].get_to<int>(own->smoothLevel);
	j_in["heightScale"].get_to<float>(own->heightScale);

	j_in["pathSplat"].get_to<std::string>(own->pathSplat);
	j_in["pathHeight"].get_to<std::string>(own->pathHeight);
	j_in["pathEffect"].get_to<std::string>(own->pathEffect);

	j_in["tileSize"][0].get_to<LONG>(own->tileSize.cx);
	j_in["tileSize"][1].get_to<LONG>(own->tileSize.cy);
	j_in["mapSize"][0].get_to<LONG>(own->mapSize.cx);
	j_in["mapSize"][1].get_to<LONG>(own->mapSize.cy);

	for (auto i : j_in["texture"])
	{
		std::string path;
		i.get_to<std::string>(path);

		own->vPathTextureFile.push_back(path);
	}

	return true;
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

void maptool_data_io::apply(OBJ::BUMP * in, staticMesh * obj)
{
	apply((OBJ::PROP*)in, obj);
}

void maptool_data_io::apply(OBJ::FIELD * in, mapObject * obj)
{
	if (obj->getTerrain())
		in->_terrain = obj->getTerrain()->getMakeParam();

	auto & mObject = obj->getMapList();
	for (auto & subset : mObject)
	{
		auto & sName = subset.first;
		auto & sObject = subset.second;

		OBJ::BUMP viewWall;
		apply(&viewWall, sObject);
		
		in->_wall.insert(decltype(in->_wall)::value_type(sName, viewWall));
	}

	if (obj->getCeilObject())
		apply(&in->_ceil, obj->getCeilObject());
}

void maptool_data_io::apply(OBJ::FIELD * in, terrain::params * obj)
{
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

void maptool_data_io::apply(staticMesh * in, OBJ::BUMP * data)
{
	apply((staticMesh*)in, (OBJ::PROP*)data);
}

void maptool_data_io::apply(mapObject * in, OBJ::FIELD * data)
{
	apply((baseObject*)in, (OBJ::BASE*)data);
	// terrain, ceil Á¦¿Ü
	
	mapObject::MAPLIST & mObjectList = in->getMapList();

	mObjectList.reserve(data->_wall.size());
	for (auto & i : data->_wall)
	{
		staticMesh* wall = nullptr;
		create(&wall, &i.second);

		mObjectList.insert(mapObject::MAPLIST::value_type(i.first, wall));
	}
}

void maptool_data_io::apply(terrain::params * in, OBJ::FIELD * data)
{
	auto & terData = data->_terrain;
	in->smoothLevel = terData.smoothLevel;
	in->heightScale = terData.heightScale;

	in->pathSplat = terData.pathSplat;
	in->pathHeight = terData.pathHeight;
	in->pathEffect = terData.pathEffect;

	CopyMemory(&in->tileSize, &terData.tileSize, sizeof(SIZE));
	CopyMemory(&in->mapSize, &terData.mapSize, sizeof(SIZE));
	std::copy(in->vPathTextureFile.begin(), in->vPathTextureFile.end(), terData.vPathTextureFile.begin());
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

void maptool_data_io::create(OBJ::BUMP ** out, staticMesh * obj)
{
	OBJ::BUMP* result = new OBJ::BUMP();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::FIELD ** out, mapObject * obj)
{
	OBJ::FIELD* result = new OBJ::FIELD();
	apply(result, obj);
	obj->init();
	*out = result;
}

void maptool_data_io::create(staticMesh ** out, OBJ::PROP * data)
{
	staticMesh* result = nullptr;

	staticMesh::mParam param;
	param.meshFilePath = data->_source;
	param.effectFilePath = data->_effect;

	result = new staticMesh(param);
	apply((staticMesh*)result, data);

	*out = result;
}

void maptool_data_io::create(staticMesh ** out, OBJ::BUMP * data)
{
	create(out, (OBJ::PROP*)data);
}

void maptool_data_io::create(mapObject ** out, OBJ::FIELD * data)
{
	mapObject* result = new mapObject();

	// apply terrain
	terrain* ter = nullptr;
	if (data->_terrain.vPathTextureFile.size() != 0)
		ter = new terrain(data->_terrain);

	// apply ceil
	staticMesh* ceil = nullptr;
	if (!data->_ceil._source.empty() && !data->_ceil._effect.empty())
	{
		staticMesh::mParam ceilParam;
		ceilParam.meshFilePath = data->_ceil._source;
		ceilParam.effectFilePath = data->_ceil._effect;

		ceil = new staticMesh(ceilParam);

		apply(ceil, &data->_ceil);
	}

	// apply mapObject
	result->getTerrain() = ter;
	result->getCeilObject() = ceil;
	apply(result, data);

	*out = result;
}
