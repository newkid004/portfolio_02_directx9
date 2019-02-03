#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

#include "maptool_data_io.h"

class terrain;
class baseObject;
class quadTree;

class maptool_field : public iUpdateble
{
public :
	struct set
	{
		std::vector<baseObject*> objList;
		std::vector< maptool_data::base*> 

		terrain* field = nullptr;
		quadTree* qTree = nullptr;

	};

private :
	set _fieldSet;

public :
	void update(void) override;
	void draw(void);

public:
	maptool_field();
	~maptool_field();
};