#include "maptool_io.h"

#include "maptool_field.h"

#include "gJson.h"

#include "mapObject.h"
#include "skinnedMesh.h"
#include "staticMesh.h"
#include "quadTree_Frustum.h"

constexpr char* filepath = "resource/json/maptool/";

typedef maptool_data_io IO_DATA;

maptool_io::maptool_io(maptool_field * bindData, int* bindMapIndex) :
	_bindData(bindData),
	_bindMapIndex(bindMapIndex)
{
	insertJson("object");
	insertJson("event");
	insertJson("field");
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

	for (int i = 0; i < vDataList.size(); ++i)
	{
		auto & vData = vDataList[i];
		auto & vObj = vObjList[i];

		if (vData->_baseType & IO_DATA::baseType::CHAR)
		{
			IO_DATA::apply((IO_DATA::OBJ::CHAR*)vData, (skinnedMesh*)vObj);
		}
		else if (vData->_baseType & IO_DATA::baseType::PROP)
		{
			IO_DATA::apply((IO_DATA::OBJ::PROP*)vData, (staticMesh*)vObj);
		}
		vData->write((*j)[i]);
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

void maptool_io::spreadObject(void)
{
	_bindData->getSet().selectionObject = nullptr;

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

	/*
	for (int i = 0; i < vDataList.size(); ++i)
	{
		auto & vData = vDataList[i];
		auto & vObj = vObjList[i];

		if (vData->_baseType & IO_DATA::baseType::CHAR)
		{
			IO_DATA::apply((IO_DATA::OBJ::CHAR*)vData, (skinnedMesh*)vObj);
		}
		else if (vData->_baseType & IO_DATA::baseType::PROP)
		{
			IO_DATA::apply((IO_DATA::OBJ::PROP*)vData, (staticMesh*)vObj);
		}
		vData->write((*j)[i]);
	}
	*/
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

	auto & ter = field->getTerrain();
	if (ter)	quad = new quadTree_Frustum(ter->getSizeMap().cx, ter->getSizeMap().cy);
	else		quad = new quadTree_Frustum(256, 256);

	quad->build();
}

void maptool_io::write(void)
{
	*_bindMapIndex = *_bindMapIndex < 0 ? 0 : *_bindMapIndex;

	buildObject();
	buildField();

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
		if (js.second == nullptr)
			js.second = new json;
		else
		{
			SAFE_DELETE(js.second);
			js.second = new json;

			string dirPath = "map" + to_string(*_bindMapIndex) + '/';
			gJson::read(*js.second, filepath + dirPath + js.first + ".json");
		}
	}

	spreadObject();
	spreadField();
}
