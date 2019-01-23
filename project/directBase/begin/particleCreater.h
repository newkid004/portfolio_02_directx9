#pragma once
#include "kGlobalDefine.h"
#include "particleEmitter.h"

class particleCreater
{
public:
	typedef particleEmitter::particle cParticle;

	enum class PC_EXPLOSION { MAKE };
	enum class PC_EXPLOSION_OUTLINE { MAKE };
	enum class PC_SINK { MAKE };
	enum class PC_ORBIT { MAKE };

public:
	static cParticle* makeParam(PC_EXPLOSION delimiter, const D3DXVECTOR3 & speed, float sizeStart, float sizeEnd, float timeLife = 3.0f);
	static cParticle* makeParam(PC_EXPLOSION_OUTLINE delimiter, const D3DXVECTOR3 & speed, float sizeStart, float sizeEnd, float timeLife = 3.0f);
	static cParticle* makeParam(PC_SINK delimiter, const D3DXVECTOR3 & pos, float sizeStart, float timeLife = 3.0f);
	static cParticle* makeParam(PC_ORBIT delimiter, const D3DXVECTOR2 & orbitInc, float posZ, float sizeEnd, float timeLife = 3.0f);

public:
	static void toType(cParticle * input, EParticleType type, cParticle* param = nullptr);

private:	// color
	static void setTranspose(cParticle * input);
	static void setTimeLife(cParticle* input);

private:	// act
	static void setExplosion(cParticle * input);
	static void setExplosionOutline(cParticle * input);
	static void setSink(cParticle * input);
	static void setOrbit(cParticle * input);

private:
	static cParticle*& getMakeParam(void) { static cParticle* makeParam = nullptr; return makeParam; }
	static void setMakeParam(cParticle* input) { getMakeParam() = input; }

private:
	particleCreater() {};
	~particleCreater() {};
};

