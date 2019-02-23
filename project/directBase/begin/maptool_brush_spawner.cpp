#include "maptool_brush_spawner.h"

#include "maptool_field.h"

#include "maptool_data_io.h"
#include "maptool_data_catalog.h"

#include "windowCtlogMaptool.h"

#include "nodeMesh.h"

void maptool_brush_spawner::updateKey(void)
{
	maptool_brush::updateKey();
}

void maptool_brush_spawner::updateObjectMove(POINT & mouseMove)
{
	maptool_brush::updateObjectMove(mouseMove);
}

void maptool_brush_spawner::updateObjectDelete(void)
{
	maptool_brush::updateObjectDelete();
}

// maptool_brush_prop �� ����
void maptool_brush_spawner::putObject(void)
{
	typedef maptool_data_catalog CATALOG;
	typedef CATALOG::OBJ CATA_OBJ;

	windowCtlogMaptool* viewWindow = *_set.bindWindow;

	CATA_OBJ::BASE* item = viewWindow->getItem();
	renderObject* duplication = nullptr;

	// īŻ�α� �� ���������� ����
	CATALOG::duplicate((spawner**)&duplication, (CATA_OBJ::SPAWNER*)item);

	if (duplication)
	{
		typedef maptool_data_io DATA_IO;

		DATA_IO::OBJ::BASE* ioBase = nullptr;
		DATA_IO::create((DATA_IO::OBJ::SPAWNER**)&ioBase, (spawner*)duplication);

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
		}
	}
}
