#pragma once
#include "GameObject.h"
class Effect : public GameObject
{
private:
	bool isFinish;
public:
	Effect(float X, float Y);
	~Effect();

	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render(Camera * camera);
	bool IsFinish() { return isFinish; };
};

