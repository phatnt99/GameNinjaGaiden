#pragma once
#ifndef __WPTHROWINGSTAR_H__
#define __WPTHROWINGSTAR_H__


#include "Weapon.h" 
#include "debug.h"
#define WPTHROWINGSTAR_GRAVITY 0.008f

class WPThrowingStar :
	public Weapon
{
private:
	CSprite *spriteIcon;
	static WPThrowingStar *Instance;

public:

	WPThrowingStar();
	virtual ~WPThrowingStar();
	static WPThrowingStar *getInstance();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif#pragma once

