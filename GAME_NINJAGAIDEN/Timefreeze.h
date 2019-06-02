#pragma once
#ifndef __TIMEFREEZE_H__
#define __TIMEFREEZE_H__


#define TIMEFREEZE_TIMEDISPLAYMAX 3000
#define TIMEFREEZE_GRAVITY 0.25f

#define TIMEFREEZE_ANI_FIVE 0
#define TIMEFREEZE_ANI_TEN 1



#include "Item.h"
class Timefreeze : public Item
{
public:
	Timefreeze(float X, float Y);

	virtual void Render(Camera * camera);

	virtual ~Timefreeze();
};

#endif