#pragma once
#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "Enemy.h"
#include "debug.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Grid.h"
#include "Brick.h"
#include "ObjectHidden.h"
#define RUNNER_SPEED_X 0.24f
#define RUNNER_GRAVITY 0.008f
#define RUNNER_ACTIVE_BBOX_WIDTH 268
#define RUNNER_ACTIVE_BBOX_HEIGHT 200
#define RUNNER_BBOX_WIDTH 40
#define RUNNER_BBOX_HEIGHT 57

#define RUNNER_ANI_WALKING_BEGIN 0
#define RUNNER_ANI_WALKING_END 1
#define RUNNER_ANI_JUMPING 1
#define RUNNER_DELTA_X 150

class Runner : public Enemy
{
	vector<Bullet*> listWeapon;
	bool isWalking;
	bool isJumping;
	bool isClimbing;
	float borderLeft, borderRight;
	float oldX;
	int id = 0;
	int flag = 0;
public:
	Runner(int direction, float X, float Y, int status);
	virtual ~Runner();

	void Update(DWORD dt, float xNinja, Grid *grid, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	virtual void SetStatus(int s);
};


#endif  


