#pragma once
#include "kGlobalDefine.h"

class inGame_field;

class inGame_io
{
public :
	static inGame_field* createField2File(int mapIndex = 0);

private :
	// read 후, field에 json내용 작성
	static void spreadObject(inGame_field* field, json & viewJson);
	static void spreadField(inGame_field* field, json & viewJson);
	static void spreadTrigger(inGame_field* field, json & viewJson);
	static void spreadGrape(inGame_field* field, json & viewJson);

	static void putObject2grape(inGame_field* field);

private :
	inGame_io() {};
	~inGame_io() {};
};

