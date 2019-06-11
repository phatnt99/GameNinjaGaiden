#include "Thief.h"


Thief::Thief(int direction, float X, float Y, float BorderLeft, float BorderRight, int status)
{
	x = X;
	y = Y;
	this->direction = direction;
	borderLeft = BorderLeft;
	borderRight = BorderRight;
	this->status = status;
	BackupX = x;
	backupDirection = direction;
	texture = TextureManager::GetInstance()->GetTexture(eType::THIEF);
	sprite = new CSprite(texture, 100);

	Health = 1; // sét máu
	type = eType::THIEF;
	vx = THIEF_SPEED_X* this->direction;
}

Thief::~Thief()
{
}

void Thief::SetStatus(int s)
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
		direction = backupDirection;
		vx = THIEF_SPEED_X * direction;
		Health = 1;
		break;
	default:
		break;
	}
}
void Thief::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (status == INACTIVE)
		return;

	if (this->GetX() <= borderLeft || this->GetX() >= borderRight)
	{
		direction *= -1;
		vx = THIEF_SPEED_X * direction;

	}

	Enemy::Update(dt);

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK || coObjects->at(i)->GetType() == eType::OBJECT_CLIMB || coObjects->at(i)->GetType() == eType::OBJECT_CLIMBUP)
		{

			listObject_Brick.push_back(coObjects->at(i));
		}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents, 0); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
		vy += THIEF_GRAVITY*dt;
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



	sprite->Update(dt); // update frame ani
}

void Thief::Render(Camera * camera)
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

	//if (true)
	//	RenderBoundingBox(camera);
	//if (Health <= 0)
	//	return;
	

}

void Thief::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (id == -1)
	{
		left = x - THIEF_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - THIEF_ACTIVE_BBOX_HEIGHT;
		bottom = y + THIEF_ACTIVE_BBOX_HEIGHT;
	}
	else
	{
		right = x + THIEF_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - THIEF_ACTIVE_BBOX_HEIGHT;
		bottom = y + THIEF_ACTIVE_BBOX_HEIGHT;
	}
}

void Thief::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + THIEF_BBOX_WIDTH;
	bottom = y + THIEF_BBOX_HEIGHT;
}
