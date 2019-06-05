#ifndef __WEAPON_H__
#define	__WEAPON_H__

#include "define.h"
#include "Camera.h"
#include "Texture.h"
#include "Sprite.h" 
#include "GameObject.h"


class Weapon : public GameObject
{
protected:
	bool isFinish;
	DWORD LastTimeAttack;

	// Thời điểm tấn công cuối cùng

public:
	Weapon();
	~Weapon();
	bool isAttacked;
	int GetDirection();
	void SetDirection(int Direction);
	virtual void Attack(float X, float Y, int Direction);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Camera *camera);
	virtual void UpdatePositionFitCharacter();
	virtual void RenderIcon(float X, float Y) = 0;
	virtual bool ableCollision(GameObject* obj);
	bool GetFinish();

	void SetFinish(bool b);

	DWORD GetLastTimeAttack();

};



#endif