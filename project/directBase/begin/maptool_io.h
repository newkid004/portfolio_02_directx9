#pragma once
#include "kGlobalDefine.h"

class maptool_field;

class maptool_io
{
private :
	maptool_field* _bindData = nullptr;

	std::unordered_map<std::string, json*> _mJson;

private :
	void insertJson(const std::string & jsonName);

	// write 전, field의 dataList에 objList의 내용 작성
	void buildObject(void);

public :
	void write(void);
	void read(void);

public:
	maptool_io(maptool_field* bindData);
	~maptool_io();
};

