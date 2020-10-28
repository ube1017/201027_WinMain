#pragma once

#include <Windows.h>
#include <math.h>
#include "KeyManager.h"

#define WINSIZE_X	1200
#define WINSIZE_Y	900
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)

struct FPOINT
{
	float x;
	float y;
};

extern HWND g_hWnd;