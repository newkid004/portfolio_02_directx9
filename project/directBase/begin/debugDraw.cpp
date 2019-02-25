#include "debugDraw.h"

#include "managerList.h"
#include "gFunc.h"

using namespace std;

debugDraw::debugDraw(renderObject * bind, EDebugDrawType drawType) :
	_bindObject(bind),
	_drawType(drawType)
{
	switch (drawType)
	{
	case EDebugDrawType::NONE:
	case EDebugDrawType::BOX:		
	case EDebugDrawType::SPHERE:
	{
		_meshBoundingSphere = createBoundingSphere(bind->getBoundingSphere());
		createBoundingBox(bind->getBoundingBoxList());
		createBoundingBox(bind->getBoundingBoxSetList());
		createBoundingSphere(bind->getBoundingSphereSetList());
	} break;
	case EDebugDrawType::PROP:
	case EDebugDrawType::WALL:
	{
		createBoundingBox(bind->getBoundingBoxList());
	} break;
	}
	
}

debugDraw::~debugDraw()
{
	for (int i = 0; i < _vMeshBoundingBoxList.size(); ++i)
	{
		SAFE_RELEASE(_vMeshBoundingBoxList[i]);
		SAFE_RELEASE(_vMeshBoundingSphereList[i]);
	}

	for (auto iter = _mMeshBoundingBoxSetList.begin(); iter != _mMeshBoundingBoxSetList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_RELEASE(iter->second);
			iter = _mMeshBoundingBoxSetList.erase(iter);
		}
		else ++iter;
	}

	for (auto iter = _mMeshBoundingSphereSetList.begin(); iter != _mMeshBoundingSphereSetList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_RELEASE(iter->second);
			iter = _mMeshBoundingSphereSetList.erase(iter);
		}
		else ++iter;
	}

	SAFE_RELEASE(_meshBoundingBox);
	SAFE_RELEASE(_meshBoundingSphere);
}

