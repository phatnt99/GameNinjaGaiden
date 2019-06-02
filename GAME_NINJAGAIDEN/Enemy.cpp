#include "Enemy.h"

void Enemy::SetStatus(int s)
{
	status = s;
}

int Enemy::GetStatus()
{
	return status;
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt, coObject);
}

void Enemy::SubHealth(int h)
{
	GameObject::SubHealth(h);
	if (Health <= 0)
		SetStatus(INACTIVE);

}