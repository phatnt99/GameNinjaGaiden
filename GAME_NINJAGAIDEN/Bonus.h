#pragma once
#ifndef __BONUS_H__
#define __BONUS_H__


#define BONUS_TIMEDISPLAYMAX 3000
#define BONUS_GRAVITY 0.25f

#define BONUS_ANI_FIVE 0
#define BONUS_ANI_TEN 1



#include "Item.h"
class Bonus : public Item
{
public:
	Bonus(float X, float Y, eType TypeBonus);

	virtual void Render(Camera * camera);

	virtual ~Bonus();
};

#endif#pragma once
