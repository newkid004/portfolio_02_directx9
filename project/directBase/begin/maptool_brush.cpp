#include "maptool_brush.h"

#include "sceneMapTool.h"

#include "maptool_window.h"
#include "maptool_io.h"

#include "windowCtlogMaptool.h"
#include "maptool_field.h"


maptool_brush::maptool_brush(sceneMapTool* viewData)
{
	_set.bindWindow = &viewData->_window->getSet().focusedWindow;
	
	_set.data_window	= viewData->_window;
	_set.data_field		= viewData->_field;
	_set.data_io		= viewData->_io;
}

void maptool_brush::update(void)
{
	if (!MN_KEY->getClickIgnore())
		updateMouse();

	updateKey();
}

void maptool_brush::updateMouse(void)
{
	windowCtlogMaptool* focusedWindow = *_set.bindWindow;

	// window open
	if (focusedWindow)
	{
		if (0 <= focusedWindow->getIndex())
		{
			// 01. prop put
			if (MN_KEY->mousePress())
			{
				putObject();
				focusedWindow->getIndex() = -1;
			}
		}
	}

	// window close
	if (focusedWindow == nullptr || focusedWindow->getIndex() < 0)
	{
		// ready to mouse
		if (MN_KEY->mousePress())
			_mousePrev = MN_KEY->getMousePos();
	}
}

void maptool_brush::updateKey(void)
{
	// window close
	if (MN_KEY->keyPress(DIK_ESCAPE))
	{
		(*_set.bindWindow)->getIndex() = -1;
		(*_set.bindWindow)->close();
	}

	// save, load
	if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->keyPress(DIK_S))
		_set.data_io->write();
	if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->keyPress(DIK_L))
	{
		int fileSelection = _set.data_window->getSet().mv_file->getIndex();

		_set.data_io->read();

		_set.data_window->getSet().mv_file->getIndex() = fileSelection;
	}
}