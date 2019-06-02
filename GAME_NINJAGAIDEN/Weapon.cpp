#include "Weapon.h"



Weapon::Weapon()
{
	type = eType::WEAPON;
	isFinish = 1;
}


Weapon::~Weapon()
{
}

int Weapon::GetDirection()
{
	return direction;
}

void Weapon::SetDirection(int Direction)
{
	this->direction = Direction;
}

void Weapon::Attack(float X, float Y, int Direction)
{
	this->x = X;
	this->y = Y;
	this->direction = Direction;
	isFinish = false; // chưa kết thúc

	LastTimeAttack = GetTickCount(); // lưu lại thời điểm lúc vừa tấn công, làm đánh dấu tránh 1 hit đánh nhiều lần cho các object, có health >1.
}
bool Weapon::ableCollision(GameObject* obj)
{
	//if (isFinish)
	//	return false;
	return isCollitionObjectWithObject(obj);
}

void Weapon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + texture->GetFrameWidth();
	bottom = top + texture->GetFrameHeight();
}

void Weapon::Render(Camera * camera)
{
	if (isFinish)
		return;

	//DebugOut(L"WEAPON: index = %d \n", sprite->GetCurrentFrame());
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
}

void Weapon::UpdatePositionFitCharacter()
{
}

bool Weapon::GetFinish()
{
	return isFinish;
}

void Weapon::SetFinish(bool b)
{
	isFinish = b;
}

DWORD Weapon::GetLastTimeAttack()
{
	return LastTimeAttack;
}
