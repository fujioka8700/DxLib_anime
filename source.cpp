//************************************************
// DXライブラリ アニメーション
// 作成日：2024/03/31
// 作成者：fujioka8700
// Copyright (c) fujioka8700 All rights reserved.
//************************************************

#define _USE_MATH_DEFINES
#include <math.h>
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
// デルタタイムの計測
//================================================
float getDeltaTime(LONGLONG* p)
{
	LONGLONG now = GetNowHiPerformanceCount();
	float    deltaTime = (float)(now - *p) / 1000000.0f;

	*p = now;
	return deltaTime;
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

	ChangeWindowMode(TRUE);              // ウィンドウモード
	SetMainWindowText("アニメーション"); // ウィンドウのタイトル

	if (DxLib_Init() == -1) return -1;

	const float RADIUS = 50, SPEED = 640.0f / 2.0f, SPEED_ANGLE = 360.0f / 2.0f;
	float    x, y, speed;
	float    angle, speedAngle;
	LONGLONG fpsTimer, deltaTimer;

	fpsTimer = deltaTimer = GetNowHiPerformanceCount();

	x = RADIUS, y = 240;
	speed = SPEED;

	angle = 0;
	speedAngle = SPEED_ANGLE;

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		float deltaTime = getDeltaTime(&deltaTimer);

		x += speed * deltaTime;
		if (x + RADIUS >= 640.0f)
		{
			x = 640.0f - RADIUS;
			speed *= -1;
			speedAngle *= -1;
		}
		else if (x - RADIUS < 0.0f) {
			x = RADIUS;
			speed *= -1;
			speedAngle *= -1;
		}

		angle += speedAngle * deltaTime;
		if (angle >= 360.0f)
		{
			angle -= 360.0f;
		}

		ClearDrawScreen();
		DrawCircleAA(x, y, RADIUS, 32, GetColor(255, 255, 0), FALSE);

		const int n = 10;
		for (int i = 0; i < n; i++)
		{
			float dx = (float)(RADIUS * cos(M_PI * (angle + i * 180.0 / n) / 180.0));
			float dy = (float)(RADIUS * sin(M_PI * (angle + i * 180.0 / n) / 180.0));
			DrawLineAA(x + dx, y + dy, x - dx, y - dy, GetColor(255, 255, 0));
		}

		FpsDraw(&fpsTimer);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}