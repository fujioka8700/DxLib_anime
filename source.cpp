//************************************************
// DXライブラリ アニメーション
// 作成日：2024/03/31
// 作成者：fujioka8700
// Copyright (c) fujioka8700 All rights reserved.
//************************************************

#include <Dxlib.h>

//================================================
// FPSの計測と描画
//================================================
void FpsDraw(LONGLONG* p)
{
#ifdef _DEBUG
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
#endif // !_DEBUG
}

//================================================
// 主処理
//================================================
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

	const float RADIUS = 20, SPEED = 0.01f;
	float x, y, speed;
	LONGLONG fpsTimer = GetNowHiPerformanceCount();

	x = RADIUS, y = 240;
	speed = SPEED;

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		x += speed;
		if (x + RADIUS >= 640.0f)
		{
			x = 640.0f - RADIUS;
			speed = -SPEED;
		}
		else if (x - RADIUS < 0.0f) {
			x = RADIUS;
			speed = SPEED;
		}

		ClearDrawScreen();
		DrawCircleAA(x, y, RADIUS, 32, GetColor(255, 255, 0), TRUE);
		FpsDraw(&fpsTimer);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}