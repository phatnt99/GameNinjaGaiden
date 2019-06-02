#ifndef __SWORD_H__
#define __SWORD_H__


#include "Weapon.h" 
#include "debug.h"
#define SWORD_GRAVITY 0.002f

class Sword :
	public Weapon
{
private:


public:
	Sword ();
	virtual ~Sword();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(float X, float Y, int Direction);
	void RenderIcon(float X, float Y);
	void UpdatePositionFitCharacter();
	void Render(Camera *camera);

};




#endif