#include "Effect_boss.h"


Effect_boss::Effect_boss(float X, float Y)
{
	x = X;
	y = Y;
	type = eType::EFFECT_BOSS;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new CSprite(texture, 200);
	isFinish = false;
}

Effect_boss::~Effect_boss()
{
}

//void Effect_boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
//{
//	left = x;
//	top = y;
//	right = x + width;
//	bottom = y + height;
//}

void Effect_boss::Update(DWORD dt)
{
	if (isFinish == true)
		return;
	int index = sprite->GetCurrentFrame();
	if (index < EFFECT_BOSS_BEGIN) // nếu ani chưa đúng
	{
		sprite->SelectFrame(EFFECT_BOSS_BEGIN); // set lại ani bắt đầu
		sprite->timeAccumulated = dt;
	}
	else
	{
		/* Update ani bình thường */
		sprite->timeAccumulated += dt;
		if (sprite->timeAccumulated >= 200)
		{
			sprite->timeAccumulated -= 200;
			sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
		}
		/* Update ani bình thường */

		if (sprite->GetCurrentFrame() > EFFECT_BOSS_END) // đã đi vượt qua frame cuối
		{
			sprite->SelectFrame(EFFECT_BOSS_BEGIN);
			isFinish = true;
		}
	}
}

void Effect_boss::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	//RenderBoundingBox(camera);
}
