#include "inGame_io.h"

#include "managerList.h"
#include "gJson.h"

#include "maptool_data_io.h"
#include "inGame_field.h"

#include "skinnedMesh.h"
#include "staticMesh.h"

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

	for (auto js : *j)
	{
		baseObject* additionObject = nullptr;
		IO_DATA::OBJ::BASE* additionData = nullptr;

		int baseType = js["baseType"];

		if (baseType & IO_DATA::baseType::CHAR)
		{
			IO_DATA::OBJ::CHAR* convert = new IO_DATA::OBJ::CHAR();
			IO_DATA::parse(convert, js);

			skinnedMesh::mParam param;
			param.filePath = convert->_source;
			param.effectFilePath = convert->_effect;

			additionObject = new skinnedMesh(param);
			IO_DATA::apply((skinnedMesh*)additionObject, convert);

			additionData = convert;
		}
		else if (baseType & IO_DATA::baseType::PROP)
		{
			IO_DATA::OBJ::PROP* convert = new IO_DATA::OBJ::PROP();
			IO_DATA::parse(convert, js);
			IO_DATA::create((staticMesh**)&additionObject, convert);

			additionData = convert;
		}

		if (additionObject && additionData)
		{
			// vDataList.push_back(additionData);
			// vObjList.push_back(additionObject);
		}
	}
}

void inGame_io::spreadField(inGame_field* field)
{
}

void inGame_io::spreadGrape(inGame_field* field)
{
}
