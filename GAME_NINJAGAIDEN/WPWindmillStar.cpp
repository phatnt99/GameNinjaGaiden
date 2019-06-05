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

	delta = abs(xNinja - xStart) + 200;
	//DebugOut(L"STAR backupX =%f\t backupY = %f\n", BackupX, backupY);
	if (abs(x - xNinja) >= DELTAX && abs(x - xNinja) < DELTAX + 15)
	{
		DebugOut(L"VO");
		xStart = x;
		direction *= -1;
		vx *= direction;
		vy = 0;
	}
	else
	{

		if (backupDirection == 1)
		{
			if (x < BackupX && direction == -1 && y > backupY)
			{
				vy -= 0.0008f * dt;
			}
			else if (x > BackupX && direction == 1 && y < backupY)
			{
				//DebugOut(L"VO");
				vy += 0.0008f * dt;
			
			}
			else if (y < backupY - 100)
			{
				vy += 0.0008f * dt;

			}
		}
		else
		{
			if (x > BackupX && direction == 1 && y > backupY)
			{
				vy -= 0.0008f * dt;
			}
			else if (x < BackupX && direction == -1 && y < backupY)
			{
				vy += 0.0008f * dt;
			}
			else if (y < backupY - 100)
			{
				vy += 0.0008f * dt;

			}
		}
	}


		//if (abs(x - BackupX) >= DELTAX)
		//{
		//	direction *= -1;
		//	vx *= direction;
		//	index = 0;
		//	isReturn = true;
		//}
		//// xét trong khoảng nó return chỉ cần ninja thay đổi y sẽ bắt theo đúng 1 lần cả quá trình 
		//if (isReturn == true && yNinja + 18 < y) // Ninja đang nhảy
		//{
		//	//vy = -0.06f; // nhảy theo
		//	//vy += -0.005f*dt;
		//	if (backupDirection == 1)
		//	{
		//		if (x < BackupX && direction == -1)
		//		{
		//			vy -= 0.0008f * dt;
		//		}
		//		else if (x > BackupX && direction == 1 && y < backupY)
		//		{
		//			//DebugOut(L"VO");
		//			vy += 0.0008f * dt;
		//		}
		//	}
		//	else
		//	{
		//		if (x > BackupX && direction == 1)
		//		{
		//			vy -= 0.0008f * dt;
		//		}
		//		else if (x < BackupX && direction == -1 && y < backupY)
		//		{
		//			vy += 0.0008f * dt;
		//		}
		//	}

		//}
		//else if (isReturn == true && yNinja + 18 > y)
		//{
		//	if (backupDirection == 1)
		//	{
		//		if (x < BackupX && direction == -1)
		//		{
		//			vy -= 0.0008f * dt;
		//		}
		//		else if (x > BackupX && direction == 1 && y < backupY)
		//		{
		//			//DebugOut(L"VO");
		//			vy += 0.0008f * dt;
		//		}
		//	}
		//	else
		//	{
		//		if (x > BackupX && direction == 1)
		//		{
		//			vy -= 0.0008f * dt;
		//		}
		//		else if (x < BackupX && direction == -1 && y < backupY)
		//		{
		//			vy += 0.0008f * dt;
		//		}
		//	}


		//}

		//if (abs(x - BackupX) <= 10)
		//	isReturn = false;

		//DebugOut(L"index =%f\t vy = %f\n", index, vy);
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
	BackupX = xStart = x;
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
