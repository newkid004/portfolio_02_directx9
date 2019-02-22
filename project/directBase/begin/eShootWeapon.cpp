#include "eShootWeapon.h"

#include "managerList.h"
#include "gFunc.h"

#include "characterBase.h"

#include "particlePoint.h"
#include "particleEmitter.h"
#include "particleCreater.h"

eShootWeapon::eShootWeapon(void* sour, unsigned long paramType) : 
	eventBase(sour, nullptr, paramType, 1.0f)
{
	auto own = static_cast<characterBase*>(m_stSour);

	_particle = createParticle(own->getPosition(), own->getDirectForward());
	_particle->particleEmitStart(0.1f);
}

eShootWeapon::~eShootWeapon()
{
	SAFE_DELETE(_particle);
}

void eShootWeapon::update(void)
{
	auto own = static_cast<characterBase*>(m_stSour);

	if (m_stParamType & EVENT::KIND::WEAPON::SHOTGUN)
	{
		_particle->setPosition(own->getPosition());
		_particle->getPosition().y += 100;
		_particle->getPosition() += own->getDirectForward() * 10;
	}
	else if (m_stParamType & EVENT::KIND::WEAPON::RIFLE)
	{
		_particle->setPosition(own->getPosition());
		_particle->getPosition().y += 100;
		_particle->getPosition() += own->getDirectForward() * 10;
	}
}

void eShootWeapon::draw(void)
{
	_particle->draw();
}

particlePoint * eShootWeapon::createParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 & normal)
{
	particleEmitter::particle makeParam;
	particlePoint::mParams param;

	param.textureFilePath = "resource/texture/effect/gunParticle.png";
	param.emitterParam.maxNumParticle = 20;
	param.emitterParam.numParticlePerSecond = 20;
	param.emitterParam.type = EParticleType::FOUNTAIN;
	param.emitterParam.makeParam = particleCreater::makeParam(
		particleCreater::PC_FOUNTAIN::MAKE,
		normal,
		D3DXVECTOR3(0.3f, 0.3f, 0.3f),
		10.0f,
		0.8f);

	param.emitterParam.makeParam->posIncInc.y -= 30.0f;

	auto result = new particlePoint(param);

	return result;
}
