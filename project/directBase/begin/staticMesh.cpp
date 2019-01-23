#include "staticMesh.h"

#include "camera.h"
#include "direct3dApplication.h"
#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"

staticMesh::staticMesh()
{
	ZeroMemory(&_param, sizeof(_param));
}

staticMesh::staticMesh(mParam & param) :
	_param(param)
{
	_effect = MN_SRC->getEffect(param.effectFilePath);
	_info = MN_SRC->getStaticMesh(param.meshFilePath);
}


staticMesh::~staticMesh()
{
}

void staticMesh::drawDo(void)
{
	renderObject::drawDo();

	_effect->SetMatrix("_mWorld", &getMatrixFinal());
	_effect->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_effect->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());

	for (int i = 0; i < _info->numMaterial; ++i)
	{
		_effect->SetTexture("_texture", _info->vTextureList[i]);

		gFunc::runEffectLoop(_effect, "myTechnique", [&](int passNum)->void {
			_info->mesh->DrawSubset(i);
		});
	}
}
