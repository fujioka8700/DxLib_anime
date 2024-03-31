#include <Dxlib.h>

void FpsDraw(LONGLONG* p)
{
	static int Fps = 0, FpsCnt = 0;
	LONGLONG now = GetNowHiPerformanceCount();

	FpsCnt++;
	if (now - *p > 1000000)
	{
		Fps = FpsCnt;
		FpsCnt = 0;
		*p = now;
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS: %d", Fps);
}

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

	const float Radius = 20;
	float x, y;
	LONGLONG fpsTimer = GetNowHiPerformanceCount();

	x = 0, y = 240;

	while (ProcessMessage() == 0)
	{
		x += 0.002f;

		ClearDrawScreen();

		DrawCircleAA(x, y, Radius, 32, GetColor(255, 255, 0), TRUE);

		FpsDraw(&fpsTimer);
	}

	DxLib_End();
	return 0;
}