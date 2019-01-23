#include "particleSystem.h"

#include "managerList.h"

particleSystem::particleSystem(const mParams & param, LPDIRECT3DVERTEXBUFFER9 vertexBuffer) :
	_param(param),
	_vertexBuffer(vertexBuffer)
{
	_texture = MN_SRC->getTexture(param.textureFilePath);
	_emitter = new particleEmitter(param.emitterParam);
}

particleSystem::~particleSystem()
{
	SAFE_DELETE(_emitter);
	SAFE_RELEASE(_vertexBuffer);
}

void particleSystem::update(void)
{
	renderObject::update();
	_emitter->update();

	if (_isEmitable)
	{
		_timeActive -= MN_TIME->getDeltaTime();

		if (_timeActive < 0.0f)
			particleEmitStop();
	}
}

void particleSystem::particleEmitStart(float timeActive)
{
	_timeActive = timeActive;

	_isEmitable = true;
	_emitter->setEmitEnable(true);
}

void particleSystem::particleEmitStop(void)
{
	_timeActive = 0.0f;

	_isEmitable = false;
	_emitter->setEmitEnable(false);
}

void particleSystem::drawPre(void)
{
	renderObject::drawPre();

	MN_DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	MN_DEV->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	MN_DEV->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	MN_DEV->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	MN_DEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	MN_DEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	MN_DEV->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_DIFFUSE);
	MN_DEV->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
}

void particleSystem::drawPost(void)
{
	renderObject::drawPost();

	MN_DEV->SetTexture(0, NULL);

	MN_DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	MN_DEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	MN_DEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void particleSystem::getParticleMParam(particleEmitter::particle ** output)
{
	particleEmitter::mParams param;
	_emitter->getParam(&param);

	*output = param.makeParam;
}
