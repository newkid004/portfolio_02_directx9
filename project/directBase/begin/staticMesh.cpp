#include "staticMesh.h"

#include "camera.h"
#include "direct3dApplication.h"
#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "frustum.h"

staticMesh::staticMesh()
{
	ZeroMemory(&_param, sizeof(_param));
}

staticMesh::staticMesh(const mParam & param) :
	_param(param)
{
	_effect = MN_SRC->getEffect(param.effectFilePath);
	_meshSet = MN_SRC->getStaticMesh(param.meshFilePath);

	setBoundingBox(gFunc::createBoundingBox(_meshSet->mesh));
	setBoundingSphere(gFunc::createBoundingSphere(_meshSet->mesh));
}


staticMesh::~staticMesh()
{
}

bool staticMesh::cullFrustum(void)
{
	boundingSphere bound;
	this->getBoundingSphereFinal(&bound);
	return GET_FRUSTUM()->isCull(bound);
}

void staticMesh::drawDo(void)
{
	renderObject::drawDo();

	if (!_effect) return;

	_effect->SetMatrix("_mWorld", &getMatrixFinal());
	_effect->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_effect->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());
	_effect->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());

	for (int i = 0; i < _meshSet->numMaterial; ++i)
	{
		if (_meshSet->vTextureList[i])
		{
			_effect->SetTexture("_texture", _meshSet->vTextureList[i]);
		}

		gFunc::runEffectLoop(_effect, "myTechnique", [&](int passNum)->void {
			_meshSet->mesh->DrawSubset(i);
		});
	}
}
