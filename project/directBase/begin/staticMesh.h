#pragma once

#include "kGlobalDefine.h"
#include "renderObject.h"

using namespace std;

class staticMesh : public renderObject
{
public :
	struct mParam
	{
		string meshFilePath;
		string effectFilePath;
	};


private :
	LPD3DXEFFECT _effect = nullptr;
	meshSet* _meshSet = nullptr;
	mParam _param;

protected :
	virtual bool cullFrustum(void);

	virtual void drawDo(void) override;

public :
	const mParam & getMakeParam(void) { return _param; }
	meshSet* getMeshSet(void) { return _meshSet; }

public:
	staticMesh();
	staticMesh(const mParam & param);

	~staticMesh();
};

