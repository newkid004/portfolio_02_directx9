#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"
#include "AnimationDef.h"

class patternMesh;

class patternMeshDup : public renderObject
{
protected:
	patternMesh * _bindPatternMesh;
	ACInfo _controlInfo;

public:
	void update(void) override;

protected:
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

public:
	int &getNextBit() { return _controlInfo.NextMotionBit; }

public:
	patternMeshDup(patternMesh* duplicateTarget);
	virtual ~patternMeshDup(void);
};