void debugDraw::drawPre(void)
{
	renderObject::drawPre();

	MN_DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	MN_DEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	MN_DEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void debugDraw::drawDo(void)
{
	renderObject::drawDo();

	updateBoundingMatrix();

	if (_drawType == EDebugDrawType::BOX)
		drawBoundingBox();
	else if (_drawType == EDebugDrawType::SPHERE)
		drawBoundingSphere();

	drawGuideLine();

	if (MN_KEY->keyPress(DIK_1))
	{
		_drawType = EDebugDrawType::NONE;
	}
	else if (MN_KEY->keyPress(DIK_2))
	{
		_drawType = EDebugDrawType::BOX;
	}
	else if (MN_KEY->keyPress(DIK_3))
	{
		_drawType = EDebugDrawType::SPHERE;
	}
}

void debugDraw::drawPost(void)
{
	renderObject::drawPost();

	MN_DEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	MN_DEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	MN_DEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void debugDraw::updateBoundingMatrix(void)
{
	for (auto rValue : _mMeshBoundingBoxSetList)
	{
		_mbBoxSet.find(rValue.first)->second.matrix = _bindObject->getBoundingBoxSetList().find(rValue.first)->second.matrix;
	}

	for (auto rValue : _mMeshBoundingSphereSetList)
	{
		_mbSphereSet.find(rValue.first)->second.matrix = _bindObject->getBoundingBoxSetList().find(rValue.first)->second.matrix;
	}
}

void debugDraw::drawBoundingBox(void)
{
	for (int i = 0; i < _vMeshBoundingBoxList.size(); ++i)
	{
		if (_vMeshBoundingBoxList[i] == nullptr) return;
	
		D3DXMATRIXA16 mWorld;
		getMatrixBound(i, &mWorld, EDebugDrawType::BOX);
		MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);
	
		_vMeshBoundingBoxList[i]->DrawSubset(0);
	}
	
	for (auto rValue : _mMeshBoundingBoxSetList)
	{
		D3DXMATRIXA16 mWorld;
		D3DXMATRIXA16 mCombine = _mbBoxSet.find(rValue.first)->second.matrix;
		getMatrixBound(rValue.first, &mWorld, mCombine, EDebugDrawType::BOX);
		MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

		rValue.second->DrawSubset(0);
	}

}

void debugDraw::drawBoundingSphere(void)
{
	if (_meshBoundingSphere != nullptr)
	{
		D3DXMATRIXA16 mWorld;
		getMatrixBound(&mWorld, EDebugDrawType::SPHERE);
		MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

		_meshBoundingSphere->DrawSubset(0);
	}

	for (int i = 0; i < _vMeshBoundingSphereList.size(); ++i)
	{
		if (_vMeshBoundingSphereList[i] == nullptr) return;

		D3DXMATRIXA16 mWorld;
		getMatrixBound(i, &mWorld, EDebugDrawType::SPHERE);
		MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

		_vMeshBoundingSphereList[i]->DrawSubset(0);
	}

	for (auto rValue : _mMeshBoundingSphereSetList)
	{
		D3DXMATRIXA16 mWorld;
		D3DXMATRIXA16 mCombine = _mbSphereSet.find(rValue.first)->second.matrix;
		getMatrixBound(rValue.first, &mWorld, mCombine, EDebugDrawType::SPHERE);
		MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

		rValue.second->DrawSubset(0);
	}
}

void debugDraw::drawGuideLine(void)
{
	vertex vertices[2];
	ZeroMemory(vertices, sizeof(vertices));

	vertices[0].diffuse = COLOR_YELLOW(255);
	vertices[1].diffuse = COLOR_YELLOW(255);

	D3DXMATRIXA16 mWorld;
	D3DXMatrixIdentity(&mWorld);
	MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

	switch (_drawType)
	{
	case EDebugDrawType::BOX: {
		boundingBox bound;
		_bindObject->getBoundingBoxFinal(&bound);

		vertices[0].pos = bound.min;
		vertices[1].pos = bound.max;

		drawGuideLineBox();
	} break;

	case EDebugDrawType::SPHERE: {
		boundingSphere bound;
		_bindObject->getBoundingSphereFinal(&bound);

		vertices[0].pos = bound.center;
		vertices[1].pos = bound.center + (D3DXVECTOR3(0.707f, 0.707f, -0.707f) * bound.radius);
	} break;
	}

	MN_DEV->SetFVF(vertex::FVF);
	MN_DEV->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(vertex));
}

