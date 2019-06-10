#ifndef __KATANA_H__
#define __KATANA_H__

#define KATANA_ANI_WAIT_TIME 120 // thời gian chờ chuyển frame của KATANA

#define KATANA_ANI_START 0
#define KATANA_ANI_END 2

#include "Weapon.h"
#include "GameObject.h" 
#include "TextureManager.h"
#include "debug.h"

class Katana : public Weapon
{
public:
	Katana();
	~Katana();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void Attack(float X, float Y, int Direction);
	bool ableCollision(GameObject* obj);
	void UpdatePositionFitCharacter(int state);
	void RenderIcon(float X, float Y);
};



#endif  
