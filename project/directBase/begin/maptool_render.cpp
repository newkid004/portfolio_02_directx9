#include "maptool_render.h"

#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "camera.h"
#include "lightBase.h"

#include "staticMesh.h"
#include "skinnedMesh.h"

static D3DXVECTOR4 defColor = D3DXVECTOR4(0.5f, 0.5f, 1.0f, 1.0f);

maptool_render::maptool_render()
{
	for (int i = 0; i < 3; ++i)
	{
		renderSet rt;
		createRenderSet(&rt);
		_vRenderTarget.push_back(rt);
	}
	createScreen(&_screen);

	_outline = MN_SRC->getEffect("resource/effect/outlineBlur.fx");
}

maptool_render::~maptool_render()
{
	for (auto & i : _vRenderTarget)
	{
		SAFE_RELEASE(i.renderTarget);
		SAFE_RELEASE(i.depthStensil);
	}
}

void maptool_render::createRenderSet(renderSet * out)
{
	MN_DEV->CreateTexture(
		GET_WINDOW_SIZE().cx,
		GET_WINDOW_SIZE().cy,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT,
		&out->renderTarget,
		NULL);

	MN_DEV->CreateDepthStencilSurface(
		GET_WINDOW_SIZE().cx,
		GET_WINDOW_SIZE().cy,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&out->depthStensil,
		NULL);
}

void maptool_render::createScreen(LPD3DXMESH * out)
{
	LPD3DXMESH result = nullptr;

	D3DXCreateMeshFVF(
		2, 4,
		D3DXMESH_MANAGED,
		vertex::FVF,
		MN_DEV,
		&result);

	// vertex
	vertex* v = nullptr;
	if (SUCCEEDED(result->LockVertexBuffer(0, (void**)&v)))
	{
		v[0].pos = D3DXVECTOR3(-1, -1, 1);
		v[1].pos = D3DXVECTOR3(-1, 1, 1);
		v[2].pos = D3DXVECTOR3(1, 1, 1);
		v[3].pos = D3DXVECTOR3(1, -1, 1);

		v[0].uv = D3DXVECTOR2(0, 1);
		v[1].uv = D3DXVECTOR2(0, 0);
		v[2].uv = D3DXVECTOR2(1, 0);
		v[3].uv = D3DXVECTOR2(1, 1);

		result->UnlockVertexBuffer();
	}

	// index
	WORD* index = nullptr;
	if (SUCCEEDED(result->LockIndexBuffer(0, (void**)&index)))
	{
		index[0] = 0; index[1] = 1; index[2] = 2;
		index[3] = 0; index[4] = 2; index[5] = 3;

		result->UnlockIndexBuffer();
	}

	*out = result;
}

void maptool_render::drawOutLine(staticMesh * obj, D3DXVECTOR4 * color)
{
	renderSet & rsOrigin = _vRenderTarget[0];
	renderSet & rsTarget = _vRenderTarget[1];
	auto meshSet = obj->getMeshSet();

	_outline->SetMatrix("_mWorld", &obj->getMatrixFinal());
	_outline->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_outline->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());
	_outline->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());

	// 광원
	D3DXMATRIXA16 mRotation = GET_CAMERA()->getMatrixRotate();
	D3DXVECTOR3 offset = GET_CAMERA()->getOffset();
	D3DXVec3TransformCoord(&offset, &offset, &mRotation);

	D3DXVECTOR4 viewPosition(GET_CAMERA()->getPosition() - offset, 1.0f);
	D3DXVECTOR4 lightDirection(GET_LIGHT()->getDirectForward(), 0.0f);

	_outline->SetVector("_viewPosition", &viewPosition);
	_outline->SetVector("_lightDirection", &lightDirection);

	// 텍스쳐
	_outline->SetTexture("_renderOrigin", rsOrigin.renderTarget);
	_outline->SetTexture("_renderOutline", rsTarget.renderTarget);

	_outline->SetFloat("_winSizeX", (float)GET_WINDOW_SIZE().cx);
	_outline->SetFloat("_winSizeY", (float)GET_WINDOW_SIZE().cy);

	// 색상
	_outline->SetVector("_outLineColor", color == nullptr ? &defColor : color);

	gFunc::runRenderTarget(rsOrigin.renderTarget, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, rsOrigin.depthStensil, [&](void)->void {
		for (int i = 0; i < meshSet->numMaterial; ++i)
		{
			_outline->SetTexture("_textureDiffuse", meshSet->vTextureList[i]);

			gFunc::runEffectLoop(_outline, "techOrigin", [&](int passNum)->void {
				meshSet->mesh->DrawSubset(i);
			});
		}
	}, true);

	gFunc::runRenderTarget(rsTarget.renderTarget, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, rsTarget.depthStensil, [&](void)->void {
		gFunc::runEffectLoop(_outline, "techOutline", [&](int passNum)->void {
			_screen->DrawSubset(0);
		});
	}, true);

	gFunc::runRenderTarget(nullptr, NULL, nullptr, [&](void)->void {
		gFunc::runEffectLoop(_outline, "techBlur", [&](int passNum)->void {
			_screen->DrawSubset(0);
		});
	}, true);
}

