#include "maptool_io.h"

#include "maptool_field.h"

#include "gJson.h"

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

void maptool_io::write(void)
{
	buildObject();

	for (auto & i : _mJson)
	{
		if (i.second)
		{
			gJson::write(*i.second, filepath + i.first + ".json");
		}
	}
}

void maptool_io::read(void)
{
}
