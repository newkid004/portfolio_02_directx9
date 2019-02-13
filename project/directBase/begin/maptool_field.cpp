#include "maptool_field.h"

#include "managerList.h"
#include "gFunc.h"
#include "gMng.h"
#include "pickRay.h"

#include "sceneBase.h"
#include "camera.h"
#include "frustum.h"
#include "heap.h"

#include "terrain.h"
#include "mapObject.h"
#include "quadTree_Frustum.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "nodeMesh.h"

#include "aStar_grape_bind.h"
#include "aStar_path.h"
#include "aStar_node.h"

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

	_fieldSet.pathGrape = new aStar_grape_bind<nodeMesh>();
}

maptool_field::~maptool_field()
{
	SAFE_DELETE(_fieldSet.field);
	SAFE_DELETE(_fieldSet.qTree);

	for (auto i : _fieldSet.objList)
		SAFE_DELETE(i);

	for (auto i : _fieldSet.dataList)
		SAFE_DELETE(i);

	SAFE_DELETE(_fieldSet.pathGrape);
	SAFE_DELETE(_fieldSet.pathData);
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

	drawPathGrape();
}

void maptool_field::updateBindGrape(void)
{
	for (auto i : _fieldSet.pathGrape->getBindList())
	{
		auto viewNode = i->getBindNode();
		i->setNodeColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
		
		if (_fieldSet.pathData)
		{
			for (auto path : _fieldSet.pathData->unpack())
			{
				if (viewNode == path->getMember().placedNode)
				{
					i->setNodeColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
					break;
				}
			}
		}
	}
}

void maptool_field::drawPathGrape(void)
{
	_fieldSet.pathGrape->runGrape([&](auto from, auto to)->void {

		aStar_node::info *infoA, *infoB;
		from->getInfo(infoA);
		to->getInfo(infoB);

		if (!(GET_FRUSTUM()->isCull(infoA->pos) && GET_FRUSTUM()->isCull(infoB->pos)))
		{
			static auto effect = MN_SRC->getEffect("resource/effect/simpleLine.fx");
			D3DXVECTOR3 v[2] = { infoA->pos, infoB->pos };

			effect->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());
			effect->SetVector("_diffuse", &D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));

			gFunc::runEffectLoop(effect, "techMain", [&](int passNum)->void {
				MN_DEV->DrawPrimitiveUP(D3DPT_LINELIST, 1, v, sizeof(D3DXVECTOR3));
			});
		}

	});
}

void maptool_field::getPickObject(baseObject** out_object, maptool_data_io::OBJ::BASE** out_data)
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

			if (result)
			{
				*out_data = _fieldSet.dataList[i];
				break;
			}
		} // renderObject 확인 끝
	}

	if (result) 
		*out_object = result;
}
