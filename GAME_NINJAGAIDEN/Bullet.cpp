#include "Bullet.h"



Bullet::Bullet()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::BULLET);
	sprite = new CSprite(texture, 100);
	type = eType::BULLET;
}


Bullet::~Bullet()
{
}

void Bullet::UpdatePositionFitCharacter()
{

	if (direction == -1)
	{
		this->x = x - 13;
		this->y = y + 13;

	}
	else
	{
		this->x = x + 13;
		this->y = y + 13;
	}
}


void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (!camera->CHECK_OBJECT_IN_CAMERA(this)) // ra khỏi cam thì kết thúc
	//{
	//	isFinish = true;
	//	return;
	//}
	if (isFinish)
		return;
	GameObject::Update(dt); // update dt,dx,dy 
	x += dx;
	y += dy;
	int StartFrame = 0; // ánh xạ chỉ số frame bằng level thay vì ifelse 
	int EndFrame = 5;


	if (StartFrame <= sprite->GetCurrentFrame() && sprite->GetCurrentFrame() < EndFrame)
		sprite->Update(dt);
	else
	{
		sprite->SelectFrame(StartFrame);
		isFinish = true;
	}

}

void Bullet::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void Bullet::RenderIcon(float X, float Y)
{
}


void Bullet::Render(Camera * camera)
{
	if (isFinish)
		return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
	RenderBoundingBox(camera);
}
