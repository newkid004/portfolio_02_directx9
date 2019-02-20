#include "maptool_data_io.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "wallMesh.h"
#include "terrain.h"
#include "mapObject.h"
#include "mapObjectBase.h"
#include "nodeMesh.h"
#include "triggerMesh.h"

#include "triggerBase.h"
#include "triggerFactory.h"

#include "aStar_node.h"
#include "aStar_grape_bind.h"

#include "inGame_grape.h"
#include "inGame_node.h"

using namespace std;

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
	OBJ::BUMP::write(in_Json);
	in_Json["texture"] = _texture;
	in_Json["normalTexture"] = _normalTexture;
}

void maptool_data_io::OBJ::CHAR::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::OBJ::BUMP::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
}

void maptool_data_io::OBJ::TRIGGER::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);
	in_Json["triggerType"] = _triggerType;
}

void maptool_data_io::OBJ::FIELD::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);
	
	for (auto & i : _wall)
		i.second.write(in_Json["wall"][i.first]);

	_ceil.write(in_Json["ceil"]);
}

void maptool_data_io::OBJ::NODE::write(json & in_Json)
{
	OBJ::PROP::write(in_Json);

	in_Json["radius"] = _radius;
}

void maptool_data_io::OBJ::PATH::write(json & in_Json)
{
	OBJ::BASE::write(in_Json);

	for (int i = 0; i < _node.size(); ++i)
		_node[i].write(in_Json["node"][i]);

	for (auto i : _connection)
		in_Json["connection"][i.first] = i.second;
}

bool maptool_data_io::parse(OBJ::BASE * own, json & j_in)
{
	if (j_in.empty()) 
		return false;

	j_in["baseType"].get_to<int>(own->_baseType);
	j_in["position"].get_to<array<float, 3>>(own->_position);

	return true;
}

