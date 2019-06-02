#pragma once
#ifndef __THROWINGSTAR_H__
#define __THROWINGSTAR_H__


#define THROWINGSTAR_TIMEDISPLAYMAX 3000
#define THROWINGSTAR_GRAVITY 0.25f


#include "Item.h"
class Throwingstar : public Item
{
public:
	Throwingstar(float X, float Y);

	virtual void Render(Camera * camera);

	virtual ~Throwingstar();
};

#endif