#include "nodeMesh.h"

#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "camera.h"

#include "aStar_node.h"

nodeMesh::nodeMesh(const mParam & param) :
	staticMesh(param)
{
	_plane = createPlane();
	_meshSet->vTextureList[0] = MN_SRC->getTexture("resource/texture/maptool/nodeRange.png");

	setScale(0.05f);
}

nodeMesh::~nodeMesh()
{
	SAFE_RELEASE(_plane);
}

void nodeMesh::update(void)
{
	calMatrixFinal();

	// 자식 갱신
	for (auto childObject : _vChildren)
		childObject->update();
}

void nodeMesh::drawDo(void)
{
	renderObject::drawDo();

	_effect->SetMatrix("_mWorld", &getMatrixFinal());
	_effect->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());
	_effect->SetVector("_diffuse", &_nodeColor);

	gFunc::runEffectLoop(_effect, "techSphere", [&](int passNum)->void {
		_meshSet->mesh->DrawSubset(0);
	});

	_effect->SetTexture("_texture", _meshSet->vTextureList[0]);
	_effect->SetMatrix("_mWorldPlane", &_mWorldPlane);
	gFunc::runEffectLoop(_effect, "techPlane", [&](int passNum)->void {
		_plane->DrawSubset(0);
	});
}

void nodeMesh::setBindNode(aStar_node * input)
{
	_bindNode = input; 
	input->getBindData() = this;
}

void nodeMesh::calMatrixFinal(void)
{
	// 이동
	D3DXMATRIXA16 mTranslation;
	D3DXMatrixTranslation(&mTranslation,
		_position.x,
		_position.y,
		_position.z);

	// 척도
	D3DXMATRIXA16 mScalse;
	D3DXMatrixScaling(&mScalse,
		_scale.x,
		_scale.y,
		_scale.z);

	D3DXMATRIXA16 mScalsePlane;
	D3DXMatrixScaling(&mScalsePlane,
		_planeRadius,
		1.0f,
		_planeRadius);

	// 회전
	D3DXMATRIXA16 mRotation;
	D3DXMatrixIdentity(&mRotation);

	CopyMemory(&mRotation(0, 0), &_directionRight, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(1, 0), &_directionUp, sizeof(D3DXVECTOR3));
	CopyMemory(&mRotation(2, 0), &_directionForward, sizeof(D3DXVECTOR3));

	// world
	_mWorld = _mOffset * mScalse * mRotation * mTranslation;
	_mWorldPlane = _mOffset * mScalsePlane * mRotation * mTranslation;
}

LPD3DXMESH nodeMesh::createPlane(void)
{
	LPD3DXMESH result = nullptr;

	D3DXCreateMeshFVF(
		sizeof(WORD) * 2,	// 삼각형의 괴수(안덱스 개수), 기본적으로 2 byte
		sizeof(vertex) * 4,	// 정점개수
		D3DXMESH_MANAGED,	//
		vertex::FVF, 		//
		MN_DEV,				//
		&result);			//

	vertex* v = NULL;
	if (SUCCEEDED(result->LockVertexBuffer(0, (void**)&v)))
	{
		v[0].pos = D3DXVECTOR3(-1, 0, -1);
		v[1].pos = D3DXVECTOR3(-1, 0,  1);
		v[2].pos = D3DXVECTOR3( 1, 0,  1);
		v[3].pos = D3DXVECTOR3( 1, 0, -1);

		v[0].uv = D3DXVECTOR2(0, 1);
		v[1].uv = D3DXVECTOR2(0, 0);
		v[2].uv = D3DXVECTOR2(1, 0);
		v[3].uv = D3DXVECTOR2(1, 1);

		result->UnlockVertexBuffer();
	}

	WORD* i = NULL;
	if (SUCCEEDED(result->LockIndexBuffer(0, (void**)&i)))
	{
		i[0] = 0; i[1] = 1; i[2] = 2;
		i[3] = 2; i[4] = 3; i[5] = 0;

		result->UnlockIndexBuffer();
	}

	return result;
}
