#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

using namespace std;

class animationController : public iUpdateble
{
public :
	struct playSet
	{
		bool isPlay = false;
		bool isLoop = false;

		float timeScale = 1.0f;
	};

	struct blendSet
	{
		float currentBlendTime = 0.0f;

		float timeBlend = 0.25f;
		float timeBlendElse = 1.0f;
		LPD3DXANIMATIONSET aniCurrent = nullptr;
	};

private :
	playSet _playSet;
	blendSet _blendSet;

	LPD3DXANIMATIONCONTROLLER _aniController = nullptr;

	vector<string> _vAniNameList;
	unordered_map<string, LPD3DXANIMATIONSET> _mAniSetList;

public :
	virtual void update(void) override;

public :
	void play(const string & aniName, double pos);
	void play(LPD3DXANIMATIONSET aniSet, double pos);
	void play(const string & aniName, bool isLoop);
	void play(LPD3DXANIMATIONSET aniSet, bool isLoop);

	void play(const string & aniName);
	void play(LPD3DXANIMATIONSET aniSet);

	void stop(void);

public :
	playSet & getPlaySet(void) { return _playSet; }
	blendSet & getBlendSet(void) { return _blendSet; }

	vector<string> & getAniNameList(void) { return _vAniNameList; }
	unordered_map<string, LPD3DXANIMATIONSET> & getAniSetList(void) { return _mAniSetList; }
	LPD3DXANIMATIONCONTROLLER & getAniController(void) { return _aniController; }

	void setPlayPosition(double pos) { _aniController->SetTrackPosition(0, pos); }
	vector<string> & getAnimationNameList(void) { return _vAniNameList; };

public:
	animationController(LPD3DXANIMATIONCONTROLLER aniController);
	~animationController();
};

