#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Grid.h"
#include <cstdlib>
#include <ctime>

class Enemy : public GameObject
{
protected:
	int status;
	int backupDirection;
public:

	int GetStatus();
	void SubHealth(int h);
	virtual void SetStatus(int s);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id) = 0;

};
