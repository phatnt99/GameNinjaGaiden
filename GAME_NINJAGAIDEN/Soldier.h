#pragma once
#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Enemy.h"
#include "debug.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Grid.h"
#define SOLDIER_SPEED_X 0.09f
#define SOLDIER_GRAVITY 0.05f
#define SOLDIER_ACTIVE_BBOX_WIDTH 268
#define SOLDIER_ACTIVE_BBOX_HEIGHT 200
#define SOLDIER_BBOX_WIDTH 40
#define SOLDIER_BBOX_HEIGHT 60

#define SOLDIER_ANI_WALKING_BEGIN 0
#define SOLDIER_ANI_WALKING_END 1
#define SOLDIER_ANI_ATTACK_BEGIN 2
#define SOLDIER_ANI_ATTACK_END 3
#define SOLDIER_DELTA_X 150

class Soldier : public Enemy
{
	int countAttack;
	vector<Bullet*> listWeapon;
	bool isWalking;
	bool isAttack;
	float borderLeft, borderRight;
	float oldX;
public:
	Soldier(int direction, float X, float Y, float BorderLeft, float BorderRight, int status);
	virtual ~Soldier();

	void Update(DWORD dt, float xNinja,Grid *grid, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	virtual void SetStatus(int s);
};


#endif  


