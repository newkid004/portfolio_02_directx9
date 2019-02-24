#include "eShootWeapon.h"

#include "managerList.h"
#include "gFunc.h"

#include "characterBase.h"

#include "particlePoint.h"
#include "particleEmitter.h"
#include "particleCreater.h"

#include "sceneBase.h"
#include "camera.h"

eShootWeapon::eShootWeapon(void* sour, unsigned long paramType) : 
	eventBase(sour, nullptr, paramType, 1.0f)
{
	auto own = static_cast<characterBase*>(m_stSour);

	_particle = createParticle(own->getPosition(), GET_CAMERA()->getDirectForward());
	_particle->particleEmitStart(0.01f);

	if (m_stParamType & EVENT::KIND::WEAPON::SHOTGUN)
	{
		_particle->setPosition(own->getPosition());
		_particle->getPosition().y += 3.3f;
		_particle->getPosition() += own->getDirectForward() * 20.0f;
		_particle->getPosition() += own->getDirectRight() * 0.2f;
	}
	else if (m_stParamType & EVENT::KIND::WEAPON::RIFLE)
	{
		_particle->setPosition(own->getPosition());
		_particle->getPosition().y += 5.3f;
		_particle->getPosition() += own->getDirectForward() * 16.0f;
		_particle->getPosition() += own->getDirectRight() * 1.1f;
	}

	own->getWeapon()->refHandPosition() = _particle->getPosition();
}

eShootWeapon::~eShootWeapon()
{
	SAFE_DELETE(_particle);
}

void eShootWeapon::update(void)
{
	eventBase::update();
	_particle->update();
}

void eShootWeapon::draw(void)
{
	_particle->getIsCull() = false;
	_particle->draw();
}

particlePoint * eShootWeapon::createParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 & normal)
{
	particleEmitter::particle makeParam;
	particlePoint::mParams param;
	param.textureFilePath = "resource/texture/effect/gunParticle.png";
	param.emitterParam.maxNumParticle = 50;
	param.emitterParam.numParticlePerSecond = 1000;
	param.emitterParam.type = EParticleType::FOUNTAIN;
	param.emitterParam.makeParam = particleCreater::makeParam(
		particleCreater::PC_FOUNTAIN::MAKE,
		(normal * 30) + D3DXVECTOR3(
			gFunc::rndFloat(-10.0f, 10.0f),
			gFunc::rndFloat(-10.0f, 10.0f),
			gFunc::rndFloat(-10.0f, 10.0f)), 
		D3DXVECTOR3(
			gFunc::rndFloat(-50.0f, 50.f),
			gFunc::rndFloat(-50.0f, 50.f),
			gFunc::rndFloat(-50.0f, 50.f)),
		3.0f,
		1.0f,
		0.3f);

	return new particlePoint(param);
}
