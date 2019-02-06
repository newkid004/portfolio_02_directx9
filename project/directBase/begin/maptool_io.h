#pragma once
#include "kGlobalDefine.h"

class maptool_field;

class maptool_io
{
private :
	maptool_field* _bindData = nullptr;
	std::unordered_map<std::string, json*> _mJson;

	std::string _filename = "default";

private :
	void insertJson(const std::string & jsonName);

	// write ��, field�� objList���� �ۼ�
	void buildObject(void);

	// read ��, field�� json���� �ۼ�
	void spreadObject(void);

public :
	void write(void);
	void read(void);

public:
	maptool_io(maptool_field* bindData);
	~maptool_io();
};

