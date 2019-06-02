#ifndef __Butterfly_H__
#define __Butterfly_H__


#include "Enemy.h"
#include "Item.h"
#include "Strength.h"
class Butterfly : public Enemy
{
	int indexItem;
	bool isDropItem;
public:
	Butterfly(int direction, float X, float Y,int item, int status);
	~Butterfly();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetIndexItem() { return indexItem; };
	bool IsDropItem() { return isDropItem; };
	void SetDropItem(bool b) { isDropItem = b; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id) {};
};


#endif

