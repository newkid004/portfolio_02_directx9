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

	// write ��, field�� dataList�� objList�� ���� �ۼ�
	void buildObject(void);

public :
	void write(void);
	void read(void);

public:
	maptool_io(maptool_field* bindData);
	~maptool_io();
};

