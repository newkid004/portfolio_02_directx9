#pragma once
#include "kGlobalDefine.h"

class maptool_field;

class maptool_io
{
private :
	maptool_field* _bindData = nullptr;
	std::unordered_map<std::string, json*> _mJson;

	int* _bindMapIndex = nullptr;

private :
	void insertJson(const std::string & jsonName);

	// write ��, field�� json���� �ۼ�
	void buildObject(void);
	void buildField(void);

	// read ��, field�� json���� �ۼ�
	void spreadObject(void);
	void spreadField(void);

public :
	void write(void);
	void read(void);

public:
	maptool_io(maptool_field* bindData, int* bindMapIndex);
	~maptool_io();
};

