#pragma once
#include "kGlobalDefine.h"

class aStar_runner;

class aStar_path
{
private:
	std::list<aStar_runner*> _path;

public:
	constexpr std::list<aStar_runner*> & unpack(void) { return _path; }

public:
	aStar_path(std::list<aStar_runner*> & p);
	~aStar_path();
};