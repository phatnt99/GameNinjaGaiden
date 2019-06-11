#include "Windmillstar.h"


Windmillstar::Windmillstar(float X, float Y)
{
	type = eType::WINDMILL;
	texture = TextureManager::GetInstance()->GetTexture(eType::WINDMILL);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = WINDMILLSTAR_GRAVITY;
	TimeDisplayMax = WINDMILLSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Windmillstar::Render(Camera * camera)
{
	if (isFinish)
		return;

	sprite->SelectFrame(0);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	//RenderBoundingBox(camera);
}

Windmillstar::~Windmillstar()
{
}
