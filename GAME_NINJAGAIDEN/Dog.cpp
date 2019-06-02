#include "Dog.h"



Dog::Dog(int Direction, float X, float Y, int status)
{
	x = X;
	y = Y;
	this->direction = Direction;
	this->status = status;
	BackupX = x;
	backupY = y;
	backupDirection = direction;
	isJumping = true;
	texture = TextureManager::GetInstance()->GetTexture(eType::DOG);
	sprite = new CSprite(texture, 300);

	Health = 1; // sét máu
	type = eType::DOG;
	/*vx = DOG_SPEED_X* this->direction;*/
}

Dog::~Dog()
{
}

void Dog::SetStatus(int s)
{
	Enemy::SetStatus(s);

	switch (this->status)
	{
	case ACTIVE:
		isJumping = true;
		break;
	case DEATH:
		break;
	case INACTIVE:
		x = BackupX;
		y = backupY;
		isJumping = true;
		direction = backupDirection;
		vx = DOG_SPEED_X * direction;
		break;
	default:
		break;
	}
}


void Dog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (status == INACTIVE)
		return;
	vx = DOG_SPEED_X * direction;
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
		vy += DOG_GRAVITY*dt;
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

	if (isJumping == true && ((x + GetWidth() >= 1080) && (x <= 2240)))
	{
		vy = -0.4f;
		isJumping = false;

	}

	sprite->Update(dt); // update frame ani
}

void Dog::Render(Camera * camera)
{
	if (this->status == INACTIVE)
	{
		return;
	}
	if (Health <= 0)
		return;

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);

	if (true)
		RenderBoundingBox(camera);

}

void Dog::GetActiveBoundingBox(float &left, float &top, float &right, float &bottom, int id)
{
	if (backupDirection == -1)
	{
		left = x - DOG_ACTIVE_BBOX_WIDTH;
		right = left + 20;
		top = y - DOG_ACTIVE_BBOX_HEIGHT;
		bottom = y + DOG_ACTIVE_BBOX_HEIGHT;
	}
	else 
	{
		right = x + DOG_ACTIVE_BBOX_WIDTH;
		left = right - 20;
		top = y - DOG_ACTIVE_BBOX_HEIGHT;
		bottom = y + DOG_ACTIVE_BBOX_HEIGHT;
	}
		
}
