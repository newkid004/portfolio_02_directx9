#include "sceneTest4.h"

#include "managerList.h"

#include "particleEmitter.h"
#include "particlePoint.h"
#include "particleQuad.h"
#include "particleCreater.h"

void sceneTest4::init(void)
{
	sceneBase::init();

	_particle = createParticle();
	_particle->setPosition(D3DXVECTOR3(0, 3, -10));
}

void sceneTest4::update(void)
{
	sceneBase::update();

	_particle->update();
	if (MN_KEY->keyDown(DIK_SPACE)) _particle->particleEmitStart(1.0f);
}

void sceneTest4::draw(void)
{
	sceneBase::draw();
	_particle->draw();
}

void sceneTest4::drawUI(void)
{
	sceneBase::drawUI();
}

particlePoint * sceneTest4::createParticle(void)
{
	particleEmitter::particle makeParam;
	particlePoint::mParams param;
	// particleQuad::mParams param;

	param.textureFilePath = "resource/texture/bonobono.png";
	param.emitterParam.maxNumParticle = 100;
	param.emitterParam.numParticlePerSecond = 20;
	param.emitterParam.type = EParticleType::FOUNTAIN;
	param.emitterParam.makeParam = particleCreater::makeParam(
		particleCreater::PC_FOUNTAIN::MAKE, 
		D3DXVECTOR3(0.5f, 0.5f, 100.0f), 
		D3DXVECTOR3(0.3f, 0.3f, 0.3f), 
		10.0f, 
		3.0f);

	return new particlePoint(param);
}
