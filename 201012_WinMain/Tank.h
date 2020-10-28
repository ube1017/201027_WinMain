#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class Enemy;
class Tank : public GameNode
{
private:
	// �Ӽ� : �������
	RECT rc;
	int size;
	float speed;

	// ����
	// ������ ������
	// ������ ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���
	Missile* missile;
	int missileCount;

	// �� (Ÿ��)
	Enemy* target;

public:
	// ��� : ����Լ�
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void Fire();
	void Move();
	void Dead();
	void RotateBarrel(float angle);

	void SetTarget(Enemy* target);

	Missile* GetMissile() { return this->missile; }
	int GetMissileCount() { return this->missileCount; }

	Tank();
	~Tank();
};

