#include "Restore.h"


Restore::Restore(float X, float Y)
{
	type = eType::RESTORE;
	texture = TextureManager::GetInstance()->GetTexture(eType::RESTORE);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = RESTORE_GRAVITY;
	TimeDisplayMax = RESTORE_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Restore::Render(Camera * camera)
{
	if (isFinish)
		return;

	sprite->SelectFrame(0);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	//RenderBoundingBox(camera);
}

Restore::~Restore()
{
}
