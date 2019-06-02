#include "Runner.h"



Runner::Runner(int direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::RUNNER);
	sprite = new CSprite(texture, 200);
	isWalking = true;
	Health = 1; // sét máu
	type = eType::RUNNER;
	vx = RUNNER_SPEED_X* this->direction;
	vy = 0.05f;
}

Runner::~Runner()
{
}

void Runner::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		isWalking = true;
		isJumping = false;
		isClimbing = false;
		oldX = x;
		vx = RUNNER_SPEED_X * direction;
		vy = 0.05f;
		break;
	case DEATH:

		break;
	case INACTIVE:
		isWalking = true;
		isJumping = false;
		isClimbing = false;
		x = BackupX;
		y = backupY;
		direction = backupDirection;
		vx = RUNNER_SPEED_X * direction;
		vy = 0.05f;
		break;
	default:
		break;
	}
}
void Runner::Update(DWORD dt, float xNinja, Grid *grid, vector<LPGAMEOBJECT>* coObjects)
{
	if (status == INACTIVE)
		return;

	int index = sprite->GetCurrentFrame();
	//DebugOut(L"climbing = %d\n", isClimbing == true ? 1 : 0);
	//DebugOut(L"vy=%f\ty=%f\tdy=%f\n", vy, y,dy);
	if (isWalking)
	{
		if (isClimbing || isJumping)
		{
			sprite->SelectFrame(RUNNER_ANI_JUMPING);
		}
		else
		{
			if (index < RUNNER_ANI_WALKING_BEGIN)
			{
				sprite->SelectFrame(RUNNER_ANI_WALKING_BEGIN);
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

				if (sprite->GetCurrentFrame() > RUNNER_ANI_WALKING_END) // đã đi vượt qua frame cuối
				{
					//mapWeapon[TypeWeaponCollect]->Start(this->x, this->y);
					sprite->SelectFrame(RUNNER_ANI_WALKING_BEGIN);
				}
			}
		}
	}

	


	Enemy::Update(dt);

	if (isJumping)
	{
		vy += 0.001f*dt;

	}
	else
		vy += 0.01f*dt;
	//if (isWalking)
	//{
	//	if (isClimbing)
	//	{

	//	} 
	//}


	//vector<LPGAMEOBJECT> listObject_Brick;
	//listObject_Brick.clear();
	//for (UINT i = 0; i < coObjects->size(); i++)
	//	if (coObjects->at(i)->GetType() == eType::BRICK)
	//		listObject_Brick.push_back(coObjects->at(i));

	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;
	//coEvents.clear();
	//CalcPotentialCollisions(&listObject_Brick, coEvents, 0); // Lấy danh sách các va chạm 
	//if (coEvents.size() == 0)
	//{
	//	y += dy;
	//	x += dx;
	//}
	//else
	//{
	//	DebugOut(L"\nCO VA CHAM\n");
	//	float min_tx, min_ty, nx = 0, ny;
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	//	//x += min_tx * dx + nx * 0.4f;


	//	if (ny == -1.0f)
	//	{
	//		vy = 0;
	//		DebugOut(L"\nVA CHAM CHAN VOI NEN %d\n",id++);
	//	}
	//	else
	//	{
	//		y += dy;
	//		DebugOut(L"\nKHONG VA CHAM CHAN VOI NEN %d\n",id++);
	//	}

	//	if (nx != 0) //cham ben trai - phai
	//	{
	//		isClimbing = true;
	//		vy = -0.4f;
	//		y += dy;
	//		DebugOut(L"\n VA CHAM DE CLIMB %d\ndy = %f\t y= %f",id++,dy,y);
	//	}
	//	else
	//	{
	//		isClimbing = false;
	//		//vx = RUNNER_SPEED_X * direction;
	//		DebugOut(L"\nKHONG VA CHAM DE CLIMB %d\n",id++);
	//	}
	//}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> listEnemy;

	listEnemy.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if ((coObjects->at(i)->GetType() == eType::BRICK && coObjects->at(i)->GetId() != 145) || (coObjects->at(i)->GetType() == eType::OBJECT_RUNNER || coObjects->at(i)->GetType() == eType::OBJECT_CLIMB && coObjects->at(i)->GetId() != 143))
		{

			listEnemy.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&listEnemy, coEvents, flag);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		//vy = 0.005f * dt;
		DebugOut(L"\ny = %f\tvy =%f\tdy= %f\n",y,vy,dy);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		min_tx = min_ty = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.1f;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			if (dynamic_cast<Brick*>(coEventsResult[i]->obj))
			{
				if (ny == -1)
				{

					vy = 0;
					isClimbing = false;
					isJumping = false;
				}
				else
					y += dy;

			}

			if (dynamic_cast<ObjectHidden*>(coEventsResult[i]->obj))
			{
				if (coEventsResult[i]->obj->GetId() == 230)
				{ 
					DebugOut(L"VA CHAM");
					if (nx != 0)
					{
						y -= 1.5f*dt;
						isClimbing = true;
					}
				}
				else 
				{
					if (ny < 0)
					{
						vy = -0.5f;
						//y += dy;
						isJumping = true;
					}
				}
			}
		}

	}


	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Runner::Render(Camera * camera)
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

	if (true)
		RenderBoundingBox(camera);
	//if (Health <= 0)
	//	return;


}

void Runner::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1)
	{
		left = x - RUNNER_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - RUNNER_ACTIVE_BBOX_HEIGHT;
		bottom = y + RUNNER_ACTIVE_BBOX_HEIGHT;
	}
	else
	{
		right = x + RUNNER_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - RUNNER_ACTIVE_BBOX_HEIGHT;
		bottom = y + RUNNER_ACTIVE_BBOX_HEIGHT;
	}
}

void Runner::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + RUNNER_BBOX_WIDTH;
	bottom = y + RUNNER_BBOX_HEIGHT;
}
