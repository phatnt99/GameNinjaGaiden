#ifndef __DOG_H__
#define __DOG_H__


#define DOG_SPEED_X 0.2f
#define DOG_GRAVITY 0.002f
#define DOG_ACTIVE_BBOX_WIDTH 250
#define DOG_ACTIVE_BBOX_HEIGHT 200

#include "Enemy.h"
class Dog : public Enemy
{
public:
	float backupY;
	bool isJumping;
	Dog(int Direction, float X, float Y, int status);
	virtual ~Dog();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	virtual void SetStatus(int s);
};


#endif  


