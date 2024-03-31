#include <Dxlib.h>

typedef struct {
	float x;
	float y;
} Pos;

struct {
	int r;
	int g;
	int b;
} Color_tb[6] = {
	{  0, 128, 255},
	{  0,  64, 255},
	{128,  64, 255},
	{128,   0, 255},
	{ 64,   0, 255},
	{  0, 128, 255},
};

void triangle(int n, Pos a, Pos b, Pos c)
{
	DrawTriangleAA(a.x, a.y, b.x, b.y, c.x, c.y,
		GetColor(Color_tb[n].r, Color_tb[n].g, Color_tb[n].b), TRUE);
	//WaitTimer(200);

	if (n < 1)
	{
		return;
	}
	else {
		Pos d, e, f;

		d.x = (a.x + b.x) / 2;
		d.y = (a.y + b.y) / 2;

		e.x = (b.x + c.x) / 2;
		e.y = (b.y + c.y) / 2;

		f.x = (a.x + c.x) / 2;
		f.y = (a.y + c.y) / 2;

		triangle(n - 1, a, d, f);
		triangle(n - 1, d, b, e);
		triangle(n - 1, f, e, c);
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

	a.x = 320.0f, a.y =  67.0f;
	b.x = 120.0f, b.y = 413.0f;
	c.x = 520.0f, c.y = 413.0f;
	
	for (int i = 0; i < 5; i++)
	{
		triangle(i, a, b, c);
		WaitKey();
	}

	WaitKey();

	DxLib_End();
	return 0;
}