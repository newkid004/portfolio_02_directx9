#pragma once
#include "kGlobalDefine.h"
#include "iUpdateble.h"

class particleEmitter : public iUpdateble
{
public:
	struct particle
	{
		bool isActive;

		float timeLife;
		float timeLifeLeft;

		D3DXCOLOR color;
		D3DXCOLOR colorStart;
		D3DXCOLOR colorEnd;

		D3DXVECTOR3 normal;

		D3DXVECTOR3 rotate;
		D3DXVECTOR3 orbit;
		D3DXVECTOR3 pos;

		D3DXVECTOR3 rotateInc;
		D3DXVECTOR3 orbitInc;
		D3DXVECTOR3 posInc;

		D3DXVECTOR3 posIncInc;

		float size;
		float sizeStart;
		float sizeEnd;
	};

	struct mParams
	{
		int maxNumParticle;
		int numParticlePerSecond;

		EParticleType type;
		particle* makeParam = nullptr;
	};

private:
	mParams _param;

	std::vector<particle> _vParticleList;

	bool _isEmitenable = false;
	float _skipTime = 0.0f;

public:
	void update(void) override;

private:
	void createParticle(void);
	void updateParticle(void);
	void removeParticle(void);

public:
	std::vector<particle> & getParticleList(void) { return _vParticleList; }
	void getParam(mParams* output) { output = &_param; }

	void setEmitEnable(bool input) { _isEmitenable = input; }


public:
	particleEmitter(mParams param);
	~particleEmitter();
};

