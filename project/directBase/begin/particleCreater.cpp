#include "particleCreater.h"

#include "gFunc.h"

particleCreater::cParticle* particleCreater::makeParam(PC_EXPLOSION delimiter, const D3DXVECTOR3 & speed, float sizeStart, float sizeEnd, float timeLife)
{
	cParticle* mParam = new cParticle();
	ZeroMemory(mParam, sizeof(cParticle));

	mParam->posInc = speed;
	mParam->sizeStart = sizeStart;
	mParam->sizeEnd = sizeEnd;
	mParam->timeLife = 0.0f < timeLife ? timeLife : gFunc::rndFloat(1.0f, 3.0f);

	return mParam;
}

particleCreater::cParticle* particleCreater::makeParam(PC_EXPLOSION_OUTLINE delimiter, const D3DXVECTOR3 & speed, float sizeStart, float sizeEnd, float timeLife)
{
	return makeParam(PC_EXPLOSION::MAKE, speed, sizeStart, sizeEnd, timeLife);
}

particleCreater::cParticle* particleCreater::makeParam(PC_SINK delimiter, const D3DXVECTOR3 & pos, float sizeStart, float timeLife)
{
	cParticle* mParam = new cParticle();
	ZeroMemory(mParam, sizeof(cParticle));

	mParam->pos = pos;
	mParam->sizeStart = sizeStart;
	mParam->timeLife = 0.0f < timeLife ? timeLife : gFunc::rndFloat(1.0f, 3.0f);

	return mParam;
}

particleCreater::cParticle* particleCreater::makeParam(PC_ORBIT delimiter, const D3DXVECTOR2 & orbitInc, float posZ, float sizeEnd, float timeLife)
{
	cParticle* mParam = new cParticle();
	ZeroMemory(mParam, sizeof(cParticle));

	mParam->orbitInc = D3DXVECTOR3(orbitInc.x, orbitInc.y, 0.0f);
	mParam->pos.z = posZ;
	mParam->sizeEnd = sizeEnd;
	mParam->timeLife = 0.0f < timeLife ? timeLife : gFunc::rndFloat(1.0f, 3.0f);

	return mParam;
}

particleCreater::cParticle * particleCreater::makeParam(PC_FOUNTAIN delimiter, const D3DXVECTOR3 & normal, const D3DXVECTOR3 & speed, float sizeStart, float sizeEnd, float timeLife)
{
	auto mParam = makeParam(PC_EXPLOSION::MAKE, speed, sizeStart, sizeEnd, timeLife);
	mParam->normal = normal;

	return mParam;
}

void particleCreater::toType(cParticle * input, EParticleType type, cParticle* param)
{
	ZeroMemory(input, sizeof(cParticle));

	setMakeParam(param);

	switch (type)
	{
	case EParticleType::EXPLOSION:			setExplosion(input); break;
	case EParticleType::EXPLOSION_OUTLINE:	setExplosionOutline(input); break;
	case EParticleType::SINK:				setSink(input); break;
	case EParticleType::ORBIT:				setOrbit(input); break;
	case EParticleType::FOUNTAIN:			setFountain(input); break;
	}

	input->isActive = true;

	setMakeParam(nullptr);
}

