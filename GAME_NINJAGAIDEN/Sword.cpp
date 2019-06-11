#include "Sword.h"



Sword::Sword()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::SWORD);
	sprite = new CSprite(texture, 100);
	type = eType::SWORD;
}


Sword::~Sword()
{
}

void Sword::UpdatePositionFitCharacter()
{

	if (direction == -1)
	{
		this->x = x - 7;
		this->y = y - 10;

	}
	else
	{
		this->x = x + 7;
		this->y = y - 10;
	}
}


void Sword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (!camera->CHECK_OBJECT_IN_CAMERA(this)) // ra khỏi cam thì kết thúc
	//{
	//	isFinish = true;
	//	return;
	//}
	//if (isFinish)
	//	return;
	vy += SWORD_GRAVITY;
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

void Sword::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void Sword::RenderIcon(float X, float Y)
{
}


void Sword::Render(Camera * camera)
{
	if (isFinish)
		return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
	//RenderBoundingBox(camera);
}
