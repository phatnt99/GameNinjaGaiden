#include "Bom.h"



Bom::Bom()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::BOM);
	sprite = new CSprite(texture, 100);
	type = eType::BOM;
}


Bom::~Bom()
{
}

void Bom::UpdatePositionFitCharacter()
{
	this->x = x + 13;
	this->y = y + 13;
	/*if (direction == -1)
	{
		this->x = x + 13;
		this->y = y + 13;

	}
	else
	{
		this->x = x + 13;
		this->y = y + 13;
	}*/
}


void Bom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void Bom::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void Bom::RenderIcon(float X, float Y)
{
}


void Bom::Render(Camera * camera)
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
