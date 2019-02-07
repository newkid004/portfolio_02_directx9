#include "buttonCatalogItem.h"

#include "gFunc.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

buttonCatalogItem::buttonCatalogItem(windowBase * bind, int index, int* bindIndex, float * bindOffset) :
	buttonItem(bind, index, bindIndex, bindOffset, 4, 4)
{
}
