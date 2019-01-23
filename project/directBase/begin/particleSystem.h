#pragma once
#include "kGlobalDefine.h"

#include "renderObject.h"
#include "particleEmitter.h"

using namespace std;

class particleSystem : public renderObject
{
public:
	struct mParams
	{
		string textureFilePath;
		particleEmitter::mParams emitterParam;
	};

protected:
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 _texture = nullptr;

	mParams _param;
	particleEmitter* _emitter = nullptr;

	bool _isEmitable = false;
	float _timeActive = 0.0f;

public:
	virtual void update(void) override;

	void particleEmitStart(float timeActice);
	void particleEmitStop(void);

protected:
	virtual void drawPre(void) override;
	virtual void drawPost(void) override;

public:
	void getParticleMParam(particleEmitter::particle** output);

protected:
	particleSystem(const mParams & param, LPDIRECT3DVERTEXBUFFER9 vertexBuffer);
	virtual ~particleSystem();
};

