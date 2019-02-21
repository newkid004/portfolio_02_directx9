#include "particleEmitter.h"

#include "managerList.h"
#include "gFunc.h"

#include "particleCreater.h"

particleEmitter::particleEmitter(mParams param) :
	_param(param)
{
}

particleEmitter::~particleEmitter()
{
	SAFE_DELETE(_param.makeParam);
}

void particleEmitter::update(void)
{
	if (_isEmitenable)
		createParticle();

	updateParticle();
	removeParticle();
}

void particleEmitter::createParticle(void)
{
	_skipTime += MN_TIME->getDeltaTime();

	while (1.0f / _param.numParticlePerSecond <= _skipTime)
	{
		_skipTime -= 1.0f / _param.numParticlePerSecond;

		if (_vParticleList.size() < _param.maxNumParticle)
		{
			particle p;
			particleCreater::toType(&p, _param.type, _param.makeParam);

			_vParticleList.push_back(p);
		}
	}
}

void particleEmitter::updateParticle(void)
{
	for (auto & p : _vParticleList)
	{
		p.timeLifeLeft -= MN_TIME->getDeltaTime();
		if (p.timeLifeLeft <= 0.0f)
		{
			p.isActive = false;
			continue;
		}

		p.rotate += p.rotateInc * MN_TIME->getDeltaTime();
		p.orbit += p.orbitInc * MN_TIME->getDeltaTime();
		p.pos += p.posInc * MN_TIME->getDeltaTime();

		p.posInc += p.posIncInc * MN_TIME->getDeltaTime();

		D3DXMATRIXA16 mRotate;
		D3DXMatrixRotationYawPitchRoll(
			&mRotate,
			p.rotate.y * MN_TIME->getDeltaTime(),
			p.rotate.x * MN_TIME->getDeltaTime(),
			p.rotate.z * MN_TIME->getDeltaTime());

		D3DXVec3TransformCoord(
			&p.posInc,
			&p.posInc,
			&mRotate);

		// º¸°£
		float lerpPercent = p.timeLifeLeft / p.timeLife;

		p.size = p.sizeEnd + (p.sizeStart - p.sizeEnd) * lerpPercent;
		p.color = p.colorEnd + (p.colorStart - p.colorEnd) * lerpPercent;
	}
}

void particleEmitter::removeParticle(void)
{
	for (auto iter = _vParticleList.begin(); iter != _vParticleList.end();)
	{
		if (iter->isActive)
			++iter;
		else
			iter = _vParticleList.erase(iter);
	}
}
