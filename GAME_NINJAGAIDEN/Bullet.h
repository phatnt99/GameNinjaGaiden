#ifndef __BULLET_H__
#define __BULLET_H__


#include "Weapon.h" 
#include "debug.h"
#define BULLET_GRAVITY 0.008f

class Bullet :
	public Weapon
{
private:


public:
	Bullet();
	virtual ~Bullet();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif#pragma once
