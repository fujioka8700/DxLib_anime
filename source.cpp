#include <Dxlib.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
#ifndef _DEBUG
	SetOutApplicationLogValidFlag(FALSE);
#endif // !_DEBUG

	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) return -1;

	DrawLine(0, 0, 640, 480, GetColor(255, 0, 0), 3);
	DrawLineAA(640, 0, 0, 480, GetColor(255, 0, 0), 3);

	DrawLine(220, 0, 220, 480, GetColor(0, 255, 0), 3);
	DrawLineAA(420, 0, 420, 480, GetColor(0, 255, 0), 3);

	DrawLine(0, 160, 640, 160, GetColor(0, 0, 255), 3);
	DrawLineAA(0, 320, 640, 320, GetColor(0, 0, 255), 3);
												  
	WaitKey();

	DxLib_End();
	return 0;
}