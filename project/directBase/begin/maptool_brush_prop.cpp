#include "maptool_brush_prop.h"

#include "maptool_field.h"
#include "maptool_data_catalog.h"
#include "maptool_data_io.h"

#include "windowCtlogMaptool.h"

maptool_brush_prop::maptool_brush_prop(sceneMapTool* viewData) :
	maptool_brush(viewData)
{
}

void maptool_brush_prop::putObject(void)
{
	typedef maptool_data_catalog CATALOG;
	typedef CATALOG::OBJ CATA_OBJ;

	windowCtlogMaptool* viewWindow = *_set.bindWindow;

	CATA_OBJ::BASE* item = viewWindow->getItem();
	renderObject* duplication = nullptr;

	// īŻ�α� �� ���������� ����
	if (item->_baseType & CATALOG::baseType::CHAR)			CATALOG::duplicate((skinnedMesh**)&duplication, (CATA_OBJ::CHAR*)item);
	else if (item->_baseType & CATALOG::baseType::BUMP)		CATALOG::duplicate((staticMesh**)&duplication, (CATA_OBJ::BUMP*)item);
	else if (item->_baseType & CATALOG::baseType::PROP)		CATALOG::duplicate((staticMesh**)&duplication, (CATA_OBJ::PROP*)item);

	if (duplication)
	{
		typedef maptool_data_io DATA_IO;

		DATA_IO::OBJ::BASE* ioBase = nullptr;

		if (item->_baseType & CATALOG::baseType::CHAR)			DATA_IO::create((DATA_IO::OBJ::CHAR**)&ioBase, (skinnedMesh*)duplication);
		else if (item->_baseType & CATALOG::baseType::BUMP)		DATA_IO::create((DATA_IO::OBJ::BUMP**)&ioBase, (staticMesh*)duplication);
		else if (item->_baseType & CATALOG::baseType::PROP)		DATA_IO::create((DATA_IO::OBJ::PROP**)&ioBase, (staticMesh*)duplication);

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