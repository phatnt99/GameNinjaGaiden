#include "BoardHealth.h"



BoardHealth::BoardHealth(float X, float Y)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::BOARDHEALTH);
	sprite = new CSprite(texture, 0);
	this->x = X;
	this->y = Y;
}

BoardHealth::~BoardHealth()
{
	SAFE_DELETE(sprite);
}

void BoardHealth::Draw(int HealthNinja, int HealthEnemy)
{
	HealthNinja = min(HealthNinja, 16);
	HealthEnemy = min(HealthEnemy, 16);

	int i, j;
	sprite->SelectFrame(BOARDHEALTH_FRAME_PLAYER);
	for (i = 0; i < HealthNinja; i++)
		sprite->Draw(x + i*texture->GetFrameWidth(), y);

	sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j<BOARDHEALTH_MAX_CELL; j++)
	{
		sprite->Draw(x + j * texture->GetFrameWidth(), y);
	}

	sprite->SelectFrame(BOARDHEALTH_FRAME_PLAYER);
	for (i = 0; i < HealthEnemy; i++)
		sprite->Draw(x + i * texture->GetFrameWidth(), y + 17);

	sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		sprite->Draw(x + j * texture->GetFrameWidth(), y + 17);
	}

}

