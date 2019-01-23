#include "kGlobalDefine.h"

#include "mainGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	SIZE size = { WINSIZEX, WINSIZEY };

	//*/
	mainGame mainGame(hInstance, size, nCmdShow);
	/*/
	practice_13 exam(hInstance, size, nCmdShow);
	//*/
	
	return mainGame.run();
}
