#include "Butterfly.h"



Butterfly::~Butterfly()
{
}


Butterfly::Butterfly(int direction, float X, float Y,int item, int status)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::BUTTERFLY);
	sprite = new CSprite(texture, 100);
	this->x = X;
	this->y = Y;
	this->direction = direction;
	type = eType::BUTTERFLY;
	Health = 1;
	indexItem = item;
	this->status = status;
	isDropItem = false;

}



void Butterfly::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 5;
	top = y - 5;
	right = x + texture->GetFrameWidth() + 5;
	bottom = y + texture->GetFrameHeight() + 5; //Mở rộng BBOX cho dễ đánh trúng

}

void Butterfly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	sprite->Update(dt); // update animation
}

void Butterfly::Render(Camera * camera)
{
	if (status == INACTIVE)
		return;

		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);
}
