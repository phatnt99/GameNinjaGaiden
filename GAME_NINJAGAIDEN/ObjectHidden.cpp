#include "ObjectHidden.h"


ObjectHidden::ObjectHidden(float X, float Y, int W, int H, int st)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::OBJECT_HIDDEN);// loại trong suốt 
	x = X;
	y = Y;
	width = W;
	height = H;
	sprite = new CSprite(texture, 1000);

	switch (st)
	{
	case 0:
		type = OBJECT_CLIMBUP;
		break;
	case 1:
		type = OBJECT_CLIMB;
		break;
	case 2:
		type = OBJECT_RUNNER;
		break;
	case 9:
		type = DOOR;
		break;
	default:
		break;
	}

	Health = 1;
}

ObjectHidden::~ObjectHidden()
{
}

void ObjectHidden::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void ObjectHidden::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void ObjectHidden::Render(Camera * camera)
{

		RenderBoundingBox(camera);
}