bool maptool_data_io::parse(OBJ::PROP * own, json & j_in)
{
	if (!parse((OBJ::BASE*)own, j_in))
		return false;

	j_in["source"].get_to<string>(own->_source);
	j_in["effect"].get_to<string>(own->_effect);
	j_in["scale"].get_to<array<float, 3>>(own->_scale);

	j_in["rotate"][0].get_to<array<float, 3>>(own->_rotateX);
	j_in["rotate"][1].get_to<array<float, 3>>(own->_rotateY);
	j_in["rotate"][2].get_to<array<float, 3>>(own->_rotateZ);

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

bool maptool_data_io::parse(OBJ::TRIGGER * own, json & j_in)
{
	parse((OBJ::PROP*)own, j_in);
	j_in["triggerType"].get_to<int>(own->_triggerType);

	return true;
}

bool maptool_data_io::parse(OBJ::FIELD * own, json & j_in)
{
	if (!parse((OBJ::BASE*)own, j_in))
		return false;

	if (!parse((OBJ::PROP*)&own->_ceil, j_in["ceil"]))
		return false;

	auto & jTarget = j_in["wall"];
	for (json::iterator i = jTarget.begin(); i != jTarget.end(); ++i)
	{ 
		OBJ::WALL viewWall; /* = */ parse(&viewWall, i.value());
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

	j_in["pathSplat"].get_to<string>(own->pathSplat);
	j_in["pathHeight"].get_to<string>(own->pathHeight);
	j_in["pathEffect"].get_to<string>(own->pathEffect);

	j_in["tileSize"][0].get_to<LONG>(own->tileSize.cx);
	j_in["tileSize"][1].get_to<LONG>(own->tileSize.cy);
	j_in["mapSize"][0].get_to<LONG>(own->mapSize.cx);
	j_in["mapSize"][1].get_to<LONG>(own->mapSize.cy);

	for (auto i : j_in["texture"])
	{
		string path;
		i.get_to<string>(path);

		own->vPathTextureFile.push_back(path);
	}

	return true;
}

bool maptool_data_io::parse(OBJ::NODE * own, json & j_in)
{
	if (!parse((OBJ::PROP*)own, j_in))
		return false;

	j_in["radius"].get_to<float>(own->_radius);

	return true;
}

bool maptool_data_io::parse(OBJ::PATH * own, json & j_in)
{
	if (!parse((OBJ::BASE*)own, j_in))
		return false;

	own->_node.resize(j_in["node"].size());
	for (int i = 0; i < own->_node.size(); ++i)
		parse(&own->_node[i], j_in["node"][i]);

	auto & jTarget = j_in["connection"];
	for (int i = 0; i < jTarget.size(); ++i)
	{
		if (!jTarget[i].is_null())
			jTarget[i].get_to<vector<int>>(own->_connection[i]);
	}
	return true;
}

bool maptool_data_io::parse(OBJ::WALL * own, json & j_in)
{
	parse((OBJ::BUMP*)own, j_in);
	j_in["texture"].get_to<std::string>(own->_texture);
	j_in["normalTexture"].get_to<std::string>(own->_normalTexture);

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

void maptool_data_io::apply(OBJ::TRIGGER * in, triggerMesh * obj)
{
	apply((OBJ::PROP*)in, obj);
	in->_triggerType = obj->getBind<triggerBase*>()->refTriggerType();
}

void maptool_data_io::apply(OBJ::FIELD * in, mapObject * obj)
{
	auto & mObject = obj->getMapList();
	for (auto & subset : mObject)
	{
		auto & sName = subset.first;
		auto & sObject = subset.second;

		OBJ::WALL viewWall;
		apply(&viewWall, sObject);
		
		in->_wall.insert(decltype(in->_wall)::value_type(sName, viewWall));
	}

	if (obj->getCeilObject())
		apply(&in->_ceil, obj->getCeilObject());
}

void maptool_data_io::apply(OBJ::NODE * in, nodeMesh * obj)
{
	apply((OBJ::PROP*)in, obj);

	in->_radius = obj->getPlaneRadius();
}

void maptool_data_io::apply(OBJ::NODE * in, inGame_node * obj)
{
	apply((OBJ::BASE*)in, (baseObject*)obj);

	in->_radius = obj->getRadius();
}

void maptool_data_io::apply(OBJ::PATH * in, grape * obj)
{
	in->_node.resize(obj->getBindList().size());
	for (int i = 0 ; i < in->_node.size(); ++i)
		apply(&in->_node[i], obj->getBindList()[i]);

	for (auto i : obj->getNodeConnection())
		in->_connection[i.first] = i.second;
}

void maptool_data_io::apply(OBJ::PATH * in, inGame_grape * obj)
{
	in->_node.resize(obj->getBindList().size());
	for (int i = 0; i < in->_node.size(); ++i)
		apply(&in->_node[i], obj->getBindList()[i]);

	for (auto i : obj->getNodeConnection())
		in->_connection[i.first] = i.second;
}

void maptool_data_io::apply(OBJ::WALL * in, wallMesh * obj)
{
	apply((OBJ::BUMP*)in, (staticMesh *)obj);

	in->_texture = obj->getTexturePath();
	in->_normalTexture = obj->getNormalTexturePath();
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

	in->calMatrixFinal();
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

	in->calMatrixFinal();
}

void maptool_data_io::apply(staticMesh * in, OBJ::BUMP * data)
{
	apply((staticMesh*)in, (OBJ::PROP*)data);
}

void maptool_data_io::apply(triggerMesh * in, OBJ::TRIGGER * data)
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
		wallMesh* wall = nullptr;
		create(&wall, &i.second);

		mObjectList.insert(mapObject::MAPLIST::value_type(i.first, wall));
	}
}

void maptool_data_io::apply(nodeMesh * in, OBJ::NODE * data)
{
	apply((staticMesh*)in, (OBJ::PROP*)data);

	in->setPlaneRadius(data->_radius);
}

void maptool_data_io::apply(inGame_node * in, OBJ::NODE * data)
{
	apply((baseObject*)in, (OBJ::BASE*)data);
}

void maptool_data_io::apply(grape * in, OBJ::PATH * data)
{
	for (int i = 0; i < data->_node.size(); ++i)
	{
		nodeMesh* item = nullptr;
		create(&item, &data->_node[i]);

		aStar_node* node = new aStar_node(item->getPosition());
		grape::BIND_OUT binder = nullptr;
		in->addNode(node, binder);
		*binder = item;
		item->setBindNode(node);
	}

	for (auto & pConnection : data->_connection)
	{
		int own = pConnection.first;

		for (auto & linkingNode : pConnection.second)
			in->connectNode(own, linkingNode);
	}
}

void maptool_data_io::apply(inGame_grape * in, OBJ::PATH * data)
{
	for (int i = 0; i < data->_node.size(); ++i)
	{
		inGame_node* item = nullptr;
		create(&item, &data->_node[i]);

		aStar_node* node = new aStar_node(item->getPosition());
		inGame_grape::BIND_OUT binder = nullptr;
		in->addNode(node, binder);
		*binder = item;
		item->setBindNode(node);
	}

	for (auto & pConnection : data->_connection)
	{
		int own = pConnection.first;

		for (auto & linkingNode : pConnection.second)
			in->connectNode(own, linkingNode);
	}
}

void maptool_data_io::apply(wallMesh * in, OBJ::WALL * data)
{
	apply((staticMesh*)in, (OBJ::BUMP*)data);
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

void maptool_data_io::create(OBJ::TRIGGER ** out, triggerMesh * obj)
{
	OBJ::TRIGGER* result = new OBJ::TRIGGER();
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

void maptool_data_io::create(OBJ::NODE ** out, nodeMesh * obj)
{
	OBJ::NODE* result = new OBJ::NODE();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::NODE ** out, inGame_node * obj)
{
	OBJ::NODE* result = new OBJ::NODE();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::PATH ** out, grape * obj)
{
	OBJ::PATH* result = new OBJ::PATH();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::PATH ** out, inGame_grape * obj)
{
	OBJ::PATH* result = new OBJ::PATH();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(OBJ::WALL ** out, wallMesh * obj)
{
	OBJ::WALL* result = new OBJ::WALL();
	apply(result, obj);
	*out = result;
}

void maptool_data_io::create(staticMesh ** out, OBJ::PROP * data)
{
	staticMesh* result = nullptr;

	staticMesh::mParam param;
	param.meshFilePath = data->_source;
	param.effectFilePath = data->_effect;

	result = new staticMesh(param);
	apply(result, data);

	*out = result;
}

void maptool_data_io::create(staticMesh ** out, OBJ::BUMP * data)
{
	create(out, (OBJ::PROP*)data);
}

void maptool_data_io::create(triggerMesh ** out, OBJ::TRIGGER * data)
{
	triggerMesh* result = nullptr;

	staticMesh::mParam param;
	param.meshFilePath = data->_source;
	param.effectFilePath = data->_effect;

	result = new triggerMesh(param);
	result->refBind() = triggerFactory::createTrigger2type(data->_triggerType, result);
	apply(result, data);

	*out = result;
}

void maptool_data_io::create(mapObject ** out, OBJ::FIELD * data)
{
	mapObject* result = new mapObject();

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
	result->getCeilObject() = ceil;
	apply(result, data);

	*out = result;
}

void maptool_data_io::create(nodeMesh ** out, OBJ::NODE * data)
{
	nodeMesh* result = nullptr;

	nodeMesh::mParam param;
	param.meshFilePath = data->_source;
	param.effectFilePath = data->_effect;

	result = new nodeMesh(param);
	apply(result, data);

	*out = result;
}

void maptool_data_io::create(inGame_node ** out, OBJ::NODE * data)
{
	inGame_node* result = nullptr;

	result = new inGame_node(
		D3DXVECTOR3(
			data->_position[0], 
			data->_position[1],
			data->_position[2]), 
		data->_radius);

	*out = result;
}

void maptool_data_io::create(grape ** out, OBJ::PATH * data)
{
	grape* result = new grape();

	apply(result, data);

	*out = result;
}

void maptool_data_io::create(inGame_grape ** out, OBJ::PATH * data)
{
	inGame_grape* result = new inGame_grape();

	apply(result, data);

	*out = result;
}

void maptool_data_io::create(wallMesh ** out, OBJ::WALL * data)
{
	wallMesh::mParam param;
	param.meshFilePath = data->_source;
	param.effectFilePath = data->_effect;

	wallMesh * result = new wallMesh(param, data->_texture, data->_normalTexture);

	apply(result, data);

	*out = result;
}
