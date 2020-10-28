#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	tank1 = new Tank();
	tank1->Init();

	enemy1 = new Enemy[36];
	enemyCount = 36;
	for (int i = 0; i < enemyCount; i++)
	{
		enemy1[i].Init();
	}
	tank1->SetTarget(enemy1);
	
	return S_OK;
}

void MainGame::Release()
{
	tank1->Release();
	delete tank1;
	for (int i = 0; i < enemyCount; i++)
	{
		enemy1[i].Release();
	}
	delete [] enemy1;

	KeyManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	tank1->Update();
	for (int i = 0; i < enemyCount; i++)
	{
		enemy1[i].Update();
	}


	// 미사일 간 충돌처리
	Missile *m1, *m2;

	int missileCount = tank1->GetMissileCount();
	for (int i = 0; i < missileCount - 1; i++)
	{
		m1 = &(tank1->GetMissile()[i]);
		if (!m1->GetIsFire())	continue;

		for (int j = i + 1; j < missileCount; j++)
		{
			m2 = &(tank1->GetMissile()[j]);
			if (!m2->GetIsFire())	continue;

			if (CheckCollision(m1, m2))
			{
				if (true)
				{
					CalcAngle(m1,m2);// 충돌 시 처리
					
				}
			}
		}
	}

	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	if (tank1)
	{
		tank1->Render(hdc);
	}
	if (enemy1)
	{
		for (int i = 0; i < enemyCount; i++)
		{
			enemy1[i].Render(hdc);
		}
	
	}

	char szText[128] = "";

	wsprintf(szText, "X : %d, Y : %d", mouseData.mousePosX, mouseData.mousePosY);
	TextOut(hdc, 10, 5, szText, strlen(szText));

	wsprintf(szText, "Clicked X : %d, Y : %d",
		mouseData.clickedPosX, mouseData.clickedPosY);
	TextOut(hdc, 10, 30, szText, strlen(szText));
}

bool MainGame::CheckCollision(Missile * m1, Missile * m2)
{
	// m1의 반지름 + m2의 반지름 >= m1과 m2사이 거리 (->충돌)
	float halfSize1 = m1->GetSize() / 2.0f;
	float halfSize2 = m2->GetSize() / 2.0f;
	FPOINT pos1 = m1->GetPos();
	FPOINT pos2 = m2->GetPos();

	if (GetDistance(pos1, pos2) <= halfSize1 + halfSize2)
	{
		return true;
	}
	return false;
}

float MainGame::GetDistance(FPOINT pos1, FPOINT pos2)
{
	float dist = sqrtf((pos2.x - pos1.x) * (pos2.x - pos1.x)
		+ (pos2.y - pos1.y) * (pos2.y - pos1.y));

	return dist;
}

float MainGame::CalcAngle(Missile * m1, Missile * m2)
{
	float angle = 0.0f;
	float angle2 = 0.0f;
	float tempAngle;
	float missileAngle;
	FPOINT pos1 = m1->GetPos();
	FPOINT pos2 = m2->GetPos();
	missileAngle = atan2f(-(pos1.y - pos2.y), (pos1.x - pos2.x));
	tempAngle = DegreeToRadian(angle);
	tempAngle +=
		(missileAngle - DegreeToRadian(angle));
	angle = RadianToDegree(tempAngle);
	angle2 = 180 + angle;
	m1->SettingAngle(angle);
	m2->SettingAngle(angle2);
	return 0.0f;

}
FPOINT MainGame::SetEnemyPos(FPOINT pos)
{ 
	for (int i = 0; i < enemyCount; i++)
	{
		enemy1[i].GetPos += 60;
	}
	
}
LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		this->Update();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_RBUTTONDOWN:
		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}