void maptool_render::drawOutLine(skinnedMesh * obj)
{
}

void maptool_render::drawOutList(std::vector<baseObject*> & objList, D3DXVECTOR4* color)
{
	renderSet & rsOrigin = _vRenderTarget[0];
	renderSet & rsTarget = _vRenderTarget[1];

	gFunc::runRenderTarget(rsOrigin.renderTarget, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, rsOrigin.depthStensil, [](void)->void {});

	_outline->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_outline->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());
	_outline->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());

	// 광원
	D3DXMATRIXA16 mRotation = GET_CAMERA()->getMatrixRotate();
	D3DXVECTOR3 offset = GET_CAMERA()->getOffset();
	D3DXVec3TransformCoord(&offset, &offset, &mRotation);

	D3DXVECTOR4 viewPosition(GET_CAMERA()->getPosition() - offset, 1.0f);
	D3DXVECTOR4 lightDirection(GET_LIGHT()->getDirectForward(), 0.0f);

	_outline->SetVector("_viewPosition", &viewPosition);
	_outline->SetVector("_lightDirection", &lightDirection);

	// 텍스쳐
	_outline->SetTexture("_renderOrigin", rsOrigin.renderTarget);
	_outline->SetTexture("_renderOutline", rsTarget.renderTarget);

	_outline->SetFloat("_winSizeX", (float)GET_WINDOW_SIZE().cx);
	_outline->SetFloat("_winSizeY", (float)GET_WINDOW_SIZE().cy);

	// 색상
	_outline->SetVector("_outLineColor", color == nullptr ? &defColor : color);

	for (auto viewObject : objList)
	{
		staticMesh* obj = dynamic_cast<staticMesh*>(viewObject);
		if (obj == nullptr) 
			continue;

		auto meshSet = obj->getMeshSet();

		_outline->SetMatrix("_mWorld", &obj->getMatrixFinal());

		gFunc::runRenderTarget(rsOrigin.renderTarget, NULL, rsOrigin.depthStensil, [&](void)->void {
			for (int i = 0; i < meshSet->numMaterial; ++i)
			{
				_outline->SetTexture("_textureDiffuse", meshSet->vTextureList[i]);

				gFunc::runEffectLoop(_outline, "techOrigin", [&](int passNum)->void {
					meshSet->mesh->DrawSubset(i);
				});
			}
		}, true);
	}

	gFunc::runRenderTarget(rsTarget.renderTarget, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, rsTarget.depthStensil, [&](void)->void {
		gFunc::runEffectLoop(_outline, "techOutline", [&](int passNum)->void {
			_screen->DrawSubset(0);
		});
	}, true);

	gFunc::runRenderTarget(nullptr, NULL, nullptr, [&](void)->void {
		gFunc::runEffectLoop(_outline, "techBlur", [&](int passNum)->void {
			_screen->DrawSubset(0);
		});
	}, true);
}
