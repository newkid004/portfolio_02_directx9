#pragma once
#include "kGlobalDefine.h"
#include "aStar_grape.h"

template<typename T = void*>
class aStar_grape_bind : public aStar_grape
{
public :
	using BIND = T*;
	using BIND_LIST = std::vector<BIND*>;

protected :
	BIND_LIST _vBindList;

public:
	virtual void addNode(aStar_node* input, BIND** out_bind = nullptr);
	virtual bool deleteNode(aStar_node* input) override;
	virtual bool deleteNode(int index) override;

public :
	BIND_LIST & getBindList(void) { return _vBindList; }

public :
	BIND operator()(int index) { return _vBindList[index]; }

public:
	aStar_grape_bind() {};
	~aStar_grape_bind() {};
};

#include "aStar_grape_bind.hpp"