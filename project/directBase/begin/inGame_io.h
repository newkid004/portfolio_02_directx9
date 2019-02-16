#pragma once
#include "kGlobalDefine.h"

class inGame_field;

class inGame_io
{
private :
	std::unordered_map<std::string, json*> _mJson;

public :
	inGame_field* createField2File(int mapIndex = 0);

private :
	// read 후, field에 json내용 작성
	void spreadObject(inGame_field* field);
	void spreadField(inGame_field* field);
	void spreadGrape(inGame_field* field);

public:
	inGame_io();
	~inGame_io();
};

