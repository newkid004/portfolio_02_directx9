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

	// īŻ�α� �� ���������� ����
	CATALOG::duplicate((triggerMesh**)&duplication, (CATA_OBJ::TRIGGER*)item);

	if (duplication)
	{
		DATA_IO::OBJ::BASE* ioBase = nullptr;

		DATA_IO::create((DATA_IO::OBJ::TRIGGER**)&ioBase, (triggerMesh*)duplication);

		// ������ ���� field�� ����Ʈ�� �߰�
		if (ioBase)
		{
			_set.data_field->getSet().objList.push_back(duplication);
			_set.data_field->getSet().dataList.push_back(ioBase);

			auto & selectionList = _set.data_field->getSet().selectionObject;

			selectionList.clear();
			selectionList.push_back(duplication);

			auto & selection = selectionList.front();

			// ��ġ, ȸ�� �ʱ�ȭ
			D3DXVECTOR3 pickPos;
			if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
				selection->setPosition(pickPos);

			selection->rotateBillboard(true, true);
		}
	}
}