#pragma once
#include "kGlobalDefine.h"

class gJson
{
public :
	static void write(json & in_json, const std::string & filepath);
	static void read(json & out_json, const std::string & filepath);

private :
	gJson() {};
	~gJson() {};
};