#include "WPThrowingStar.h"

WPThrowingStar * WPThrowingStar::Instance = NULL;

WPThrowingStar::WPThrowingStar()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::WPTHROWINGSTAR);
	sprite = new CSprite(texture, 100);
	spriteIcon = new CSprite(TextureManager::GetInstance()->GetTexture(eType::THROWINGSTAR), 0);
	type = eType::WPTHROWINGSTAR;
}

WPThrowingStar * WPThrowingStar::getInstance()
{
	if (Instance == NULL)
		Instance = new WPThrowingStar();
	return Instance;
}

WPThrowingStar::~WPThrowingStar()
{
}

void WPThrowingStar::UpdatePositionFitCharacter()
{

	if (direction == -1)
	{
		this->x = x - 13;
		this->y = y + 18;

	}
	else
	{
		this->x = x + 43;
		this->y = y + 18;
	}
}


void WPThrowingStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void WPThrowingStar::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void WPThrowingStar::RenderIcon(float X, float Y)
{
	spriteIcon->Draw(X, Y);
}


void WPThrowingStar::Render(Camera * camera)
{
	if (isFinish == true)
		return;


	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
	//RenderBoundingBox(camera);
}