void debugDraw::drawGuideLineBox(void)
{
	vertex vertices[24];
	ZeroMemory(vertices, sizeof(vertices));

	for (auto & v : vertices)
		v.diffuse = COLOR_GREEN(255);

	objectBox objBox;
	boundingBox bndBox;

	_bindObject->getObjectBox(&objBox);
	gFunc::obj2bound(&bndBox, &objBox);

	D3DXVECTOR3 boxInterval(
		bndBox.max.x - bndBox.min.x,
		bndBox.max.y - bndBox.min.y,
		bndBox.max.z - bndBox.min.z);

	// ----- 하단 ----- // ↑ → ↓ ←
	vertices[0].pos = bndBox.min;
	vertices[1].pos = vertices[0].pos + D3DXVECTOR3(0.0f, 0.0f, boxInterval.z);

	vertices[2].pos = vertices[1].pos;
	vertices[3].pos = vertices[2].pos + D3DXVECTOR3(boxInterval.x, 0.0f, 0.0f);

	vertices[4].pos = vertices[3].pos;
	vertices[5].pos = vertices[4].pos + D3DXVECTOR3(0.0f, 0.0f, -boxInterval.z);

	vertices[6].pos = vertices[5].pos;
	vertices[7].pos = vertices[6].pos + D3DXVECTOR3(-boxInterval.x, 0.0f, 0.0f);

	// ----- 상단 ----- // ↑ → ↓ ←
	vertices[8 + 0].pos = bndBox.min + D3DXVECTOR3(0.0f, boxInterval.y, 0.0f);
	vertices[8 + 1].pos = vertices[8 + 0].pos + D3DXVECTOR3(0.0f, 0.0f, boxInterval.z);

	vertices[8 + 2].pos = vertices[8 + 1].pos;
	vertices[8 + 3].pos = vertices[8 + 2].pos + D3DXVECTOR3(boxInterval.x, 0.0f, 0.0f);

	vertices[8 + 4].pos = vertices[8 + 3].pos;
	vertices[8 + 5].pos = vertices[8 + 4].pos + D3DXVECTOR3(0.0f, 0.0f, -boxInterval.z);

	vertices[8 + 6].pos = vertices[8 + 5].pos;
	vertices[8 + 7].pos = vertices[8 + 6].pos + D3DXVECTOR3(-boxInterval.x, 0.0f, 0.0f);

	// ----- 세로 선 ----- // ↙ ↖ ↗ ↘
	vertices[16].pos = vertices[0 + 0].pos;
	vertices[17].pos = vertices[0 + 8].pos;

	vertices[18].pos = vertices[2 + 0].pos;
	vertices[19].pos = vertices[2 + 8].pos;

	vertices[20].pos = vertices[4 + 0].pos;
	vertices[21].pos = vertices[4 + 8].pos;

	vertices[22].pos = vertices[6 + 0].pos;
	vertices[23].pos = vertices[6 + 8].pos;

	MN_DEV->SetFVF(vertex::FVF);
	MN_DEV->DrawPrimitiveUP(D3DPT_LINELIST, 12, vertices, sizeof(vertex));
}

void debugDraw::createBoundingBox(std::vector<boundingBox> & input)
{
	LPD3DXMESH result = nullptr;

	for (int i = 0; i < input.size(); ++i)
	{
		_vbBox.push_back(input[i]);

		D3DXCreateBox(
			MN_DEV,
			input[i].max.x - input[i].min.x,
			input[i].max.y - input[i].min.y,
			input[i].max.z - input[i].min.z,
			&result,
			NULL);

		_vMeshBoundingBoxList.push_back(result);
	}
}

void debugDraw::createBoundingBox(BOUNDBOXMATRIXSET & input)
{
	LPD3DXMESH result = nullptr;

	_mbBoxSet = input;
	for(auto rValue : _mbBoxSet)
	{
		D3DXCreateBox(
			MN_DEV,
			rValue.second.box.max.x - rValue.second.box.min.x,
			rValue.second.box.max.y - rValue.second.box.min.y,
			rValue.second.box.max.z - rValue.second.box.min.z,
			&result,
			NULL);

		_mMeshBoundingBoxSetList.insert(unordered_map<string, LPD3DXMESH>::value_type(rValue.first, result));
	}
}

LPD3DXMESH debugDraw::createBoundingSphere(boundingSphere & input)
{
	LPD3DXMESH result = nullptr;

	_bSphere = input;

	D3DXCreateSphere(
		MN_DEV,
		input.radius,
		10,
		10,
		&result,
		NULL);
	
	return result;
}

void debugDraw::createBoundingSphere(std::vector<boundingSphere> & input)
{
	LPD3DXMESH result = nullptr;

	for (int i = 0; i < input.size(); ++i)
	{
		_vbSphere.push_back(input[i]);

		D3DXCreateSphere(
			MN_DEV,
			input[i].radius,
			10,
			10,
			&result,
			NULL);

		_vMeshBoundingSphereList.push_back(result);
	}
}

