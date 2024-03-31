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

	for (int x = 0; x < 640; x += 2)
	{
		int y = (int)(80.0 * sin(M_PI * x * 4.0 / 180.0));

		DrawCircle(x, 240 - y, 3, GetColor(255, 255, 0), TRUE);
	}

	WaitKey();
	ClearDrawScreen();

	for (int y = 0; y < 480; y += 2)
	{
		int x = (int)(80.0 * sin(M_PI * y * 4.0 / 180.0));

		DrawCircle(320 + x,  y, 3, GetColor(255, 0, 255), TRUE);
	}

	WaitKey();

	DxLib_End();
	return 0;
}