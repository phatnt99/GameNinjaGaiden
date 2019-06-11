#include "Firewheel.h"


Firewheel::Firewheel(float X, float Y)
{
	type = eType::FIREWHEEL;
	texture = TextureManager::GetInstance()->GetTexture(eType::FIREWHEEL);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = FIREWHEEL_GRAVITY;
	TimeDisplayMax = FIREWHEEL_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Firewheel::Render(Camera * camera)
{
	if (isFinish)
		return;

	sprite->SelectFrame(0);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	//RenderBoundingBox(camera);
}

Firewheel::~Firewheel()
{
}
