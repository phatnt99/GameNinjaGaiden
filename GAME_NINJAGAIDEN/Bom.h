#ifndef __BOM_H__
#define __BOM_H__


#include "Weapon.h" 
#include "debug.h"
#define BOM_GRAVITY 0.008f

class Bom :
	public Weapon
{
private:


public:
	Bom();
	virtual ~Bom();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif#pragma once
