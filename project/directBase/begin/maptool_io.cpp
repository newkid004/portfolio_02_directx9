#include "maptool_io.h"

#include "maptool_data_io.h"
#include "maptool_field.h"

#include "gJson.h"

#include "quadTree_Frustum.h"

#include "skinnedMesh.h"
#include "staticMesh.h"
#include "mapObject.h"
#include "nodeMesh.h"
#include "triggerMesh.h"

#include "aStar_grape_bind.h"
#include "aStar_path.h"

constexpr char* filepath = "resource/json/maptool/";

typedef maptool_data_io IO_DATA;

maptool_io::maptool_io(maptool_field * bindData, int* bindMapIndex) :
	_bindData(bindData),
	_bindMapIndex(bindMapIndex)
{
	insertJson("object");
	insertJson("trigger");
	insertJson("field");
	insertJson("grape");
}

maptool_io::~maptool_io()
{
	for (auto i : _mJson)
		SAFE_DELETE(i.second);
}

void maptool_io::insertJson(const std::string & filepath)
{
	_mJson.insert(decltype(_mJson)::value_type(filepath, nullptr));
}

void maptool_io::buildObject()
{
	auto iter = _mJson.find("object");
	json*& j = iter->second;

	SAFE_DELETE(j);
	j = new json;

	auto & vDataList = _bindData->getSet().dataList;
	auto & vObjList = _bindData->getSet().objList;

	int writeCount = -1;
	for (int i = 0; i < vDataList.size(); ++i)
	{
		auto & vData = vDataList[i];
		auto & vObj = vObjList[i];

		if (vData->_baseType & IO_DATA::baseType::NODE)
			continue;	// grape에서 따로 적용

		else if (vData->_baseType & IO_DATA::baseType::BUMP)
			IO_DATA::apply((IO_DATA::OBJ::BUMP*)vData, (staticMesh*)vObj);

		else if (vData->_baseType & IO_DATA::baseType::TRIGGER)
			continue;	// trigger에서 따로 적용

		else if (vData->_baseType & IO_DATA::baseType::CHAR)
			IO_DATA::apply((IO_DATA::OBJ::CHAR*)vData, (skinnedMesh*)vObj);

		else if (vData->_baseType & IO_DATA::baseType::PROP)
			IO_DATA::apply((IO_DATA::OBJ::PROP*)vData, (staticMesh*)vObj);

		vData->write((*j)[++writeCount]);
	}
}

void maptool_io::buildField(void)
{
	auto iter = _mJson.find("field");
	json*& j = iter->second;

	SAFE_DELETE(j);
	j = new json;

	if (mapObject* field = _bindData->getSet().field)
	{
		IO_DATA::OBJ::FIELD data;
		IO_DATA::apply(&data, field);
		data.write(*j);
	}
}

void maptool_io::buildTrigger(void)
{
	auto iter = _mJson.find("trigger");
	json*& j = iter->second;

	SAFE_DELETE(j);
	j = new json;

	auto & vDataList = _bindData->getSet().dataList;
	auto & vObjList = _bindData->getSet().objList;
	
	int writeCount = -1;
	for (int i = 0; i < vDataList.size(); ++i)
	{
		auto & vData = vDataList[i];
		auto & vObj = vObjList[i];

		if ((vData->_baseType & IO_DATA::baseType::TRIGGER) == 0)
			continue;

		if (vData->_baseType & IO_DATA::baseType::TRIGGER)
			IO_DATA::apply((IO_DATA::OBJ::TRIGGER*)vData, (triggerMesh*)vObj);

		vData->write((*j)[++writeCount]);
	}
}

void maptool_io::buildGrape(void)
{
	auto iter = _mJson.find("grape");
	json*& j = iter->second;

	SAFE_DELETE(j);
	j = new json;

	if (IO_DATA::grape* grape = _bindData->getSet().pathGrape)
	{
		IO_DATA::OBJ::PATH data;
		IO_DATA::apply(&data, grape);
		data.write(*j);
	}
}

