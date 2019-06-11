#include "WPFireWheel.h"

WPFireWheel * WPFireWheel::Instance = NULL;

WPFireWheel::WPFireWheel()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::WPFIREWHEEL);
	sprite = new CSprite(texture, 100);
	type = eType::WPFIREWHEEL;
	spriteIcon = new CSprite(TextureManager::GetInstance()->GetTexture(eType::FIREWHEEL), 0);
}

WPFireWheel * WPFireWheel::getInstance()
{
	if (Instance == NULL)
		Instance = new WPFireWheel();
	return Instance;
}

WPFireWheel::~WPFireWheel()
{
}

void WPFireWheel::UpdatePositionFitCharacter()
{

	if (direction == -1)
	{
		this->x = x;
		this->y = y;

	}
	else
	{
		this->x = x ;
		this->y = y ;
	}
}


void WPFireWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void WPFireWheel::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void WPFireWheel::RenderIcon(float X, float Y)
{
	spriteIcon->Draw(X, Y);
}


void WPFireWheel::Render(Camera * camera)
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