void debugDraw::createBoundingSphere(BOUNDSPHEREMATRIXSET & input)
{
	LPD3DXMESH result = nullptr;


	_mbSphereSet = input;
	for (auto rValue : _mbSphereSet)
	{
		D3DXCreateSphere(
			MN_DEV,
			rValue.second.sphere.radius,
			10,
			10,
			&result,
			NULL);

		_mMeshBoundingSphereSetList.insert(unordered_map<string, LPD3DXMESH>::value_type(rValue.first, result));
	}
}

LPD3DXMESH debugDraw::getBoundMesh(EDebugDrawType type)
{
	if (type == EDebugDrawType::NONE)
		type = _drawType;

	switch (type)
	{
	case EDebugDrawType::BOX:		return _meshBoundingBox;	break;
	case EDebugDrawType::SPHERE:	return _meshBoundingSphere;	break;
	}

	return nullptr;
}

void debugDraw::getMatrixBound(D3DXMATRIXA16 * outMat, EDebugDrawType type)
{
	if (type == EDebugDrawType::NONE)
		type = _drawType;

	switch (type)
	{
	case EDebugDrawType::BOX: {

		D3DXMATRIXA16 mTranslate;
		D3DXMatrixTranslation(
			&mTranslate,
			(_bBox.min.x + _bBox.max.x) / 2.0f,
			(_bBox.min.y + _bBox.max.y) / 2.0f,
			(_bBox.min.z + _bBox.max.z) / 2.0f);

		*outMat = _bindObject->getMatrixFinal() * mTranslate;
	} break;

	case EDebugDrawType::SPHERE: {
		D3DXMATRIXA16 mTranslate;
		D3DXMatrixTranslation(
			&mTranslate,
			_bSphere.center.x,
			_bSphere.center.y,
			_bSphere.center.z);

		*outMat = _bindObject->getMatrixFinal() * mTranslate;
	} break;
	}
}

void debugDraw::getMatrixBound(int index, D3DXMATRIXA16 * outMat, EDebugDrawType type)
{
	if (type == EDebugDrawType::NONE)
		type = _drawType;

	switch (type)
	{
	case EDebugDrawType::BOX: {

		D3DXMATRIXA16 mTranslate;
		D3DXMatrixTranslation(
			&mTranslate,
			(_vbBox[index].min.x + _vbBox[index].max.x) / 2.0f,
			(_vbBox[index].min.y + _vbBox[index].max.y) / 2.0f,
			(_vbBox[index].min.z + _vbBox[index].max.z) / 2.0f);

		*outMat = mTranslate * _bindObject->getMatrixFinal();
	} break;

	case EDebugDrawType::SPHERE: {
		D3DXMATRIXA16 mTranslate;
		D3DXMatrixTranslation(
			&mTranslate,
			_vbSphere[index].center.x,
			_vbSphere[index].center.y,
			_vbSphere[index].center.z);

		*outMat = mTranslate * _bindObject->getMatrixFinal();
	} break;
	}
}

void debugDraw::getMatrixBound(string name, D3DXMATRIXA16 * outMat, D3DXMATRIXA16 & combineMat, EDebugDrawType type)
{
	if (type == EDebugDrawType::NONE)
		type = _drawType;

	switch (type)
	{
	case EDebugDrawType::BOX: {
		boundingBox box = _mbBoxSet.find(name)->second.box;
		D3DXMATRIXA16 mTranslate;
		D3DXMatrixTranslation(
			&mTranslate,
			(box.min.x + box.max.x) / 2.0f,
			(box.min.y + box.max.y) / 2.0f,
			(box.min.z + box.max.z) / 2.0f);

		*outMat = combineMat * mTranslate;
	} break;

	case EDebugDrawType::SPHERE: {
		boundingSphere sphere = _mbSphereSet.find(name)->second.sphere;
		D3DXMATRIXA16 mTranslate;
		D3DXMatrixTranslation(
			&mTranslate,
			sphere.center.x,
			sphere.center.y,
			sphere.center.z);

		*outMat = combineMat * mTranslate;
	} break;
	}

}
