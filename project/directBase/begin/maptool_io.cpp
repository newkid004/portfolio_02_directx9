#include "maptool_io.h"

#include "maptool_field.h"

#include "gJson.h"

#include "skinnedMesh.h"
#include "staticMesh.h"

constexpr char* filepath = "resource/json/maptool/";

maptool_io::maptool_io(maptool_field * bindData) :
	_bindData(bindData)
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

	typedef maptool_data_io IO_DATA;
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

	typedef maptool_data_io IO_DATA;

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

			staticMesh::mParam param;
			param.meshFilePath = convert->_source;
			param.effectFilePath = convert->_effect;

			additionObject = new staticMesh(param);
			IO_DATA::apply((staticMesh*)additionObject, convert);

			additionData = convert;
		}

		if (additionObject && additionData)
		{
			vDataList.push_back(additionData);
			vObjList.push_back(additionObject);
		}
	}

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

void maptool_io::write(void)
{
	buildObject();

	for (auto & i : _mJson)
	{
		if (i.second)
		{
			gJson::write(*i.second, filepath + _filename + "/" + i.first + ".json");
		}
	}
}

void maptool_io::read(void)
{
	for (auto & js : _mJson)
	{
		if (js.second == nullptr)
			js.second = new json;
		else
		{
			SAFE_DELETE(js.second);
			js.second = new json;

			gJson::read(*js.second, filepath + _filename + "/" + js.first + ".json");
		}
	}

	spreadObject();
}
