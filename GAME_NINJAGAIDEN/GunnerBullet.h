#ifndef __GUNNERBULLET_H__
#define __GUNNERBULLET_H__


#include "Weapon.h" 
#include "debug.h"
#define GUNNERBULLET_GRAVITY 0.008f

class GunnerBullet :
	public Weapon
{
private:


public:
	GunnerBullet();
	virtual ~GunnerBullet();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif#pragma once
