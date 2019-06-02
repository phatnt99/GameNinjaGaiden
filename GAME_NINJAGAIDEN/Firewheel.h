#pragma once
#ifndef __FIREWHEEL_H__
#define __FIREWHEEL_H__


#define FIREWHEEL_TIMEDISPLAYMAX 3000
#define FIREWHEEL_GRAVITY 0.25f

#define FIREWHEEL_ANI_FIVE 0
#define FIREWHEEL_ANI_TEN 1



#include "Item.h"
class Firewheel : public Item
{
public:
	Firewheel(float X, float Y);

	virtual void Render(Camera * camera);

	virtual ~Firewheel();
};

#endif