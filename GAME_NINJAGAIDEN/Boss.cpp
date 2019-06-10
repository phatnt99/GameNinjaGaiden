#include "Boss.h"



Boss::Boss(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	directX = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::BOSS);
	sprite = new CSprite(texture, 200);
	sound = Sound::GetInstance();
	isIdle = false;
	isDeath = false;
	isJumping = true;
	Health = 16; // sét máu
	type = eType::BOSS;
	start = GetTickCount();
	vy = 0.002f;
}

Boss::~Boss()
{
}

void Boss::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		break;
	case DEATH:

		break;
	case INACTIVE:

		break;
	default:
		break;
	}
}
void Boss::Update(DWORD dt, float xNinja, Grid *grid, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinish)
		return;
	if (Health == 0 && !isDeath)
	{
		isDeath = true;
		startDeath = GetTickCount();
	}
	if (status == INACTIVE || isDeath)
	{
		sound->Play(eSound::bumboss);
		DWORD now = GetTickCount();
		if (now - startDeath > TIME_DEATH)
		{
			isFinish = true;
			startDeath = now;
			return;
		}
		//DebugOut(L"DIE\n");
		if (listEffect.size() == 0)
			listEffect.push_back(new Effect_boss(x - 36, y + 35));

		if (!dynamic_cast<Effect_boss*>(listEffect.back())->IsFinish())
			listEffect.back()->Update(dt);
		else
			listEffect.push_back(new Effect_boss(x - 36, y + 35)); listEffect.back();
		return;
	}
	DWORD now = GetTickCount();
	if (now - start > TIME_WAIT && !isJumping)
	{
		count++;
		directX *= -1;
		if (61 <= xNinja && xNinja <= 421)
		{
			if (directX == 1)
				direction = 1;
			else if (directX == -1)
				direction = -1;
		}
		else if (xNinja < x)
		{
			direction = -1;
		}
		else if (xNinja > x)
		{
			direction = 1;
		}
		if (count == 3)
		{
			count = 0;
			if (direction == -1)
			{
				for (int i = 0; i < 3; i++)
				{
					Bom *bom = new Bom();
					Weapon.push_back(bom);
					sprite->SelectFrame(0);
					sprite->ResetTime();
					Weapon.back()->SetSpeed(0.1f * direction, 0);
					Weapon.back()->Attack(x + i * 30, y + i * 30, this->direction);
					Unit * unit = new Unit(grid, bom, bom->GetX(), bom->GetY());

				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					Bom *bom = new Bom();
					Weapon.push_back(bom);
					sprite->SelectFrame(0);
					sprite->ResetTime();
					Weapon.back()->SetSpeed(0.1f * direction, 0);
					Weapon.back()->Attack(x - i * 30, y + i * 30, this->direction);
					Unit * unit = new Unit(grid, bom, bom->GetX(), bom->GetY());

				}
			}
		}
		x += 5 * directX;
		y = -sqrt(pow(360 * 1.0 / 2, 2) - pow(x - 482 * 1.0 / 2, 2)) + 274;
		start = now;
		isJumping = true;
		vx = BOSS_SPEED_X * directX;
		//vy = -0.05f;
	}
	else if (isJumping && x > 61 && x < 421)
	{
		x += 5 * directX;
		y = -sqrt(pow(360 * 1.0 / 2, 2) - pow(x - 482 * 1.0 / 2, 2)) + 274;
		DebugOut(L"\nx = %f\ty = %f\n", x, y);
		//if ((x >= SCREEN_WIDTH / 2 - 50 && direction == -1) || (x <= SCREEN_WIDTH / 2 - 50 && direction == 1))
		//{
		//	//DebugOut(L"VO\n");
		//	vy = -0.07f;
		//}
		//else if ((x <= SCREEN_WIDTH / 2 - 50 && direction == -1) || (x >= SCREEN_WIDTH / 2 - 50 && direction == 1))
		//{
		//	vy = 0.07f;
		//}
	}
	else if (x <= 61 && isJumping)
	{
		//DebugOut(L"\nvy = %f\ty = %f\n", vy, y);
		vy = 0.005f;
		isIdle = true;
		y += vy * dt;

	}
	else if (x >= 421 && isJumping)
	{
		vy = 0.006f;
		isIdle = true;
		y += vy * dt;
	}

	int index = sprite->GetCurrentFrame();
	if (isJumping)
	{
		if (index != BOSS_ANI_JUMP)
		{
			sprite->SelectFrame(BOSS_ANI_JUMP);
			sprite->timeAccumulated = dt;
		}
	}
	else
	{
		if (index != BOSS_ANI_IDLE)
		{
			sprite->SelectFrame(BOSS_ANI_IDLE);
			sprite->timeAccumulated = dt;
		}
	}



	Enemy::Update(dt);
	//DebugOut(L"vx = %f, vy = %f, dx = %f, dy=%f, x=%f, y=%f\n", vx, vy, dx, dy, x, y);
	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK)
			listObject_Brick.push_back(coObjects->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents, 0); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0 && isIdle)
	{
		y += dy;
		//x += dx;
		//vy += BOSS_GRAVITY*dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		//x += min_tx * dx + nx * 0.4f;


		if (ny == -1.0f)
		{
			//DebugOut(L"VA CHAM DAT\n");
			vy = 0;
			vx = 0;
			isJumping = false;
			sound->Play(eSound::bosstouchbrick);
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	for (auto bom : Weapon)
	{
		if (!bom->GetFinish())
		{

			bom->Update(dt, coObjects);
		}

	}
}

void Boss::Render(Camera * camera)
{
	if (isFinish)
		return;
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);

	for (auto bom : Weapon)
	{
		if (bom->GetFinish() == false)
			bom->Render(camera);
	}

	if (true)
		RenderBoundingBox(camera);
	for (auto obj : listEffect)
	{
		if (!dynamic_cast<Effect_boss*>(obj)->IsFinish())
			obj->Render(camera);
	}


}

void Boss::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1)
	{
		left = x - BOSS_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - BOSS_ACTIVE_BBOX_HEIGHT;
		bottom = y + BOSS_ACTIVE_BBOX_HEIGHT;
	}
	else
	{
		right = x + BOSS_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - BOSS_ACTIVE_BBOX_HEIGHT;
		bottom = y + BOSS_ACTIVE_BBOX_HEIGHT;
	}
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOSS_BBOX_WIDTH;
	bottom = y + BOSS_BBOX_HEIGHT;
}
