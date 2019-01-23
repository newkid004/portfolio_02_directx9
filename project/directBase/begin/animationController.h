#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

using namespace std;

class animationController : public iUpdateble
{
private :
	struct blendSet
	{
		LPD3DXANIMATIONSET ani;
	};

private :
	bool _isPlay = false;
	bool _isLoop = false;

	float _currentBlendTime = 0.0f;

	float _timeBlend = 0.25f;
	float _timeScale = 0.0f;
	LPD3DXANIMATIONSET _aniCurrent = nullptr;
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
	void setPlayPosition(double pos) { _aniController->SetTrackPosition(0, pos); }
	void setTimeScale(float input) { _timeScale = input; }
	void setTimeBlend(float input) { _timeBlend = input; }
	vector<string> & getAnimationNameList(void) { return _vAniNameList; };

public:
	animationController(LPD3DXANIMATIONCONTROLLER aniController);
	~animationController();
};

