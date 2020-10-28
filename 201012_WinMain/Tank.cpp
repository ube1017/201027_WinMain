#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"

Tank::Tank()
{
}


Tank::~Tank()
{
}

HRESULT Tank::Init()
{
	target = nullptr;
	size = 100;
	rc = {	(WINSIZE_X / 2) - (size / 2), (WINSIZE_Y) - (size / 2),
			(WINSIZE_X / 2) + (size / 2), (WINSIZE_Y) + (size / 2) };
	speed = 5.0f;

	// ����
	barrelSize = 150;
	barrelEnd.x = WINSIZE_X / 2;
	barrelEnd.y = WINSIZE_Y - barrelSize;
	barrelAngle = 90.0f;		// ���� : degree(0 ~ 360), radian(0 ~ 6.28)

	//90 : 360 = x : 6.28

	//	360 * x = 90 * 6.28
	//	x = DegreeToRadian(90);

	// �̻���
	missileCount = 20;
	missile = new Missile[missileCount];
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Init();
	}

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Release();
	}
	delete[] missile;
}

void Tank::Update()
{
	// �̻��� �߻� Ű�Է�
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
	{
		Fire();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		RotateBarrel(1.0f);
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		RotateBarrel(-1.0f);
	}

	if (missile)
	{
		for (int i = 0; i < missileCount; i++)
		{
			missile[i].Update();
		}
	}
}

void Tank::Render(HDC hdc)
{
	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);

	// ����
	MoveToEx(hdc, WINSIZE_X / 2, WINSIZE_Y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
	if (missile)
	{
		for (int i = 0; i < missileCount; i++)
		{
			missile[i].Render(hdc);
		}
	}
}

void Tank::Fire()
{
	if (missile)
	{
		for (int i = 0; i < missileCount; i++)
		{
			if (missile[i].GetIsFire() == false)
			{
				missile[i].SetPos(barrelEnd);
				missile[i].SetAngle(barrelAngle);
				missile[i].SetIsFire(true);
				break;
			}
		}
	}
}

void Tank::Move()
{
}

void Tank::Dead()
{
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;
	barrelEnd.x = WINSIZE_X / 2
		+ cosf(DegreeToRadian(barrelAngle)) * barrelSize;
	barrelEnd.y = WINSIZE_Y
		- sinf(DegreeToRadian(barrelAngle)) * barrelSize;
}

void Tank::SetTarget(Enemy * target)
{
	this->target = target;
	if (missile)
	{
		missile->SetTarget(target);
	}
}
