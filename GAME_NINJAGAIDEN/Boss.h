#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#include "Enemy.h"
#include "debug.h"
#include "Weapon.h"
#include "Bom.h"
#include "Grid.h"
#include "Effect_boss.h"
#include "Sound.h"
#define BOSS_SPEED_X 0.09f
#define BOSS_GRAVITY 0.009f
#define BOSS_ACTIVE_BBOX_WIDTH 500
#define BOSS_ACTIVE_BBOX_HEIGHT 200
#define BOSS_BBOX_WIDTH 82
#define BOSS_BBOX_HEIGHT 115

#define BOSS_ANI_JUMP 0
#define BOSS_ANI_IDLE 1
#define TIME_WAIT 2000
#define TIME_DEATH 3000

class Boss : public Enemy
{
	list<Weapon*> Weapon;
	bool isIdle;
	bool isJumping;
	bool isDeath;
	bool isFinish;
	int directX;
	int count = 0;
	DWORD start;
	DWORD startDeath;
	Sound *sound;
	list<Effect_boss*> listEffect;
public:
	Boss(int direction, float X, float Y, int status);
	virtual ~Boss();

	bool GetIsDeath() { return isDeath; }
	void SetIsDeath(bool d) { isDeath = d; }
	void Update(DWORD dt, float xNinja, Grid *grid, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	virtual void SetStatus(int s);
};


#endif  


