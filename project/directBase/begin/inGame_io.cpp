#include "inGame_io.h"

#include "managerList.h"
#include "gJson.h"
#include "gFunc.h"

#include "maptool_data_io.h"
#include "inGame_field.h"
#include "inGame_grape.h"
#include "inGame_node.h"

#include "quadTree_Frustum.h"

#include "skinnedMesh.h"
#include "staticMesh.h"
#include "mapObject.h"

constexpr char* filepath = "resource/json/maptool/";

typedef maptool_data_io IO_DATA;

inGame_io::inGame_io()
{
	_mJson.insert(decltype(_mJson)::value_type("object", nullptr));
	_mJson.insert(decltype(_mJson)::value_type("trigger", nullptr));
	_mJson.insert(decltype(_mJson)::value_type("field", nullptr));
	_mJson.insert(decltype(_mJson)::value_type("grape", nullptr));
}

inGame_io::~inGame_io()
{
	for (auto i : _mJson)
		SAFE_DELETE(i.second);
}


inGame_field * inGame_io::createField2File(int mapIndex)
{
	inGame_field* result = new inGame_field();

	for (auto & js : _mJson)
	{
		SAFE_DELETE(js.second);
		js.second = new json;

		string dirPath = "map" + to_string(mapIndex) + '/';
		gJson::read(*js.second, filepath + dirPath + js.first + ".json");
	}

	spreadObject(result);
	spreadField(result);
	spreadGrape(result);

	return nullptr;
}

void inGame_io::spreadObject(inGame_field* field)
{
	auto iter = _mJson.find("object");
	json*& j = iter->second;

	auto bindFieldList = field->getList();

	for (auto js : *j)
	{
		baseObject* additionObject = nullptr;
		IO_DATA::OBJ::BASE* additionData = nullptr;

		int baseType = js["baseType"];

		if (baseType & IO_DATA::baseType::BUMP)
		{
			IO_DATA::OBJ::BUMP* convert = new IO_DATA::OBJ::BUMP();
			IO_DATA::parse(convert, js);
			IO_DATA::create((staticMesh**)&additionObject, convert);

			additionData = convert;

			bindFieldList.vWall.push_back((staticMesh*)additionObject);
		}
		else if (baseType & IO_DATA::baseType::PROP)
		{
			IO_DATA::OBJ::PROP* convert = new IO_DATA::OBJ::PROP();
			IO_DATA::parse(convert, js);
			IO_DATA::create((staticMesh**)&additionObject, convert);

			additionData = convert;

			bindFieldList.vProp.push_back((staticMesh*)additionObject);
		}

		if (additionObject && additionData)
		{
			bindFieldList.vTotalObject.push_back((staticMesh*)additionObject);
			bindFieldList.vRenderable.push_back((staticMesh*)additionObject);
		}
	}
}

void inGame_io::spreadField(inGame_field* field)
{
	auto iter = _mJson.find("field");
	json*& j = iter->second;

	auto & bindFieldList = field->getList();
	auto & bindMemberSet = field->getMember();

	SAFE_DELETE(bindMemberSet.mapObject);

	IO_DATA::OBJ::FIELD data;
	IO_DATA::parse(&data, *j);
	IO_DATA::create(&bindMemberSet.mapObject, &data);

	for (auto i : bindMemberSet.mapObject->getMapList())
	{
		auto & wall = i.second;
		bindFieldList.vTotalObject.push_back(wall);
		bindFieldList.vRenderable.push_back(wall);
		bindFieldList.vWall.push_back(wall);
	}
}

void inGame_io::spreadTrigger(inGame_field * field)
{
}

void inGame_io::spreadGrape(inGame_field* field)
{
	auto iter = _mJson.find("grape");
	json*& j = iter->second;

	auto & bindFieldList = field->getList();
	auto & bindMemberSet = field->getMember();

	inGame_grape*& grape = bindMemberSet.grape;
	SAFE_DELETE(grape);

	IO_DATA::OBJ::PATH data;
	IO_DATA::parse(&data, *j);
	IO_DATA::create(&grape, &data);
}

void inGame_io::putObject2grape(inGame_field * field)
{
	auto & grape = field->getMember().grape;
	auto & wallList = field->getList().vWall;
	auto & propList = field->getList().vWall;

	for (auto & node : grape->getNodeList())
	{
		auto data = (inGame_node*)node->getBindData();
		
		for (auto & obj : wallList)
		{
			boundingSphere viewSphere;
			obj->getBoundingSphereFinal(&viewSphere);

			float distance = gFunc::Vec2Distance(
				D3DXVECTOR2(data->getPosition().x, data->getPosition().z),
				D3DXVECTOR2(viewSphere.center.x, viewSphere.center.z));

			if (distance < data->getRadius() + viewSphere.radius)
				data->getListSet().wall.push_back(obj);
		}

		for (auto & obj : propList)
		{
			boundingSphere viewSphere;
			obj->getBoundingSphereFinal(&viewSphere);

			float distance = gFunc::Vec2Distance(
				D3DXVECTOR2(data->getPosition().x, data->getPosition().z),
				D3DXVECTOR2(viewSphere.center.x, viewSphere.center.z));

			if (distance < data->getRadius() + viewSphere.radius)
				data->getListSet().prop.push_back(obj);
		}
	}
}
