//************************************************
// DX���C�u���� �A�j���[�V����
// �쐬���F2024/04/01
// �쐬�ҁFfujioka8700
// Copyright (c) fujioka8700 All rights reserved.
//************************************************

#define _USE_MATH_DEFINES
#include <math.h>
#include <Dxlib.h>

//================================================
// FPS�̌v���ƕ`��
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
// �f���^�^�C���̌v��
//================================================
float getDeltaTime(LONGLONG* p)
{
	LONGLONG now = GetNowHiPerformanceCount();
	float    deltaTime = (float)(now - *p) / 1000000.0f;

	*p = now;
	return deltaTime;
}

//================================================
// �又��
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

	ChangeWindowMode(TRUE);              // �E�B���h�E���[�h
	SetMainWindowText("�A�j���[�V����"); // �E�B���h�E�̃^�C�g��

	if (DxLib_Init() == -1) return -1;

	const float RADIUS = 80, SPEED_ANGLE = 360.0f / 2.0f, INTERVAL = 1.5f;
	const float x = 320, y = 240;
	const int   POLYGON_MIN = 3, POLYGON_MAX = 10;
	float    angle, speedAngle;
	LONGLONG fpsTimer, deltaTimer;
	int      n, dn;
	float    intervalTime;

	fpsTimer = deltaTimer = GetNowHiPerformanceCount();

	angle = 0;
	speedAngle = SPEED_ANGLE;

	n = POLYGON_MIN;
	dn = 1;
	intervalTime = INTERVAL;

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		float deltaTime = getDeltaTime(&deltaTimer);

		angle += speedAngle * deltaTime;
		if (angle >= 360.0f)
		{
			angle -= 360.0f;
		}

		intervalTime -= deltaTime;
		if (intervalTime <= 0.0f)
		{
			intervalTime = INTERVAL;

			n += dn;
			if (n >= POLYGON_MAX || n <= POLYGON_MIN)
			{
				dn *= -1;
			}
		}
		
		ClearDrawScreen();

		for (int i = 0; i < n; i++)
		{
			float dx = (float)(RADIUS * cos(M_PI * (angle + i * 360.0 / n) / 180.0));
			float dy = (float)(RADIUS * sin(M_PI * (angle + i * 360.0 / n) / 180.0));
			float ex = (float)(RADIUS * cos(M_PI * (angle + (i + 1) * 360.0 / n) / 180.0));
			float ey = (float)(RADIUS * sin(M_PI * (angle + (i + 1) * 360.0 / n) / 180.0));
			int color = 255 - i * (255 - 64) / n;
			DrawTriangleAA(x - 40, y - 40, x + dx, y + dy, x + ex, y + ey, GetColor(color, color, 0), TRUE);
		}

		FpsDraw(&fpsTimer);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}