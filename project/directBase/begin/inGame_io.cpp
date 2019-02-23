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

#include "triggerBase.h"

constexpr char* filepath = "resource/json/maptool/";

typedef maptool_data_io IO_DATA;


inGame_field * inGame_io::createField2File(int mapIndex)
{
	inGame_field* result = nullptr;

	SAFE_DELETE(result);
	result = new inGame_field();

	std::unordered_map<std::string, json> mJson;

	mJson.insert(decltype(mJson)::value_type("object",	json()));
	mJson.insert(decltype(mJson)::value_type("field",	json()));
	mJson.insert(decltype(mJson)::value_type("trigger",	json()));
	mJson.insert(decltype(mJson)::value_type("grape",	json()));

	for (auto & js : mJson)
	{
		string dirPath = "map" + to_string(mapIndex) + '/';
		gJson::read(js.second, filepath + dirPath + js.first + ".json");
	}

	spreadObject(result,	mJson.find("object")->second);
	spreadField(result,		mJson.find("field")->second);
	spreadTrigger(result,	mJson.find("trigger")->second);
	spreadGrape(result,		mJson.find("grape")->second);

	putObject2grape(result);

	return result;

}

void inGame_io::spreadObject(inGame_field* field, json & viewJson)
{
	auto & bindFieldList = field->getList();

	for (auto js : viewJson)
	{
		baseObject* additionObject = nullptr;
		IO_DATA::OBJ::BASE* additionData = nullptr;

		int baseType = js["baseType"];

		if (baseType & IO_DATA::baseType::TRIGGER)
			continue;	// trigger에서 처리

		else if (baseType & IO_DATA::baseType::SPAWNER)
		{
			IO_DATA::OBJ::SPAWNER* convert = new IO_DATA::OBJ::SPAWNER();
			IO_DATA::parse(convert, js);
			IO_DATA::create((nodeMesh**)&additionObject, convert);

			additionData = convert;

			bindFieldList.vSpawnPos.push_back((nodeMesh*)additionObject);
		}
		else if (baseType & IO_DATA::baseType::BUMP)
		{
			IO_DATA::OBJ::BUMP* convert = new IO_DATA::OBJ::BUMP();
			IO_DATA::parse(convert, js);
			IO_DATA::create((staticMesh**)&additionObject, convert);

			additionData = convert;

			bindFieldList.vWall.push_back((staticMesh*)additionObject);
			bindFieldList.vRenderable.push_back((staticMesh*)additionObject);
		}
		else if (baseType & IO_DATA::baseType::PROP)
		{
			IO_DATA::OBJ::PROP* convert = new IO_DATA::OBJ::PROP();
			IO_DATA::parse(convert, js);
			IO_DATA::create((staticMesh**)&additionObject, convert);

			additionData = convert;

			bindFieldList.vProp.push_back((staticMesh*)additionObject);
			bindFieldList.vRenderable.push_back((staticMesh*)additionObject);
		}

		if (additionObject && additionData)
		{
			additionObject->calMatrixFinal();
			bindFieldList.vTotalObject.push_back((staticMesh*)additionObject);
		}
	}
}

void inGame_io::spreadField(inGame_field* field, json & viewJson)
{
	auto & bindFieldList = field->getList();
	auto & bindMemberSet = field->getMember();

	IO_DATA::OBJ::FIELD data;
	IO_DATA::parse(&data, viewJson);
	IO_DATA::create(&bindMemberSet.mapObject, &data);

	for (auto i : bindMemberSet.mapObject->getMapSetList())
	{
		auto & wall = i.second;
		wall->calMatrixFinal();

		bindFieldList.vTotalObject.push_back(wall);
		bindFieldList.vRenderable.push_back(wall);
		bindFieldList.vWall.push_back(wall);
	}
}

void inGame_io::spreadTrigger(inGame_field * field, json & viewJson)
{
	auto & bindFieldList = field->getList();

	for (auto js : viewJson)
	{
		baseObject* additionObject = nullptr;
		IO_DATA::OBJ::BASE* additionData = nullptr;

		triggerBase* trigger = nullptr;

		int baseType = js["baseType"];

		if (baseType & IO_DATA::baseType::TRIGGER)
		{
			IO_DATA::OBJ::TRIGGER* convert = new IO_DATA::OBJ::TRIGGER();
			IO_DATA::parse(convert, js);
			IO_DATA::create((triggerMesh**)&additionObject, convert);

			additionData = convert;

			bindFieldList.vProp.push_back((staticMesh*)additionObject);

			// 타입에 따른 분기 필요
			trigger = additionObject->getBind<triggerBase*>();
			bindFieldList.vTrigger.push_back(trigger);
		}

		if (additionObject && additionData)
		{
			bindFieldList.vTotalObject.push_back((staticMesh*)additionObject);
			bindFieldList.vRenderable.push_back((staticMesh*)additionObject);

			bindFieldList.vUpdateable.push_back(trigger);
			bindFieldList.vRenderable.push_back(trigger);
		}
	}
}

void inGame_io::spreadGrape(inGame_field* field, json & viewJson)
{
	inGame_grape*& grape = field->getMember().grape;

	IO_DATA::OBJ::PATH data;
	IO_DATA::parse(&data, viewJson);
	IO_DATA::create(&grape, &data);
}

void inGame_io::putObject2grape(inGame_field * field)
{
	auto & grape = field->getMember().grape;
	auto & wallList = field->getList().vWall;
	auto & propList = field->getList().vProp;

	for (auto & i : wallList)
		grape->putData(i, 0, i->getPosition(), i->refBoundingSphere().radius);

	for (auto & i : propList)
		grape->putData(i, 1, i->getPosition(), i->refBoundingSphere().radius);
}
