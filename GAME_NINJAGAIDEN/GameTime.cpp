#include "GameTime.h"



GameTime::GameTime()
{
	this->accumulationTime = 0;
	SetTime(0);
}


GameTime::~GameTime()
{
}

void GameTime::Update(DWORD dt)
{
	if (accumulationTime + dt < 1000)
	{
		accumulationTime += dt;
	}
	else
	{
		accumulationTime = (accumulationTime + dt) % 1000;
		time++;
		isJustChanged = true; // set trạng thái vừa thay đổi
	}
}

void GameTime::SetTime(int t)
{
	time = t;
}

int GameTime::GetTime()
{
	return time;
}

bool GameTime::CheckIsJustChanged()
{
	bool b = isJustChanged;
	isJustChanged = false; // sau khi lấy trạng thái xong rồi thì coi như "chưa thay đổi"
	return b;
}
