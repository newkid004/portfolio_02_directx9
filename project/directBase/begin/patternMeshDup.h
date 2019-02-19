#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"
#include "AnimationDef.h"

//
#include "weaponBase.h"
//

class patternMesh;

class patternMeshDup : public renderObject
{
protected:
	patternMesh * _bindPatternMesh;
	ACInfo _controlInfo;
	D3DXMATRIXA16 _finalHandMatrix[2];
	D3DXMATRIXA16 _finalNeckMatrix;

	weaponBase* _weapon;

public:
	void update(void) override;

protected:
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

private:
	void calcurateHandMatrix(void);

public:
	int &getNextBit() { return _controlInfo.NextMotionBit; }
	D3DXMATRIXA16 &getFinalNeckMatrix() { return _finalNeckMatrix; }
	const ACInfo getAControllInfo(void) { return _controlInfo; }

public:
	patternMeshDup(patternMesh* duplicateTarget);
	virtual ~patternMeshDup(void);
};