void maptool_io::spreadObject(void)
{
	_bindData->getSet().selectionObject.clear();

	auto iter = _mJson.find("object");
	json*& j = iter->second;

	auto & vDataList = _bindData->getSet().dataList;
	auto & vObjList = _bindData->getSet().objList;

	for (int i = 0; i < vDataList.size(); ++i)
	{
		SAFE_DELETE(vObjList[i]);
		SAFE_DELETE(vDataList[i]);
	}
	vObjList.clear();
	vDataList.clear();

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
		else if (baseType & IO_DATA::baseType::TRIGGER)
			continue;	// trigger에서 처리

		else if (baseType & IO_DATA::baseType::BUMP)
		{
			IO_DATA::OBJ::BUMP* convert = new IO_DATA::OBJ::BUMP();
			IO_DATA::parse(convert, js);
			IO_DATA::create((staticMesh**)&additionObject, convert);

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
			vDataList.push_back(additionData);
			vObjList.push_back(additionObject);
		}
	}
}

void maptool_io::spreadField(void)
{
	auto iter = _mJson.find("field");
	json*& j = iter->second;

	mapObject*& field = _bindData->getSet().field;
	SAFE_DELETE(field);

	IO_DATA::OBJ::FIELD data;
	IO_DATA::parse(&data, *j);
	IO_DATA::create(&field, &data);

	quadTree_Frustum* & quad = _bindData->getSet().qTree;
	SAFE_DELETE(quad);

	quad = new quadTree_Frustum(256, 256);
	quad->build();
}

void maptool_io::spreadTrigger(void)
{
	auto iter = _mJson.find("trigger");
	json*& j = iter->second;

	auto & vDataList = _bindData->getSet().dataList;
	auto & vObjList = _bindData->getSet().objList;

	for (auto js : *j)
	{
		baseObject* additionObject = nullptr;
		IO_DATA::OBJ::BASE* additionData = nullptr;

		int baseType = js["baseType"];

		if (baseType & IO_DATA::baseType::TRIGGER)
		{
			IO_DATA::OBJ::TRIGGER* convert = new IO_DATA::OBJ::TRIGGER();
			IO_DATA::parse(convert, js);
			IO_DATA::create((triggerMesh**)&additionObject, convert);

			additionData = convert;
		}

		if (additionObject && additionData)
		{
			vDataList.push_back(additionData);
			vObjList.push_back(additionObject);
		}
	}
}

void maptool_io::spreadGrape(void)
{
	auto iter = _mJson.find("grape");
	json*& j = iter->second;

	IO_DATA::grape*& grape = _bindData->getSet().pathGrape;
	SAFE_DELETE(grape);
	SAFE_DELETE(_bindData->getSet().pathData);

	IO_DATA::OBJ::PATH data;
	IO_DATA::parse(&data, *j);
	IO_DATA::create(&grape, &data);

	auto & vDataList = _bindData->getSet().dataList;
	auto & vObjList = _bindData->getSet().objList;

	auto & bindList = grape->getBindList();

	for (int i = 0; i < bindList.size(); ++i)
	{
		vDataList.push_back(new IO_DATA::OBJ::NODE(data._node[i]));
		vObjList.push_back(bindList[i]);
	}
}

void maptool_io::write(void)
{
	*_bindMapIndex = *_bindMapIndex < 0 ? 0 : *_bindMapIndex;

	buildObject();
	buildField();
	buildTrigger();
	buildGrape();

	for (auto & i : _mJson)
	{
		if (i.second)
		{
			string dirPath = "map" + to_string(*_bindMapIndex) + '/';
			gJson::write(*i.second, filepath + dirPath + i.first + ".json");
		}
	}
}

void maptool_io::read(void)
{
	*_bindMapIndex = *_bindMapIndex < 0 ? 0 : *_bindMapIndex;

	for (auto & js : _mJson)
	{
		SAFE_DELETE(js.second);
		js.second = new json;

		string dirPath = "map" + to_string(*_bindMapIndex) + '/';
		gJson::read(*js.second, filepath + dirPath + js.first + ".json");
	}

	spreadObject();
	spreadField();
	spreadTrigger();
	spreadGrape();
}
