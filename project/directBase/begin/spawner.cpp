#include "spawner.h"

#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "camera.h"

spawner::spawner(const staticMesh::mParam & param) :
	nodeMesh(param)
{
	if (_meshSet->vTextureList.size() < 2)
		_meshSet->vTextureList.push_back(MN_SRC->getTexture("resource/texture/maptool/nodeRange2.png"));

	setScale(0.05f);
}


spawner::~spawner()
{
}

void spawner::drawDo(void)
{
	renderObject::drawDo();

	_effect->SetMatrix("_mWorld", &getMatrixFinal());
	_effect->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());
	_effect->SetVector("_diffuse", &_nodeColor);

	gFunc::runEffectLoop(_effect, "techSphere", [&](int passNum)->void {
		_meshSet->mesh->DrawSubset(0);
	});

	_effect->SetTexture("_texture", _meshSet->vTextureList[1]);
	_effect->SetMatrix("_mWorldPlane", &_mWorldPlane);
	gFunc::runEffectLoop(_effect, "techPlane", [&](int passNum)->void {
		_plane->DrawSubset(0);
	});
}
