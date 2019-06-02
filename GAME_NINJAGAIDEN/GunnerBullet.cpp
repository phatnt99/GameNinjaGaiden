#include "GunnerBullet.h"



GunnerBullet::GunnerBullet()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::GUNNERBULLET);
	sprite = new CSprite(texture, 100);
	type = eType::GUNNERBULLET;
}


GunnerBullet::~GunnerBullet()
{
}

void GunnerBullet::UpdatePositionFitCharacter()
{

	if (direction == -1)
	{
		this->x = x - 13;
		this->y = y + 13;

	}
	else
	{
		this->x = x + 60;
		this->y = y + 13;
	}
}


void GunnerBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish) // ra khỏi cam thì kết thúc
	{
		return;
	}
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
	}

}

void GunnerBullet::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void GunnerBullet::RenderIcon(float X, float Y)
{
}


void GunnerBullet::Render(Camera * camera)
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
