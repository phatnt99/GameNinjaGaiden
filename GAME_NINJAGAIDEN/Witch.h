#ifndef __WITCH_H__
#define __WITCH_H__


#define WITCH_SPEED_X 0.05f
#define WITCH_GRAVITY 0.005f
#define WITCH_ACTIVE_BBOX_WIDTH 268
#define WITCH_ACTIVE_BBOX_HEIGHT 200
#define WITCH_BBOX_WIDTH 60
#define WITCH_BBOX_HEIGHT 77


#include "Enemy.h"
#include "Weapon.h"
#include "Sword.h"

#define WITCH_ANI_WALKING_BEGIN 0
#define WITCH_ANI_WALKING_END 1
#define WITCH_ANI_ATTACK 2


class Witch : public Enemy
{
public:
	vector<Sword*> listWeapon;
	bool isWalking;
	bool isAttack;
	float borderLeft, borderRight;
	Witch(int direction, float X, float Y, float BorderLeft, float BorderRight, int status);
	virtual ~Witch();

	void Update(DWORD dt, float xNinja,Grid *grid, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	void SetStatus(int s);
};


#endif  


