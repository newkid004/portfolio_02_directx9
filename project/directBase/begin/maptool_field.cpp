#include "maptool_field.h"

#include "managerList.h"
#include "gFunc.h"
#include "pickRay.h"

#include "sceneBase.h"
#include "camera.h"

#include "terrain.h"
#include "quadTree_Frustum.h"

#include "staticMesh.h"
#include "skinnedMesh.h"

maptool_field::maptool_field(terrain* inTerrain)
{
	_fieldSet.field = inTerrain;

	if (_fieldSet.field)
		_fieldSet.qTree = new quadTree_Frustum(inTerrain->getSizeMap().cx, inTerrain->getSizeMap().cy);
	else
		_fieldSet.qTree = new quadTree_Frustum(256, 256);

	_fieldSet.qTree->build();
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

	_fieldSet.qTree->cullFrustum();
}

void maptool_field::draw(void)
{
	for (auto i : _fieldSet.objList)
	{
		if (auto rObject = dynamic_cast<renderObject*>(i))
			rObject->draw();
	}
}

renderObject * maptool_field::getPickObject(void)
{
	float distance = FLT_MAX;
	renderObject* result = nullptr;

	for (int i = 0; i < _fieldSet.objList.size(); ++i)
	{
		// renderObject Ȯ��
		auto rObject = dynamic_cast<renderObject*>(_fieldSet.objList[i]);
		if (dynamic_cast<renderObject*>(rObject))
		{
			// frustum culling Ȯ��
			if (!rObject->isCull())
			{
				maptool_data::base* rData = _fieldSet.dataList[i];
				
				// ���� Ȯ�� : ĳ����
				if (rData->_baseType & maptool_data::baseType::CHAR)
				{
					if (auto viewObject = dynamic_cast<skinnedMesh*>(rObject))
					{
						// �浹 Ȯ��
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
				// ���� Ȯ�� : ��ü
				else if (rData->_baseType & maptool_data::baseType::PROP)
				{
					if (auto viewObject = dynamic_cast<staticMesh*>(rObject))
					{
						// �浹 Ȯ��
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
				} // ���� Ȯ�� ��
			} // frustum culling Ȯ�� ��
		} // renderObject Ȯ�� ��
	}

	return result;
}
