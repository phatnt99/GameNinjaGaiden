#ifndef __TheBird_H__
#define __TheBird_H__


#include "Enemy.h"
#include "Item.h"
#include "Strength.h"
class TheBird : public Enemy
{
	int indexItem;
	bool isDropItem;
public:
	TheBird(int direction, float X, float Y, int item, int status);
	~TheBird();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetIndexItem() { return indexItem; };
	bool IsDropItem() { return isDropItem; };
	void SetDropItem(bool b) { isDropItem = b; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	virtual void GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id) {};
};


#endif

