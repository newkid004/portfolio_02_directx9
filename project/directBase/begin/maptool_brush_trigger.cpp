#include "maptool_brush_trigger.h"

#include "maptool_field.h"
#include "maptool_data_catalog.h"
#include "maptool_data_io.h"

#include "windowCtlogMaptool.h"

#include "triggerMesh.h"

void maptool_brush_trigger::putObject(void)
{
	typedef maptool_data_catalog	CATALOG;
	typedef CATALOG::OBJ			CATA_OBJ;
	typedef maptool_data_io			DATA_IO;

	windowCtlogMaptool* viewWindow = *_set.bindWindow;

	CATA_OBJ::BASE* item = viewWindow->getItem();
	renderObject* duplication = nullptr;

	// 카탈로그 내 아이템정보 복사
	CATALOG::duplicate((triggerMesh**)&duplication, (CATA_OBJ::TRIGGER*)item);

	if (duplication)
	{
		DATA_IO::OBJ::BASE* ioBase = nullptr;

		DATA_IO::create((DATA_IO::OBJ::TRIGGER**)&ioBase, (triggerMesh*)duplication);

		// 복사한 정보 field내 리스트에 추가
		if (ioBase)
		{
			_set.data_field->getSet().objList.push_back(duplication);
			_set.data_field->getSet().dataList.push_back(ioBase);

			auto & selectionList = _set.data_field->getSet().selectionObject;

			selectionList.clear();
			selectionList.push_back(duplication);

			auto & selection = selectionList.front();

			// 위치, 회전 초기화
			D3DXVECTOR3 pickPos;
			if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
				selection->setPosition(pickPos);

			selection->rotateBillboard(true, true);
		}
	}
}