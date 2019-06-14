#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include "define.h"

class GameTime
{
private:
	DWORD accumulationTime; // thời gian đã tích lũy
	int time; // time game 

public:
	GameTime();
	~GameTime();
	void Update(DWORD dt);
	void SetTime(int t);
	int GetTime();
};




#endif 

