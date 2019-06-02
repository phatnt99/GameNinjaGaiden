#include "Brick.h"




Brick::Brick(float X, float Y, int W, int H)
{

	texture = TextureManager::GetInstance()->GetTexture(eType::BRICK_TRANSPARENT);// loại trong suốt 

	type = eType::BRICK;
	sprite = new CSprite(texture, 1000);
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
}

void Brick::Render(Camera * camera)
{
	if (true)
		RenderBoundingBox(camera);



	////return;

	//int vtd = 0;
	//if (x < camera->GetXCam())
	//	vtd =  (camera->GetXCam() - x) / texture->GetFrameWidth();

	//int vtc = (int)ceil(width / texture->GetFrameWidth());// min((int)ceil(width / texture->GetFrameWidth()), vtd + camera->GetWidth() / texture->GetFrameWidth());


	//for (int i = vtd; i < vtc; i++)
	//	for (int j = 0; j < (int)ceil(height / texture->GetFrameHeight()); j++)
	//		sprite->Draw((int)pos.x + i * texture->GetFrameWidth(), (int)pos.y + j * texture->GetFrameHeight());
	//
	//for (int i = 0; i < (int)ceil(width / texture->GetFrameWidth()); i++)
	//	for (int j = 0; j < (int)ceil(height / texture->GetFrameHeight()); j++)
	//		sprite->Draw((int)pos.x + i * texture->GetFrameWidth(), (int)pos.y + j * texture->GetFrameHeight());
	// 

}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	float a = ceil(width / texture->GetFrameWidth());
	int bb = width / texture->GetFrameWidth();
	r =x + (float)width / texture->GetFrameWidth()*texture->GetFrameWidth();
	b =y + (float)height / texture->GetFrameHeight()*texture->GetFrameHeight();
}

