#pragma once
#ifndef __WINDMILLSTAR_H__
#define __WINDMILLSTAR_H__


#define WINDMILLSTAR_TIMEDISPLAYMAX 3000
#define WINDMILLSTAR_GRAVITY 0.25f



#include "Item.h"
class Windmillstar : public Item
{
public:
	Windmillstar(float X, float Y);

	virtual void Render(Camera * camera);

	virtual ~Windmillstar();
};

#endif