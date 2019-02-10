#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"
#include "animationController.h"

class skinnedMesh;

class skinnedMeshDup : public renderObject
{
private :
	typedef animationController ANI;

private :
	skinnedMesh* _bindObject = nullptr;
	LPD3DXANIMATIONCONTROLLER _bindAnimation = nullptr;

	ANI::playSet _playSet;
	ANI::blendSet _blendSet;
	ANI::blendSet _blendSetPrev;

public:
	void update(void) override;

protected:
	void applyAnimation(void);

	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

private:
	void updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate);

	void drawBone(LPD3DXFRAME frame);
	void drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

public :
	void play(LPD3DXANIMATIONSET aniSet);

public:
	skinnedMesh* & getBindObject(void) { return _bindObject; }

	// animationController* getAniController(void) { return _aniController; }
	// LPD3DXMESH getMesh(void) { return _mesh; }


public:
	skinnedMeshDup(skinnedMesh* duplicateTarget);
	~skinnedMeshDup();
};

