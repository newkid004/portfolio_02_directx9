#pragma once
#include "kGlobalDefine.h"

namespace gJson
{
	void write(json & in_json, const std::string & filepath);
	void read(json & out_json, const std::string & filepath);
};