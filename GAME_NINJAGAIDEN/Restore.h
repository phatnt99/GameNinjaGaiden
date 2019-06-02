#pragma once
#ifndef __RESTORE_H__
#define __RESTORE_H__


#define RESTORE_TIMEDISPLAYMAX 3000
#define RESTORE_GRAVITY 0.25f



#include "Item.h"
class Restore : public Item
{
public:
	Restore(float X, float Y);

	virtual void Render(Camera * camera);

	virtual ~Restore();
};

#endif