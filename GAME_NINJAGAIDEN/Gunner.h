#pragma once
#ifndef __GUNNER_H__
#define __GUNNER_H__

#include "Enemy.h"
#include "debug.h"
#include "Weapon.h"
#include "GunnerBullet.h"
#include "Grid.h"
#include "Sound.h"
#define GUNNER_GRAVITY 0.05f
#define GUNNER_ACTIVE_BBOX_WIDTH 268
#define GUNNER_ACTIVE_BBOX_HEIGHT 200
#define GUNNER_BBOX_WIDTH 40
#define GUNNER_BBOX_HEIGHT 60

#define GUNNER_ANI_ATTACK_BEGIN 0
#define GUNNER_ANI_ATTACK_END 1
#define GUNNER_DELTA_X 150

class Gunner : public Enemy
{
	vector<GunnerBullet*> listWeapon;
	Sound *sound;
	bool isAttack;
	int i = 1;
public:
	Gunner(int direction, float X, float Y, int status);
	virtual ~Gunner();

	void Update(DWORD dt, float xNinja, Grid *grid, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	virtual void SetStatus(int s);
};


#endif  


