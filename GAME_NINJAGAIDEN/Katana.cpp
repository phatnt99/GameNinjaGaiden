#include "Katana.h"



Katana::Katana()
{
	type = eType::KATANA;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new CSprite(texture, KATANA_ANI_WAIT_TIME);
	isAttacked = false;
}


Katana::~Katana()
{
}

void Katana::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"\nxKatana = %f\n", x);
	GameObject::Update(dt);

	// update for check collision
	
	isFinish = sprite->GetCurrentFrame() == 3;
	int StartFrame = KATANA_ANI_START; // ánh xạ chỉ số frame bằng level thay vì ifelse 
	int EndFrame = 3;

	if (StartFrame <= sprite->GetCurrentFrame() && sprite->GetCurrentFrame() < EndFrame)
		sprite->Update(dt);
	else
	{
		sprite->SelectFrame(StartFrame);
	}

}

void Katana::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (direction == 1)
	{
		left = x + 30;
		top = y + 20;
		right = left + 42;
		bottom = top + 25;
	}
	else
	{
		left = x;
		top = y + 20;
		right = left + 35;
		bottom = top + 25;
	}
}
void Katana::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);
	RenderBoundingBox(camera);
}

bool Katana::ableCollision(GameObject* obj)
{
	if (sprite->GetCurrentFrame() == KATANA_ANI_START)
		return false;
	return Weapon::ableCollision(obj);
}

void Katana::Attack(float X, float Y, int Direction)
{

	Weapon::Attack(X, Y, Direction);
	//UpdatePositionFitCharacter();
	sprite->SelectFrame(KATANA_ANI_START);
	sprite->ResetTime();
}

void Katana::UpdatePositionFitCharacter(int state)
{
	if (state == 0)// đang đứng
	{
		if (direction == -1)
		{
			this->x = x - 20;
			this->y = y - 1;

		}
		else
		{
			this->x = x + 20;
			this->y = y - 1;
		}
	}
	else //ngồi
	{
		if (direction == -1)
		{
			this->x = x - 20;
			this->y = y + 10;

		}
		else
		{
			this->x = x + 20;
			this->y = y + 10;
		}
	}

}

void Katana::RenderIcon(float X, float Y)
{
}
