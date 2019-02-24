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
	virtual void update(void) override;

protected:
	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

private:
	void calcurateHandMatrix(void);
	void calcurateBoundSphereMatrix(void);

public:
	int &getNextBit() { return _controlInfo.NextMotionBit; }
	patternMesh* &getOriginMesh() { return _bindPatternMesh; }
	D3DXMATRIXA16 &getFinalNeckMatrix() { return _finalNeckMatrix; }
	D3DXMATRIXA16 &getLeftHandMatrix() { return _finalHandMatrix[0]; }
	ACInfo &getAControllInfo(void) { return _controlInfo; }

public:
	patternMeshDup(patternMesh* duplicateTarget);
	virtual ~patternMeshDup(void);
};