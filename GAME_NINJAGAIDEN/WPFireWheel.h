#pragma once
#pragma once
#ifndef __WPFIREWHEEL_H__
#define __WPFIREWHEEL_H__


#include "Weapon.h" 
#include "debug.h"
#define WPFIREWHEEL_GRAVITY 0.008f

class WPFireWheel :
	public Weapon
{
private:
	CSprite *spriteIcon;
	static WPFireWheel *Instance;

public:
	WPFireWheel();
	virtual ~WPFireWheel();
	static WPFireWheel  *getInstance();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif#pragma once

