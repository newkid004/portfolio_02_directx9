#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

#include "maptool_data_io.h"

class mapObject;
class baseObject;
class renderObject;
class quadTree_Frustum;

class nodeMesh;

template<typename T>
class aStar_grape_bind;

class maptool_field : public iUpdateble
{
public :
	struct set
	{
	public :
		using OBJ = baseObject*;
		using DATA = maptool_data_io::OBJ::BASE*;

	public :
		std::vector<OBJ> objList;
		std::vector<DATA> dataList;
		aStar_grape_bind<nodeMesh>* pathGrape;

		mapObject* field = nullptr;
		quadTree_Frustum* qTree = nullptr;

		OBJ selectionObject = nullptr;
		DATA selectionData = nullptr;
	};

private :
	set _fieldSet;

public :
	void update(void) override;
	void draw(void);

protected :
	void updateBindGrape(void);

public :
	void getPickObject(baseObject** out_object, maptool_data_io::OBJ::BASE** out_data);	// update보다 먼저 확인 필요

	constexpr set & getSet(void) { return _fieldSet; }

public:
	maptool_field(mapObject* inTerrain);
	~maptool_field();
};