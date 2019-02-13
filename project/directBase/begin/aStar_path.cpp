#include "aStar_path.h"

#include "aStar_runner.h"

aStar_path::aStar_path(std::list<aStar_runner*>& p) :
	_path(p)
{
	sizeof(aStar_runner);
}

aStar_path::~aStar_path()
{
	for (auto i : _path)
		SAFE_DELETE(i);
}