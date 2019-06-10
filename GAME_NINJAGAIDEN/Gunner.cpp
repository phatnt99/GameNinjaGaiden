#include "Gunner.h"



Gunner::Gunner(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::GUNNER);
	sprite = new CSprite(texture, 200);
	sound = Sound::GetInstance();
	Health = 1; // sét máu
	type = eType::GUNNER;
	vy = 0.05f;
}

Gunner::~Gunner()
{
}

void Gunner::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		break;
	case DEATH:

		break;
	case INACTIVE:
		x = BackupX;
		y = backupY;
		direction = backupDirection;
		break;
	default:
		break;
	}
}
void Gunner::Update(DWORD dt, float xNinja, Grid *grid, vector<LPGAMEOBJECT>* coObjects)
{
	if (status == INACTIVE)
		return;
	if (this->x < xNinja)
	{
		direction = 1;
	}
	else
		direction = -1;

	

	int index = sprite->GetCurrentFrame();
	if (index < GUNNER_ANI_ATTACK_BEGIN)
	{
		sprite->SelectFrame(GUNNER_ANI_ATTACK_BEGIN);
		sprite->timeAccumulated = dt;
		
	}
	else
	{
		sprite->timeAccumulated += dt;
		if (sprite->timeAccumulated >= 1000)
		{
			sprite->timeAccumulated -= 1000;
			sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			if (sprite->GetCurrentFrame() < 2)
			{
				GunnerBullet* bullet = new GunnerBullet();
				bullet->SetSpeed(0.2f * direction, 0);
				bullet->Attack(x, y, this->direction);
				listWeapon.push_back(bullet);
				Unit * unit = new Unit(grid, bullet, bullet->GetX(), bullet->GetY());
				sound->Play(eSound::oneshot);
			}
			
		}
		if (sprite->GetCurrentFrame() > GUNNER_ANI_ATTACK_END)
		{
			sprite->SelectFrame(GUNNER_ANI_ATTACK_BEGIN);

		}
	}


	//else
	//{
	//	if (index < GUNNER_ANI_WALKING_BEGIN)
	//	{
	//		sprite->SelectFrame(GUNNER_ANI_WALKING_BEGIN);
	//		sprite->timeAccumulated = dt;
	//	}
	//	else
	//	{
	//		sprite->timeAccumulated += dt;
	//		if (sprite->timeAccumulated >= 200)
	//		{
	//			sprite->timeAccumulated -= 200;
	//			sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
	//		}
	//		/* Update ani bình thường */

	//		if (sprite->GetCurrentFrame() > GUNNER_ANI_WALKING_END) // đã đi vượt qua frame cuối
	//		{
	//			//mapWeapon[TypeWeaponCollect]->Start(this->x, this->y);
	//			sprite->SelectFrame(GUNNER_ANI_WALKING_BEGIN);
	//		}
	//	}
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
		vy += GUNNER_GRAVITY*dt;
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

void Gunner::Render(Camera * camera)
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

	if (true)
		RenderBoundingBox(camera);
	//if (Health <= 0)
	//	return;


}

void Gunner::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1)
	{
		left = x - GUNNER_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - GUNNER_ACTIVE_BBOX_HEIGHT;
		bottom = y + GUNNER_ACTIVE_BBOX_HEIGHT;
	}
	else
	{
		right = x + GUNNER_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - GUNNER_ACTIVE_BBOX_HEIGHT;
		bottom = y + GUNNER_ACTIVE_BBOX_HEIGHT;
	}
}

void Gunner::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + GUNNER_BBOX_WIDTH;
	bottom = y + GUNNER_BBOX_HEIGHT;
}
