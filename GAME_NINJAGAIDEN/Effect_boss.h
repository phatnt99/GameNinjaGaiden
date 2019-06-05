#pragma once
#include "GameObject.h"

#define EFFECT_BOSS_BEGIN 0
#define EFFECT_BOSS_END 2

class Effect_boss : public GameObject
{
private:
	bool isFinish;
public:
	Effect_boss(float X, float Y);
	~Effect_boss();

	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render(Camera * camera);
	bool IsFinish() { return isFinish; };
};

