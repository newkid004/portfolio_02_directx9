#include "windowMoveable.h"

#include "managerList.h"
#include "gMng.h"

#include "buttonMoveBar.h"

windowMoveable::windowMoveable(const uiInfo & info) : windowStatic(info)
{
	addButton("moveBar", new buttonMoveBar(this));
}
