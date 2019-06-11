#include "Witch.h"



Witch::Witch(int direction, float X, float Y, float BorderLeft, float BorderRight, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	borderLeft = BorderLeft;
	borderRight = BorderRight;
	this->status = status;
	BackupX = x;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::WITCH);
	sprite = new CSprite(texture, 200);

	Health = 1; // sét máu
	type = eType::WITCH;
	vx = WITCH_SPEED_X* this->direction;
	isWalking = true;
	isAttack = false;
}

Witch::~Witch()
{
}

void Witch::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		isWalking = true;
		isAttack = false;
		break;
	case DEATH:

		break;
	case INACTIVE:
		x = BackupX;
		direction = backupDirection;
		vx = WITCH_SPEED_X * direction;
		isWalking = false;
		break;
	default:
		break;
	}
}

void Witch::Update(DWORD dt, float xNinja,Grid *grid, vector<LPGAMEOBJECT>* coObjects)
{
	if (status == INACTIVE)
		return;
	if (this->x < xNinja)
		direction = 1;
	else
		direction = -1;

	//if (status == DEATH)
	//{
	//	this->SetStatus(INACTIVE);
	//	return;
	//}
	if (this->GetX() <= borderLeft)
	{
		vx = WITCH_SPEED_X;

		srand(time(NULL));
		if (rand() % 2)
		{
			isAttack = true;
			Sword* sword = new Sword();
			int a = rand() % 3 + 1;
			if (a == 1)
			{
				sword->SetSpeed(0.02f * direction, -0.07f);
			}
			else if (a == 2)
				sword->SetSpeed(0.06f * direction, -0.09f);
			else
				sword->SetSpeed(0.15f * direction, -0.15f);
			sword->Attack(x, y, this->direction);
			listWeapon.push_back(sword);
			Unit * unit = new Unit(grid, sword, sword->GetX(), sword->GetY());
		}
		//isWalking = false;
		//DebugOut(L"%d\n", direction);

	}
	else if (this->GetX() >= borderRight)
	{
		vx = -WITCH_SPEED_X;
		srand(time(NULL));
		if (rand() % 2)
		{
			isAttack = true;
			Sword* sword = new Sword();
			int a = rand() % 3 + 1;
			if (a == 1)
			{
				sword->SetSpeed(0.02f * direction, -0.07f);
			}
			else if (a == 2)
				sword->SetSpeed(0.06f * direction, -0.09f);
			else
				sword->SetSpeed(0.15f * direction, -0.15f);
			sword->Attack(x, y, this->direction);
			listWeapon.push_back(sword);
			Unit * unit = new Unit(grid, sword, sword->GetX(), sword->GetY());
		}
	}

	int index = sprite->GetCurrentFrame();
	if (isWalking)
	{
		if (isAttack)
		{

			if (index < WITCH_ANI_ATTACK)
			{
				sprite->SelectFrame(WITCH_ANI_ATTACK);
				sprite->timeAccumulated = dt;
			}
			else
			{
				sprite->timeAccumulated += dt;
				if (sprite->timeAccumulated >= 200)
				{
					sprite->timeAccumulated -= 200;
					sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
				}
				if (sprite->GetCurrentFrame() > WITCH_ANI_ATTACK)
				{
					isAttack = false;
					sprite->SelectFrame(WITCH_ANI_WALKING_BEGIN);
				}
			}
		}
		
		else
		{
			if (index < WITCH_ANI_WALKING_BEGIN)
			{
				sprite->SelectFrame(WITCH_ANI_WALKING_BEGIN);
				sprite->timeAccumulated = dt;
			}
			else
			{
				sprite->timeAccumulated += dt;
				if (sprite->timeAccumulated >= 200)
				{
					sprite->timeAccumulated -= 200;
					sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
				}
				/* Update ani bình thường */

				if (sprite->GetCurrentFrame() > WITCH_ANI_WALKING_END) // đã đi vượt qua frame cuối
				{
					//mapWeapon[TypeWeaponCollect]->Start(this->x, this->y);
					sprite->SelectFrame(WITCH_ANI_WALKING_BEGIN);
				}
			}
		}
	}
	//else if (isAttack)
	//{
	//	sprite->SelectFrame(WITCH_ANI_ATTACK);
	//	sprite->Update(dt);

	//	isAttack = false;
	//	isWalking = true;

	//}
	

	Enemy::Update(dt);

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK)
			listObject_Brick.push_back(coObjects->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents, 0); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
		vy += WITCH_GRAVITY*dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		/*if (nx != 0)
		{
		vx *= -1;
		direction *= -1;
		}*/

		//if (ny != 0)
		//{
		//	vy = 0;
		//	vx = 0;
		//}

		if (ny == -1.0f)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	for (auto sword : listWeapon)
	{
		if (!sword->GetFinish())
		{

			sword->Update(dt, coObjects);
		}
	}

}

void Witch::Render(Camera * camera)
{
	if (this->status == INACTIVE)
	{
		return;
	}
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);

	for (auto sword : listWeapon)
	{
		/*if (sword->GetFinish() == false)*/
			sword->Render(camera);
	}
	

	//if (true)
	//	RenderBoundingBox(camera);
}

void Witch::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1)
	{
		left = x - WITCH_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - WITCH_ACTIVE_BBOX_HEIGHT;
		bottom = y + WITCH_ACTIVE_BBOX_HEIGHT;
	}
	else
	{
		right = x + WITCH_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - WITCH_ACTIVE_BBOX_HEIGHT;
		bottom = y + WITCH_ACTIVE_BBOX_HEIGHT;
	}
}

void Witch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y - 1;
	right = x + WITCH_BBOX_WIDTH - 20 ;
	bottom = y + WITCH_BBOX_HEIGHT;
}
