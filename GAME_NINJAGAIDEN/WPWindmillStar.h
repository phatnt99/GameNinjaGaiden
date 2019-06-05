#pragma once
#ifndef __WPWINDMILLSTAR_H__
#define __WPWINDMILLSTAR_H__


#include "Weapon.h" 
#include "debug.h"
#define WPWINDMILLSTAR_GRAVITY 0.008f
#define DELTAX 200
#define DELTAY 100

class WPWindmillStar :
	public Weapon
{
private:
	CSprite *spriteIcon;
	static WPWindmillStar *Instance;
	//int xNinja, yNinja;
	float v = 0;
	float delta = 0;
	float index = 0;
	float flag = 0;
public:
	float yNinja, xNinja, xStart;
	bool isReturn;
	WPWindmillStar();
	virtual ~WPWindmillStar();
	static WPWindmillStar *getInstance();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif#pragma once

