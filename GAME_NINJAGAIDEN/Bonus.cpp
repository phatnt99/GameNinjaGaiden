#include "Bonus.h"


Bonus::Bonus(float X, float Y, eType TypeBonus)
{
	type = TypeBonus;
	texture = TextureManager::GetInstance()->GetTexture(eType::BONUS);
	sprite = new CSprite(texture, 0);

	this->x = X;
	this->y = Y;

	vx = 0;

	vy = BONUS_GRAVITY;
	TimeDisplayMax = BONUS_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

void Bonus::Render(Camera * camera)
{
	if (isFinish)
		return;
	switch (type)
	{
	case eType::BONUS_5:
		sprite->SelectFrame(BONUS_ANI_FIVE);
		break;

	case eType::BONUS_10:
		sprite->SelectFrame(BONUS_ANI_TEN);
		break;

		break;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	RenderBoundingBox(camera);
}

Bonus::~Bonus()
{
}
