#include "WPWindmillStar.h"

WPWindmillStar * WPWindmillStar::Instance = NULL;

WPWindmillStar::WPWindmillStar()
{
	texture = TextureManager::GetInstance()->GetTexture(eType::WPWINDMILLSTAR);
	sprite = new CSprite(texture, 100);
	spriteIcon = new CSprite(TextureManager::GetInstance()->GetTexture(eType::WINDMILL), 0);
	type = eType::WPWINDMILLSTAR;
	
}

WPWindmillStar * WPWindmillStar::getInstance()
{
	if (Instance == NULL)
		Instance = new WPWindmillStar();
	return Instance;
}

WPWindmillStar::~WPWindmillStar()
{
}

void WPWindmillStar::UpdatePositionFitCharacter()
{

	if (direction == -1)
	{
		this->x = x - 30;
		this->y = y + 18;

	}
	else
	{
		this->x = x + 80;
		this->y = y + 18;
	}
}


void WPWindmillStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (!camera->CHECK_OBJECT_IN_CAMERA(this)) // ra khỏi cam thì kết thúc
	//{
	//	isFinish = true;
	//	return;
	//}
	if (isFinish)
		return;
	int delta;
		if (direction == -1)
			delta = DELTAX - 35;
		else
			delta = DELTAX;
	if (abs(x - xNinja) >= delta)
	{
		direction *= -1;
		vx *= direction;
		vy = 0;
		isReturn = true;
	}
	else
	{
		if (isReturn)
		{
			if (status == 1)
				vy = -0.05f;
			else if (status == 2)
				vy = 0.05f;
			else
				vy = 0;
		}

		if (isMiddle)
		{
			vy *= 1.6f;
		}

		if (abs(x - BackupX) <= 10)
		{
			isReturn = false;
			isMiddle = true;
		}
		else isMiddle = false;
	}

	//if (abs(x - BackupX) >= DELTA)
	//{
	//	direction *= -1;
	//	vx *= direction;
	//	index = 0;
	//	isReturn = true;
	//}
	//// xét trong khoảng nó return chỉ cần ninja thay đổi y sẽ bắt theo đúng 1 lần cả quá trình 
	//if (isReturn == true && yNinja + 18 < y) // Ninja đang nhảy
	//{
	//	vy = -0.06f; // nhảy theo
	//	//vy += -0.005f*dt;
	//	isReturn = false;
	//}
	//else if (isReturn == true && yNinja + 18 > y)
	//{
	//	vy = 0.06f;
	//	isReturn = false;
	//}

	//if (abs(x - BackupX) <= 10)
	//	isReturn = false;

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

void WPWindmillStar::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y, Direction);
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	UpdatePositionFitCharacter();
	sprite->SelectFrame(0);
	sprite->ResetTime();
}

void WPWindmillStar::RenderIcon(float X, float Y)
{
	spriteIcon->Draw(X, Y);
}


void WPWindmillStar::Render(Camera * camera)
{
	if (isFinish == true)
		return;


	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
	RenderBoundingBox(camera);
}
