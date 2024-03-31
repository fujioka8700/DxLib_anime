#include <math.h>
#include <Dxlib.h>

typedef struct {
	float x, y;
	float length;
} Pos;

void LeftDownRight(int n, Pos* p);
void UpRightDown(int n, Pos* p);
void RightUpLeft(int n, Pos* p);
void DownLeftUp(int n, Pos* p);

void Line(float x1, float y1, float x2, float y2)
{
	static const int STEP = 64;
	static const int MAX = 256 / STEP;
	static int r = MAX, g = MAX, b = MAX;
	static int rDir = -1, gDir = -1, bDir = -1;

	DrawLineAA(x1, y1, x2, y2,
		GetColor(r * STEP - 1, g * STEP - 1, b * STEP - 1));

	if ((r += rDir) >= MAX || r <= 0)
	{
		r = (r <= 0) ? 1 : MAX;
		rDir *= -1;
		if ((g += gDir) >= MAX || g <= 0)
		{
			gDir *= -1;
			if ((b += bDir) >= MAX || b <= 0)
			{
				b = (b <= 0) ? 1 : MAX;
				bDir *= -1;
			}
		}
	}
}

void GoRight(Pos* p)
{
	Line(p->x, p->y, p->x + p->length, p->y);
	p->x += p->length;
}
void GoLeft(Pos* p)
{
	Line(p->x, p->y, p->x - p->length, p->y);
	p->x -= p->length;
}
void GoUp(Pos* p)
{
	Line(p->x, p->y, p->x, p->y - p->length);
	p->y -= p->length;
}
void GoDown(Pos* p)
{
	Line(p->x, p->y, p->x, p->y + p->length);
	p->y += p->length;
}

void LeftDownRight(int n, Pos *p)
{
	if (n > 0)
	{
		DownLeftUp(n - 1, p);
		GoLeft(p);
		LeftDownRight(n - 1, p);
		GoDown(p);
		LeftDownRight(n - 1, p);
		GoRight(p);
		UpRightDown(n - 1, p);
	}
}
void UpRightDown(int n, Pos* p)
{
	if (n > 0)
	{
		RightUpLeft(n - 1, p);
		GoUp(p);
		UpRightDown(n - 1, p);
		GoRight(p);
		UpRightDown(n - 1, p);
		GoDown(p);
		LeftDownRight(n - 1, p);
	}
}
void RightUpLeft(int n, Pos* p)
{
	if (n > 0)
	{
		UpRightDown(n - 1, p);
		GoRight(p);
		RightUpLeft(n - 1, p);
		GoUp(p);
		RightUpLeft(n - 1, p);
		GoLeft(p);
		DownLeftUp(n - 1, p);
	}
}
void DownLeftUp(int n, Pos* p)
{
	if (n > 0)
	{
		LeftDownRight(n - 1, p);
		GoDown(p);
		DownLeftUp(n - 1, p);
		GoLeft(p);
		DownLeftUp(n - 1, p);
		GoUp(p);
		RightUpLeft(n - 1, p);
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

	Pos pos;
	const int size = 480;
	const float startX = 80;

	for (int n = 1; n <= 6; n++)
	{
		ClearDrawScreen();

		pos.length = (float)(size / pow(2, n));
		pos.x = startX + size - pos.length / 2.0f;
		pos.y = pos.length / 2.0f;

		LeftDownRight(n, &pos);
		WaitKey();
	}

	DxLib_End();
	return 0;
}