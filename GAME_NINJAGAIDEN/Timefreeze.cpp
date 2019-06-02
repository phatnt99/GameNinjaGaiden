#include "Timefreeze.h"


Timefreeze::Timefreeze(float X, float Y)
{
	type = eType::TIMEFREEZE;
	texture = TextureManager::GetInstance()->GetTexture(eType::TIMEFREEZE);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = TIMEFREEZE_GRAVITY;
	TimeDisplayMax = TIMEFREEZE_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Timefreeze::Render(Camera * camera)
{
	if (isFinish)
		return;

	sprite->SelectFrame(0);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	RenderBoundingBox(camera);
}

Timefreeze::~Timefreeze()
{
}
