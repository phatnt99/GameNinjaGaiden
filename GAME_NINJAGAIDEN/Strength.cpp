#include "Strength.h"


Strength::Strength(float X, float Y, eType TypeStrength)
{
	type = TypeStrength;
	texture = TextureManager::GetInstance()->GetTexture(eType::STRENGTH);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = STRENGTH_GRAVITY;
	TimeDisplayMax = STRENGTH_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Strength::Render(Camera * camera)
{
	if (isFinish)
		return;
	switch (type)
	{
	case eType::STRENGTH_5:
		sprite->SelectFrame(STRENGTH_ANI_FIVE);
		break;

	case eType::STRENGTH_10:
		sprite->SelectFrame(STRENGTH_ANI_TEN);
		break;

		break;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	RenderBoundingBox(camera);
}

Strength::~Strength()
{
}
