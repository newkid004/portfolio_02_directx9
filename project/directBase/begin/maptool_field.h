#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

#include "maptool_data_io.h"

class terrain;
class baseObject;

class maptool_field : public iUpdateble
{
public :
	struct set
	{
		std::list<baseObject*> objList;
		//std::list< maptool_data::base*> 

		terrain* field = nullptr;


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