void particleCreater::setTranspose(cParticle * input)
{
	// color
	input->colorStart = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	input->colorEnd = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

void particleCreater::setTimeLife(cParticle * input)
{
	auto param = getMakeParam();

	// time
	input->timeLife = param == nullptr ? gFunc::rndFloat(1.0f, 3.0f) : param->timeLife;
	input->timeLifeLeft = input->timeLife;
}

void particleCreater::setExplosion(cParticle* input)
{
	auto param = getMakeParam();

	// def
	setTranspose(input);
	setTimeLife(input);

	// speed
	if (param == nullptr)
		input->posInc = D3DXVECTOR3(
			gFunc::rndFloat(-3.0f, 3.0f),
			gFunc::rndFloat(-3.0f, 3.0f),
			gFunc::rndFloat(-3.0f, 3.0f));
	else
		input->posInc = param->posInc;

	// size
	input->sizeStart = param == nullptr ? gFunc::rndFloat(2.0f, 4.0f) : param->sizeStart;
	input->sizeEnd = param == nullptr ? gFunc::rndFloat(4.0f, 6.0f) : param->sizeEnd;

}

void particleCreater::setExplosionOutline(cParticle * input)
{
	setExplosion(input);

	input->pos = input->posInc * 2.5f;
}

void particleCreater::setSink(cParticle * input)
{
	auto param = getMakeParam();

	// def
	setTranspose(input);
	setTimeLife(input);

	// size
	input->sizeStart = param == nullptr ? gFunc::rndFloat(1.0f, 5.0f) : param->sizeStart;
	input->sizeEnd = 0.0f;

	// pos
	input->pos = param == nullptr ?
		D3DXVECTOR3(
			gFunc::rndFloat(-50.0f, 50.0f),
			gFunc::rndFloat(-50.0f, 50.0f),
			gFunc::rndFloat(-50.0f, 50.0f)) :
		D3DXVECTOR3(
			gFunc::rndFloat(-param->pos.x, param->pos.x),
			gFunc::rndFloat(-param->pos.y, param->pos.y),
			gFunc::rndFloat(-param->pos.z, param->pos.z));

	// speed
	input->posInc = -input->pos * (1.0f / input->timeLife);
}

void particleCreater::setOrbit(cParticle * input)
{
	auto param = getMakeParam();

	// def
	setTranspose(input);
	setTimeLife(input);

	// size
	input->sizeStart = 0.0f;
	input->sizeEnd = param == nullptr ? gFunc::rndFloat(2.0f, 4.0f) : param->sizeEnd;

	// rotate
	// input->rotateInc = D3DXVECTOR3(
	// 	gFunc::rndFloat(0.0f, 360.0f),
	// 	gFunc::rndFloat(0.0f, 360.0f),
	// 	gFunc::rndFloat(0.0f, 360.0f));

	// orbit
	input->orbit = D3DXVECTOR3(
		gFunc::rndFloat(0.0f, 360.0f),
		gFunc::rndFloat(0.0f, 360.0f),
		gFunc::rndFloat(0.0f, 360.0f));

	input->orbitInc = param == nullptr ?
		D3DXVECTOR3(
			360.0f * gFunc::rndFloat(-0.2f, 0.2f),
			360.0f * gFunc::rndFloat(-0.2f, 0.2f),
			0) :
		D3DXVECTOR3(
			360.0f * gFunc::rndFloat(-param->orbitInc.x, param->orbitInc.x),
			360.0f * gFunc::rndFloat(-param->orbitInc.y, param->orbitInc.y),
			360.0f * gFunc::rndFloat(-param->orbitInc.x, param->orbitInc.z));

	// pos
	input->pos.z = param == nullptr ? 10.0f : param->pos.z;
}

void particleCreater::setFountain(cParticle * input)
{
	auto param = getMakeParam();

	// def
	setTranspose(input);
	setTimeLife(input);

	// speed
	if (param == nullptr)
	{
		input->posInc = D3DXVECTOR3(
			gFunc::rndFloat(-3.0f, 3.0f), 
			10.0f, 
			gFunc::rndFloat(-3.0f, 3.0f));
	}
	else
		input->posInc = D3DXVECTOR3(
			param->normal.x + gFunc::rndFloat(-5.0f, 5.0f),
			param->normal.y + gFunc::rndFloat(8.0f, 10.0f),
			param->normal.z + gFunc::rndFloat(-5.0f, 5.0f));

	// gravity
	if (param == nullptr)
		input->posIncInc = D3DXVECTOR3(0.0f, -30.0f, 0.0f);

	// size
	input->sizeStart = param == nullptr ? gFunc::rndFloat(2.0f, 4.0f) : param->sizeStart;
	input->sizeEnd = param == nullptr ? gFunc::rndFloat(4.0f, 6.0f) : param->sizeEnd;
}
