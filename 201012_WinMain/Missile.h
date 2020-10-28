#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Missile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float speed;
	bool isFire;
	float angle;
	float destAngle;
	Enemy* target;
	float followRatio;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool fire) { isFire = fire; }

	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return this->pos; }

	void SetAngle(float angle) { this->angle = angle; }

	void SetTarget(Enemy* target) { this->target = target; }

	int GetSize() { return this->size; } 
	
	void SettingAngle(float angle);


	Missile();
	~Missile();
};

