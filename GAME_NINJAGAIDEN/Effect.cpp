#include "Effect.h"


Effect::Effect(float X, float Y)
{
	x = X;
	y = Y;
	type = eType::EFFECT;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new CSprite(texture, 70);
	isFinish = false;
}

Effect::~Effect()
{
}

//void Effect::GetBoundingBox(float & left, float & top, float & right, float & bottom)
//{
//	left = x;
//	top = y;
//	right = x + width;
//	bottom = y + height;
//}

void Effect::Update(DWORD dt)
{
	if (sprite->GetCurrentFrame() > 2)
		isFinish = true;
	sprite->Update(dt);

}

void Effect::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);

	RenderBoundingBox(camera);
}
