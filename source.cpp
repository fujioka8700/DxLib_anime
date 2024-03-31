#define _USE_MATH_DEFINES
#include <math.h>
#include <Dxlib.h>

typedef struct {
	float x, y;
} Pos;

void KochCurve(int n, Pos a, Pos b)
{
	if (n <= 0)
	{
		DrawLineAA(a.x, a.y, b.x, b.y, GetColor(255, 255, 0));
	}
	else {
		Pos c, d, e;

		c.x = (2 * a.x + b.x) / 3;
		c.y = (2 * a.y + b.y) / 3;
		
		d.x = (a.x + 2 * b.x) / 3;
		d.y = (a.y + 2 * b.y) / 3;

		e.x = c.x + (d.x - c.x) * (float)cos(M_PI * 60.0 / 180.0) + (d.y - c.y) * (float)sin(M_PI * 60.0 / 180.0);
		e.y = c.y - (d.x - c.x) * (float)sin(M_PI * 60.0 / 180.0) + (d.y - c.y) * (float)cos(M_PI * 60.0 / 180.0);

		KochCurve(n - 1, a, c);
		KochCurve(n - 1, c, e);
		KochCurve(n - 1, e, d);
		KochCurve(n - 1, d, b);
	}
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

	Pos a, b, c;

	a.x = 50.0f, a.y = 300.0f;
	b.x = 590.0f, b.y = 300.0f;

	for (int n = 0; n <= 5; n++)
	{
		ClearDrawScreen();
		KochCurve(n, a, b);
		WaitKey();
	}

	a.x = 120.0f, a.y = 358.0f;
	b.x = 320.0f, b.y =  12.0f;
	c.x = 520.0f, c.y = 358.0f;

	for (int n = 0; n <= 5; n++)
	{
		ClearDrawScreen();
		KochCurve(n, a, b);
		KochCurve(n, b, c);
		KochCurve(n, c, a);
		WaitKey();
	}

	DxLib_End();
	return 0;
}