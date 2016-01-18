#include "editor.h"

int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	editor::Editor* pEd = new editor::Editor;
	pEd->Run();
	return 0;
}