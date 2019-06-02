#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "Sprite.h"
#include "Camera.h"
#include "Texture.h"
#include "GameObject.h" 
#include "define.h" 
#include "Sprite.h"

class Item : public GameObject
{
protected:

	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.


	bool isFinish; // đã kết thúc chưa?

public:
	Item();
	virtual ~Item();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);
	virtual bool isWaitingDisplay(); // đang chờ object hiển thi? - simon chưa được ăn

	bool GetFinish();
	void SetFinish(bool b);
};



#endif // !__ITEM_H__




