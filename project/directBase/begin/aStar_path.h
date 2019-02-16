#pragma once
#include "kGlobalDefine.h"

class aStar_node;
class aStar_runner;

class aStar_path
{
private:
	std::list<aStar_runner*> _path;

	float _distance = 0;

public :
	bool connect(aStar_path * connection, bool isDelete = true, bool isConnectable = false);
	bool connectAuto(aStar_path * connection, bool isDelete = true);

	void advance(void);
	bool cutTail(aStar_node* dest = nullptr);
	aStar_runner* putTail(aStar_node* dest);

protected :
	bool eraseFront(void);
	bool eraseBack(void);

private :
	float calDistance(void);

public:
	constexpr std::list<aStar_runner*> & unpack(void) { return _path; }
	constexpr float getDistance(void) { return _distance; }

public:
	aStar_path(std::list<aStar_runner*> & p);
	~aStar_path();
};