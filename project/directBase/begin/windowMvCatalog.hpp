#include "windowMvCatalog.h"

#include "gFunc.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"
#include "buttonCatalogItem.h"

template<typename T>
windowMvCatalog<T>::windowMvCatalog(const uiInfo & info) :
	windowMoveable(info)
{
	_scroll = (buttonScrollVertical*)addButton("scroll", new buttonScrollVertical(this, 4, 4));

	for (int i = 0; i < 20; ++i)
	{
		auto btn = createButtonCatalog(i);

		_vCatalog.push_back(btn);

		char buf[64];
		sprintf_s(buf, "Catalog_%d", i);
		addButton(buf, btn);
	}
}

template<typename T>
windowMvCatalog<T>::~windowMvCatalog()
{
	for (auto i : _vCatalog)
		SAFE_DELETE(i);
}

template<typename T>
inline windowBase::UI_LIST_NODE windowMvCatalog<T>::updateWindow(void)
{
	_offset = 
		(_info.size.y - BTN_MOVE_BAR_SIZE_Y) *
		_scroll->getValue() * (rowCount() / 4.0f);

	float btnSize = (_info.size.y - BTN_MOVE_BAR_SIZE_Y) / 4.0f;
	float modOffset = std::fmodf(_offset, btnSize);
	for (int i = 0; i < 20; ++i)
	{
		int dataIndex = (i % 4) + ((_offset - modOffset + (btnSize * (i / 4))) / btnSize) * 4;

		if (dataIndex < _vData.size())
		{
			auto & btnInfo = _vCatalog[i]->getInfo();
			auto texture = btnInfo.backImage = putTexture2button(dataIndex);
			
			D3DXVECTOR2 texSize;
			gFunc::getTextureSize(&texSize, texture);

			btnInfo.scale = D3DXVECTOR2(
				btnSize / texSize.x, 
				btnSize / texSize.y);
			btnInfo.size = texSize;
		}
		else
			_vCatalog[i]->getInfo().backImage = nullptr;
	}

	return _managedNode;
}

template<typename T>
buttonCatalogItem * windowMvCatalog<T>::createButtonCatalog(int index)
{
	return new buttonCatalogItem(this, index, &_offset);;
}

template<typename T>
inline void windowMvCatalog<T>::addItem(T input)
{
	_vData.push_back(input);

	int rows = rowCount();
	int listItemRows = rows < 4 ? 4 : rows;

	_scroll->putListHeight(listItemRows, 4);
}