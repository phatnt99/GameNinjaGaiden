#pragma once
#ifndef __STRENGTH_H__
#define __STRENGTH_H__


#define STRENGTH_TIMEDISPLAYMAX 3000
#define STRENGTH_GRAVITY 0.25f

#define STRENGTH_ANI_FIVE 0
#define STRENGTH_ANI_TEN 1



#include "Item.h"
class Strength : public Item
{
public:
	Strength(float X, float Y, eType TypeStrength);

	virtual void Render(Camera * camera);

	virtual ~Strength();
};

#endif