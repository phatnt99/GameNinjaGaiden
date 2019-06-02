#ifndef __THIEF_H__
#define __THIEF_H__


#define THIEF_SPEED_X 0.09f
#define THIEF_GRAVITY 0.005f
#define THIEF_ACTIVE_BBOX_WIDTH 268
#define THIEF_ACTIVE_BBOX_HEIGHT 200
#define THIEF_BBOX_WIDTH 46
#define THIEF_BBOX_HEIGHT 70

#include "Enemy.h"
#include "debug.h"
class Thief : public Enemy
{
	float borderLeft, borderRight;
public:
	Thief(int direction, float X, float Y, float BorderLeft, float BorderRight, int status);
	virtual ~Thief();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id);
	virtual void SetStatus(int s);
};


#endif  


