#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

#include "maptool_data_io.h"

class terrain;
class baseObject;
class renderObject;
class quadTree_Frustum;

class maptool_field : public iUpdateble
{
public :
	struct set
	{
		std::vector<baseObject*> objList;
		std::vector<maptool_data::base*> dataList;

		terrain* field = nullptr;
		quadTree_Frustum* qTree = nullptr;

		baseObject* selectionObject = nullptr;
	};

private :
	set _fieldSet;

public :
	void update(void) override;
	void draw(void);

public :
	renderObject* getPickObject(void);	// update보다 먼저 확인 필요

	constexpr set & getSet(void) { return _fieldSet; }

public:
	maptool_field(terrain* inTerrain);
	~maptool_field();
};