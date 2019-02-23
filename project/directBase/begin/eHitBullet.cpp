#include "eHitBullet.h"
#include "eventDef.h"

#include "gDigit.h"
#include "gFunc.h"

#include "inGame_digit.h"

#include "bulletBase.h"
#include "characterBase.h"

#include "particlePoint.h"
#include "particleEmitter.h"
#include "particleCreater.h"

eHitCharacterBullet::eHitCharacterBullet(bulletBase * bullet, characterBase * take, int hitPart) :
	eventBase(bullet, take, 
		EVENT::TYPE::BULLET |
		EVENT::KIND::BULLET::COLLISION |
		EVENT::CALL::BULLET_COLLISION_TO::CHARACTER,
		0.3f)
{
	auto viewBullet = static_cast<bulletBase*>(bullet);
	auto viewTake = static_cast<characterBase*>(take);

	putDigitStatus(viewBullet, viewTake, hitPart);
	putValue(viewBullet, viewTake);

	_particle = createParticle(bullet->getIntersect(), -viewBullet->getRay().direction);
	_particle->particleEmitStart(0.01f);
}

eHitCharacterBullet::~eHitCharacterBullet()
{
	SAFE_DELETE(_particle);
}

void eHitCharacterBullet::update(void)
{
	eventBase::update();
	_particle->update();
}

void eHitCharacterBullet::draw(void)
{
	_particle->getIsCull() = false;
	_particle->draw();
}

void eHitCharacterBullet::putDigitStatus(bulletBase* bullet, characterBase * take, int hitPart)
{
	// flag on : 피격 상태
	gDigit::put(take->getInfoCharacter().status, inGame_digit::CHAR::BESHOT);

	// 타격 무기 확인
	int weaponType = bullet->getWeaponType();
	if (weaponType == weapon_set::type::rifle)
		gDigit::put(take->getStatusBeShot(), inGame_digit::PART::BYRIFLE);

	else if (weaponType == weapon_set::type::shotgun)
		gDigit::put(take->getStatusBeShot(), inGame_digit::PART::BYSHOTGUN);

	else if (
		weaponType == weapon_set::type::zombie ||
		weaponType == weapon_set::type::tank)
		gDigit::put(take->getStatusBeShot(), inGame_digit::PART::BYNORMAL);

	// 피격 부위 확인
	gDigit::put(take->getStatusBeShot(), hitPart);
}

void eHitCharacterBullet::putValue(bulletBase* bullet, characterBase * take)
{
	// 데미지 전달
	int & nowHp = take->getInfoCharacter().nowHp;
	nowHp -= bullet->getDamage();
	if (nowHp < 1)
		gDigit::put(take->getInfoCharacter().status, inGame_digit::CHAR::DEAD);

	// 행동 저지
	take->getInfoMove().currentSpeed /= 2.0f;
}

particlePoint * eHitCharacterBullet::createParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 & normal)
{
	static constexpr char* bloodParticle[5] = {
		"resource/texture/blood/blood1.png",
		"resource/texture/blood/blood2.png",
		"resource/texture/blood/blood3.png",
		"resource/texture/blood/blood4.png",
		"resource/texture/blood/blood5.png"
	};

	particleEmitter::particle makeParam;
	particlePoint::mParams param;
	param.textureFilePath = bloodParticle[gFunc::rndInt(0, 4)];
	param.emitterParam.maxNumParticle = 50;
	param.emitterParam.numParticlePerSecond = 90;
	param.emitterParam.type = EParticleType::FOUNTAIN;
	param.emitterParam.makeParam = particleCreater::makeParam(
		particleCreater::PC_FOUNTAIN::MAKE,
		normal * 10,
		D3DXVECTOR3(
			gFunc::rndFloat(-50.0f, 50.f),
			gFunc::rndFloat(-50.0f, 50.f),
			gFunc::rndFloat(-50.0f, 50.f)),
		0.5f,
		3.0f,
		0.3f);

	auto result = new particlePoint(param);
	result->setPosition(pos);

	return result;
}
