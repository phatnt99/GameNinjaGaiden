#include "Throwingstar.h"


Throwingstar::Throwingstar(float X, float Y)
{
	type = eType::THROWINGSTAR;
	texture = TextureManager::GetInstance()->GetTexture(eType::THROWINGSTAR);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = THROWINGSTAR_GRAVITY;
	TimeDisplayMax = THROWINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Throwingstar::Render(Camera * camera)
{
	if (isFinish)
		return;

	sprite->SelectFrame(0);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	//RenderBoundingBox(camera);
}

Throwingstar::~Throwingstar()
{
}
