#include "TheBird.h"



TheBird::~TheBird()
{
}


TheBird::TheBird(int direction, float X, float Y, int item, int status)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::THEBIRD);
	sprite = new CSprite(texture, 150);
	this->x = X;
	this->y = Y;
	this->direction = direction;
	type = eType::THEBIRD;
	Health = 1;
	indexItem = item;
	this->status = status;
	isDropItem = false;

}



void TheBird::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 5;
	top = y - 5;
	right = x + texture->GetFrameWidth() + 5;
	bottom = y + texture->GetFrameHeight() + 5; //Mở rộng BBOX cho dễ đánh trúng

}

void TheBird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	sprite->Update(dt); // update animation
}

void TheBird::Render(Camera * camera)
{
	if (status == INACTIVE)
		return;

	//RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);
}
