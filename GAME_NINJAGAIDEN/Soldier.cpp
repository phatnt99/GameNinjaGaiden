#include "Soldier.h"



Soldier::Soldier(int direction, float X, float Y, float BorderLeft, float BorderRight, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	borderLeft = BorderLeft;
	borderRight = BorderRight;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::SOLDIER);
	sprite = new CSprite(texture, 200);
	sound = Sound::GetInstance();

	Health = 1; // sét máu
	type = eType::SOLDIER;
	vx = SOLDIER_SPEED_X* this->direction;
	vy = 0.05f;
	countAttack = 0;
}

Soldier::~Soldier()
{
}

void Soldier::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		isWalking = true;
		isAttack = false;
		oldX = x;
		countAttack = 0;

		break;
	case DEATH:

		break;
	case INACTIVE:
		x = BackupX;
		y = backupY;
		direction = backupDirection;
		vx = SOLDIER_SPEED_X * direction;
		break;
	default:
		break;
	}
}
void Soldier::Update(DWORD dt, float xNinja,Grid *grid, vector<LPGAMEOBJECT>* coObjects)
{
	if (status == INACTIVE)
		return;
	if (this->x < xNinja)
	{
		direction = 1;
	}
	else
		direction = -1;

	if (this->x <= borderLeft || this->x >= borderRight)
	{
		vx *= -1;
		oldX = x;
	}

	if (abs(x - oldX) >= SOLDIER_DELTA_X)
	{
		isAttack = true;
		oldX = x;
		vx = 0;
		Bullet* bullet = new Bullet();
		bullet->SetSpeed(0.2f * direction, 0);
		bullet->Attack(x, y, this->direction);
		listWeapon.push_back(bullet);
		Unit * unit = new Unit(grid, bullet, bullet->GetX(), bullet->GetY());
		countAttack++;
		sound->Play(eSound::threeshot);
	}

	//if (status == DEATH)
	//{
	//	this->SetStatus(INACTIVE);
	//	return;
	//}
	/*if (this->GetX() <= borderLeft)
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
		}
		isWalking = false;
		DebugOut(L"%d\n", direction);

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
		}
	}*/

	int index = sprite->GetCurrentFrame();
	if (isWalking)
	{
		if (isAttack)
		{
			if (index < SOLDIER_ANI_ATTACK_BEGIN)
			{
				sprite->SelectFrame(SOLDIER_ANI_ATTACK_BEGIN);
				sprite->timeAccumulated = dt;
			}
			else
			{
				sprite->timeAccumulated += dt;
				if (sprite->timeAccumulated >= 70)
				{
					sprite->timeAccumulated -= 70;
					sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
				}
				if (sprite->GetCurrentFrame() > SOLDIER_ANI_ATTACK_END)
				{
					if (countAttack > 2)
					{
						isAttack = false;
						sprite->SelectFrame(SOLDIER_ANI_WALKING_BEGIN);
						vx = SOLDIER_SPEED_X* this->direction;
						countAttack = 0;
					}
					else
					{
						sprite->SelectFrame(SOLDIER_ANI_ATTACK_BEGIN);
						vx = 0;
						Bullet* bullet = new Bullet();
						bullet->SetSpeed(0.2f * direction, 0);
						bullet->Attack(x, y, this->direction);
						listWeapon.push_back(bullet);
						Unit * unit = new Unit(grid, bullet, bullet->GetX(), bullet->GetY());
						countAttack++;
					}
				}
			}
		}

		else
		{
			if (index < SOLDIER_ANI_WALKING_BEGIN)
			{
				sprite->SelectFrame(SOLDIER_ANI_WALKING_BEGIN);
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

				if (sprite->GetCurrentFrame() > SOLDIER_ANI_WALKING_END) // đã đi vượt qua frame cuối
				{
					//mapWeapon[TypeWeaponCollect]->Start(this->x, this->y);
					sprite->SelectFrame(SOLDIER_ANI_WALKING_BEGIN);
				}
			}
		}
	}


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
		vy += SOLDIER_GRAVITY*dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		

		if (ny == -1.0f)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	for (auto bullet : listWeapon)
	{
		if (!bullet->GetFinish())
		{

			bullet->Update(dt, coObjects);
		}

	}
}

void Soldier::Render(Camera * camera)
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

	for (auto bullet : listWeapon)
	{
		if (bullet->GetFinish() == false)
			bullet->Render(camera);
	}

	//if (true)
	//	RenderBoundingBox(camera);
	//if (Health <= 0)
	//	return;


}

void Soldier::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1)
	{
		left = x - SOLDIER_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - SOLDIER_ACTIVE_BBOX_HEIGHT;
		bottom = y + SOLDIER_ACTIVE_BBOX_HEIGHT;
	}
	else
	{
		right = x + SOLDIER_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - SOLDIER_ACTIVE_BBOX_HEIGHT;
		bottom = y + SOLDIER_ACTIVE_BBOX_HEIGHT;
	}
}

void Soldier::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SOLDIER_BBOX_WIDTH;
	bottom = y + SOLDIER_BBOX_HEIGHT;
}
