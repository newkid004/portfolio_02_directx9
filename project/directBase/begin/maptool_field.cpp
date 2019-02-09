#include "maptool_field.h"

#include "managerList.h"
#include "gFunc.h"
#include "pickRay.h"

#include "sceneBase.h"
#include "camera.h"

#include "terrain.h"
#include "mapObject.h"
#include "quadTree_Frustum.h"

#include "staticMesh.h"
#include "skinnedMesh.h"

maptool_field::maptool_field(mapObject* inTerrain)
{
	_fieldSet.field = inTerrain;
	if (_fieldSet.field)
	{
		auto & ter = _fieldSet.field->getTerrain();
		if (ter)	_fieldSet.qTree = new quadTree_Frustum(ter->getSizeMap().cx, ter->getSizeMap().cy);
		else		_fieldSet.qTree = new quadTree_Frustum(256, 256);

		_fieldSet.qTree->build();
	}
}

maptool_field::~maptool_field()
{
	SAFE_DELETE(_fieldSet.field);
	SAFE_DELETE(_fieldSet.qTree);

	for (auto i : _fieldSet.objList)
		SAFE_DELETE(i);

	for (auto i : _fieldSet.dataList)
		SAFE_DELETE(i);
}

void maptool_field::update(void)
{
	for (auto i : _fieldSet.objList)
		i->update();

	if (_fieldSet.field) _fieldSet.field->update();
	if (_fieldSet.qTree) _fieldSet.qTree->cullFrustum();
}

void maptool_field::draw(void)
{
	for (auto i : _fieldSet.objList)
	{
		if (auto rObject = dynamic_cast<renderObject*>(i))
			rObject->draw();
	}
	if (_fieldSet.field) _fieldSet.field->draw();
}

renderObject * maptool_field::getPickObject(void)
{
	float distance = FLT_MAX;
	renderObject* result = nullptr;

	for (int i = 0; i < _fieldSet.objList.size(); ++i)
	{
		// renderObject 확인
		auto rObject = dynamic_cast<renderObject*>(_fieldSet.objList[i]);
		if (dynamic_cast<renderObject*>(rObject))
		{
			// frustum culling 확인
			if (!rObject->isCull())
			{
				maptool_data_io::OBJ::BASE* rData = _fieldSet.dataList[i];
				
				// 형태 확인 : 캐릭터
				if (rData->_baseType & maptool_data_io::baseType::CHAR)
				{
					if (auto viewObject = dynamic_cast<skinnedMesh*>(rObject))
					{
						// 충돌 확인
						pick::ray ray = MN_KEY->getPickRay();
						pick::applyMatrix(&ray, &ray, &viewObject->getMatrixFinal());

						pick::info info;
						pick::chkPick(&info, &ray, viewObject->getMesh());

						if (info.isHit)
						{
							float clickDistance = D3DXVec3Length(&(ray.direction * info.distance));
							if (clickDistance < distance)
								result = viewObject;
						}
					}
				}
				// 형태 확인 : 물체
				else if (rData->_baseType & maptool_data_io::baseType::PROP)
				{
					if (auto viewObject = dynamic_cast<staticMesh*>(rObject))
					{
						// 충돌 확인
						pick::ray ray = MN_KEY->getPickRay();
						pick::applyMatrix(&ray, &ray, &viewObject->getMatrixFinal());

						pick::info info;
						pick::chkPick(&info, &ray, viewObject->getMeshSet()->mesh);

						if (info.isHit)
						{
							float clickDistance = D3DXVec3Length(&(ray.direction * info.distance));
							if (clickDistance < distance)
								result = viewObject;
						}
					}
				} // 형태 확인 끝
			} // frustum culling 확인 끝
		} // renderObject 확인 끝
	}

	return result;
}
