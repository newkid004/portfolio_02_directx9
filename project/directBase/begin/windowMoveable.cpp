#include "windowMoveable.h"

#include "managerList.h"
#include "gMng.h"

#include "buttonMoveBar.h"

windowMoveable::windowMoveable(const uiInfo & info) : 
	windowStatic(info)
{
	//*/
	buttonMoveBar * btn = new buttonMoveBar(this);
	_mButton.insert(decltype(_mButton)::value_type("moveBar", btn));
	
	/*/
	gMng::add((string)"moveBar", (buttonBase*)new buttonMoveBar(this), _mButton);

	//*/
}
