//************************************************
// DX���C�u���� �A�j���[�V����
// �쐬���F2024/03/31
// �쐬�ҁFfujioka8700
// Copyright (c) fujioka8700 All rights reserved.
//************************************************

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

	ChangeWindowMode(TRUE);            // �E�B���h�E���[�h
	SetWaitVSyncFlag(FALSE);           // ������������
	SetAlwaysRunFlag(TRUE);            // ��A�N�e�B�u����
	SetMainWindowText("������������"); // �E�B���h�E�̃^�C�g��

	if (DxLib_Init() == -1) return -1;

	const float RADIUS = 20, SPEED = 640.0f / 2.0f;
	float    x, y, speed;
	LONGLONG fpsTimer, deltaTimer;

	fpsTimer = deltaTimer = GetNowHiPerformanceCount();

	x = RADIUS, y = 240;
	speed = SPEED;

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		float deltaTime = getDeltaTime(&deltaTimer);

		x += speed * deltaTime; // �t���[�����[�g�ɍ��E���ꂸ�A�����X�s�[�h���Œ肷��
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