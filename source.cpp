#define _USE_MATH_DEFINES
#include <math.h>
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

	DrawLine(320, 110, 320, 370, GetColor(128, 128, 128));
	DrawLine(30, 240, 610, 240, GetColor(128, 128, 128));

	for (int x = -290; x < 290; x++)
	{
		int y = (int)(sin(M_PI * x / 180.0f) * 100);
		DrawPixel(320 + x, 240 - y, GetColor(255, 0, 0));
	}
	for (int x = -290; x < 290; x+=10)
	{
		int y = (int)(sin(M_PI * x / 180.0f) * 100);
		DrawCircle(320 + x, 240 - y, 3, GetColor(255, 0, 0), TRUE);
	}

	WaitKey();

	DxLib_End();
	return 0;
}