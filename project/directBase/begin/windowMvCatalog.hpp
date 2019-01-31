#include "windowMvCatalog.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"
#include "buttonCatalogItem.h"

template<typename T>
windowMvCatalog<T>::windowMvCatalog(const uiInfo & info) :
	windowMoveable(info)
{
	_scroll = addButton("scroll", new buttonScrollVertical(this, 4, 4));

	for (int i = 0; i < 20; ++i)
		_vCatalog.push_back(createButtonCatalog(i));
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
		_scroll->getValue() *
		(rowCount() / 4.0f);

	float btnSize = (_info.size.y - BTN_MOVE_BAR_SIZE_Y) / 4.0f;
	float modOffset = std::fmodf(_offset, btnSize);
	for (int i = 0; i < 20; ++i)
	{
		int dataIndex = (_offset - modOffset - (btnSize * (i / 4))) / btnSize;

		_vCatalog[i]->getInfo().backImage = putTexture2button(dataIndex);
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