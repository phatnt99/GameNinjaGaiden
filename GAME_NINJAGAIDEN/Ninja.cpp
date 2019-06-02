#include "Ninja.h"

Ninja::Ninja(Camera* camera)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::NINJA);
	sprite = new CSprite(texture, 100);
	//_sprite_deadth = sprite->SelectFrame(NINJA_DEADTH);
	type = eType::NINJA;

	Health = 10;
	Lives = 5;
	this->camera = camera;
	//mapWeapon[eType::KATANA] = new Katana();
	subWeapon.push_back(new Katana());

	Init();
}


Ninja::~Ninja()
{
	SAFE_DELETE(_sprite_deadth);
}

void Ninja::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true)
	{
		left = x;
		top = y + 12;
		right = x + NINJA_BBOX_WIDTH - 15;
		bottom = y + NINJA_BBOX_SITTING_HEIGHT;
	}
	else
	{
		left = x + 12;
		top = y + 10;
		right = left + NINJA_BBOX_WIDTH;
		bottom = y + NINJA_BBOX_HEIGHT;

		if (isJumping)
		{
			//top = y + 30;
			bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

		}
	}

}

void Ninja::GetBoundingBoxBrick(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true)
	{
		left = x;
		top = y + 60;
		right = x + NINJA_BBOX_WIDTH - 15;
		bottom = y + NINJA_BBOX_SITTING_HEIGHT;
	}
	else
	{
		left = x + 12;
		top = y + 60;
		right = left + NINJA_BBOX_WIDTH;
		bottom = y + NINJA_BBOX_HEIGHT;

		if (isJumping)
		{
			//top = y + 30;
			bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

		}
	}

}

void Ninja::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (Health <= 0)
		return;
	if (x < camera->GetBoundaryLeft() - 16)
		x = camera->GetBoundaryLeft() - 16;
	if (x + NINJA_BBOX_WIDTH > camera->GetBoundaryRight() + SCREEN_WIDTH)
		x = (float)(camera->GetBoundaryRight() + SCREEN_WIDTH - NINJA_BBOX_WIDTH);
	/* Không cho lọt khỏi camera */
	int index = sprite->GetCurrentFrame();

	if (isClimbing)
	{
		if (isUp)
		{
			if (index < NINJA_ANI_CLIMB_GO_UP_BEGIN) // nếu ani chưa đúng
			{
				sprite->SelectFrame(NINJA_ANI_CLIMB_GO_UP_BEGIN); // set lại ani bắt đầu
				sprite->timeAccumulated = dt;
			}
			else
			{
				/* Update ani bình thường */
				sprite->timeAccumulated += dt;
				if (sprite->timeAccumulated >= 100)
				{
					sprite->timeAccumulated -= 100;
					sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
				}
				/* Update ani bình thường */

				if (sprite->GetCurrentFrame() > NINJA_ANI_CLIMB_GO_UP_END) // đã đi vượt qua frame cuối
				{
					isUp = false;
					sprite->SelectFrame(NINJA_ANI_CLIMB_GO_UP_BEGIN);
				}
			}
			y += vy;


		}
		else
			sprite->SelectFrame(NINJA_ANI_CLIMB);
		
	}
	else
	{
		if (isSitting == true)
		{
			if (isAttacking)
			{
				if (index < NINJA_ANI_SITTING_ATTACKING_BEGIN) // nếu ani chưa đúng
				{
					sprite->SelectFrame(NINJA_ANI_SITTING_ATTACKING_BEGIN); // set lại ani bắt đầu
					sprite->timeAccumulated = dt;
				}
				else
				{
					/* Update ani bình thường */
					sprite->timeAccumulated += dt;
					if (sprite->timeAccumulated >= NINJA_TIME_WAIT_ANI_ATTACKING)
					{
						sprite->timeAccumulated -= NINJA_TIME_WAIT_ANI_ATTACKING;
						sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
					}
					/* Update ani bình thường */

					if (sprite->GetCurrentFrame() > NINJA_ANI_SITTING_ATTACKING_END) // đã đi vượt qua frame cuối
					{
						isAttacking = false;
						sprite->SelectFrame(NINJA_ANI_SITTING);
					}
				}
			}
			else
				sprite->SelectFrame(NINJA_ANI_SITTING);
		}
		else
		{
			if (isAttacking == true)
			{

				///* Xử lí ani đứng đánh */
				if (index < NINJA_ANI_STANDING_ATTACKING_BEGIN) // nếu ani chưa đúng
				{
					sprite->SelectFrame(NINJA_ANI_STANDING_ATTACKING_BEGIN); // set lại ani bắt đầu
					sprite->timeAccumulated = dt;
				}
				else
				{
					/* Update ani bình thường */
					sprite->timeAccumulated += dt;
					if (sprite->timeAccumulated >= NINJA_TIME_WAIT_ANI_ATTACKING)
					{
						sprite->timeAccumulated -= NINJA_TIME_WAIT_ANI_ATTACKING;
						sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
					}
					/* Update ani bình thường */

					if (sprite->GetCurrentFrame() > NINJA_ANI_STANDING_ATTACKING_END) // đã đi vượt qua frame cuối
					{
						//mapWeapon[TypeWeaponCollect]->Start(this->x, this->y);

						isAttacking = false;
						sprite->SelectFrame(NINJA_ANI_IDLE);
					}
				}
				// Xử lí ani đứNG

			}
			else
			{
				if (isWalking == true) // đang di chuyển
				{
					if (isJumping == false) // ko nhảy
					{
						if (index < NINJA_ANI_WALKING_BEGIN || index >= NINJA_ANI_WALKING_END)
							sprite->SelectFrame(NINJA_ANI_WALKING_BEGIN);

						//cập nhật frame mới
						sprite->Update(dt); // dt này được cập nhật khi gọi update; 
					}
					else
					{
						if (index < NINJA_ANI_JUMPING_BEGIN || index >= NINJA_ANI_JUMPING_END)
							sprite->SelectFrame(NINJA_ANI_JUMPING_BEGIN);

						//cập nhật frame mới
						sprite->Update(dt); // dt này được cập nhật khi gọi update; 
					}

				}
				else
					if (isJumping == true) // nếu ko đi mà chỉ nhảy
					{
						if (index < NINJA_ANI_JUMPING_BEGIN || index >= NINJA_ANI_JUMPING_END)
							sprite->SelectFrame(NINJA_ANI_JUMPING_BEGIN);

						//cập nhật frame mới
						sprite->Update(dt);
					}
					else
					{
						sprite->SelectFrame(NINJA_ANI_IDLE);		// SIMON đứng yên

					}
			}
		}


		/* Update về sprite */

		GameObject::Update(dt);
		//if(isWalking == true)
		//	x += dx;
		if (isJumping)
		{
			dx = vx * dt;
			dy = vy * dt;
			vy += NINJA_GRAVITY_JUMPING * dt;
			if (vy > 0)
				isFallDown = true;
			else
				isFallDown = false;
			//if (y >= 250)
			//{
			//	y = 250;
			//	isJumping = false;
			//}
		}
		else
		{

			//DebugOut(L"isHurt = %d ---- untouchable = %d\n",isHurting == true? 1:0, untouchable == true? 1: 0);
			if (isHurting)
			{
				sprite->SelectFrame(NINJA_ANI_HURTING);
				//DebugOut(L"IS HURTING ON\n");
				vy += NINJA_GRAVITY_HURTING * dt;
			}
			else
				vy += NINJA_GRAVITY * dt;
		}
		//CollisionWithObjHidden(coObjects);
		CollisionWithBrick(coObjects);
	}


	for (auto obj : subWeapon)
	{
		if (obj->GetFinish() == false)
		{
			if (obj->GetType() == eType::KATANA)
			{
				//if(isUseSubWeapon == true)
				//	continue;
				obj->SetPosition(this->x, this->y);
				obj->SetSpeed(vx, vy); // set vận tốc để kt va chạm
				obj->UpdatePositionFitCharacter();
			}
			else if (obj->GetType() == eType::WPWINDMILLSTAR)
			{
				if (isJumping)
					dynamic_cast<WPWindmillStar*>(obj)->status = 1;
				else if (isFallDown)
					dynamic_cast<WPWindmillStar*>(obj)->status = 2;
				dynamic_cast<WPWindmillStar*>(obj)->xNinja = x;
				//dynamic_cast<WPWindmillStar*>(obj)->yNinja = y;
				//obj->BackupX = x;
				//obj->backupY = y + 18;

			}
			obj->Update(dt, coObjects);
		}
	}

	for (auto obj : listEffect)
	{
		if (!dynamic_cast<Effect*>(obj)->IsFinish())
			obj->Update(dt);
	}
}


void Ninja::Render(Camera* camera)
{
	if (true)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Transform(x, y);

	int alpha = 255;

	if (untouchable)
		alpha = 128;



	if (direction == 1) // hướng phải
		sprite->Draw(pos.x, pos.y, alpha);
	else
		sprite->DrawFlipX(pos.x, pos.y, alpha);

	//for (auto& obj : mapWeapon)
	//{
	//	if(obj.second->GetFinish() == false)
	//		obj.second->Render(camera);

	//}

	for (auto obj : subWeapon)
	{
		if (obj->GetFinish() == false)
			obj->Render(camera);
	}

	for (auto obj : listEffect)
	{
		if (!dynamic_cast<Effect*>(obj)->IsFinish())
			obj->Render(camera);
	}

}

void Ninja::Left()
{
	isSitting = false;
	direction = -1;
}

void Ninja::Right()
{

	isSitting = false;
	SetDirection(1);

}

void Ninja::Go()
{

	vx = NINJA_WALKING_SPEED * direction;
	isWalking = 1;

}

void Ninja::Sit()
{

	vx = 0;
	vy = 0;
	isWalking = 0;

	isJumping = 0;
	if (isSitting == false)
		y = y + PULL_UP_NINJA_AFTER_SITTING;

	isSitting = 1;
}

void Ninja::ResetSit()
{
	if (isSitting == true)
	{
		isSitting = 0;
		y = y - PULL_UP_NINJA_AFTER_SITTING;
	}
}

void Ninja::Jump()
{
	if (isJumping == true)
		return;



	if (isSitting == true)
		return;
	//if (isAttacking == true)
	//	return;

	if (isHurting)
		return;
	vy = -NINJA_VJUMP;
	isJumping = true;
}

void Ninja::Stop()
{
	if (isAttacking == true)
		return;

	if (isHurting)
		return;

	vx = 0;
	//DebugOut(L"[STOP] Set vx = %f \n", vx);


	isWalking = 0;
	if (isSitting == true)
	{
		isSitting = 0;
		y = y - PULL_UP_NINJA_AFTER_SITTING;
	}

}

void Ninja::SetHurt()
{
	if (isHurting == true)
		return;

	isWalking = 0;
	isAttacking = 0;
	isJumping = 0;

	ResetSit();

		subWeapon.front()->SetFinish(true);

	if (true) // ko "đang tự đi" và ko "đang trên thang" thì bật ra
	{
		//if (e->nx != 0)
		//{
		vx = NINJA_WALKING_SPEED * -direction;
		vy = -NINJA_VJUMP_HURTING;
		isHurting = 1;
		//DebugOut(L"Vy khi di chuyen = %f \n", vx);
	//}

	//if (e->ny != 0)
	//{
	//	vy = -NINJA_VJUMP_HURTING;
	//	isHurting = 1;
	//	DebugOut(L"SET IS HURT 2\n");
	//	//DebugOut(L"Vy khi dung yen = %f \n", vy);
	//}
	}
	else
	{
		isWalking = 1;
	}

	StartUntouchable(); // không cho các object đụng tiếp


	SubHealth(1); // chạm enemy -1 máu
	//sound->Play(eSound::soundHurting);
}

void Ninja::SetStrength(int s)
{
	strength = s;
}

int Ninja::GetStrength()
{
	return strength;
}

void Ninja::CollisionWithBrick(const vector<LPGAMEOBJECT>* coObjects)
{
	flag = 1;
	if (this->y > 380)
	{
		isDeadth = true;
		return;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> listEnemy;

	listEnemy.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == eType::BRICK || coObjects->at(i)->GetType() == eType::OBJECT_CLIMB || coObjects->at(i)->GetType() == eType::OBJECT_CLIMBUP)
		{

			listEnemy.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&listEnemy, coEvents, flag);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isCollisionAxisYWithBrick = false;

		isClimbing = false;
		isClimbUp = false;
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
					if (isJumping)
					{
						isJumping = false;
						y = y - PULL_UP_NINJA_AFTER_JUMPING;
					}
				}
				else
					y += dy;

				//if (nx != 0)
				//{
				//	if (isJumping)
				//	{

				//		isCollisionAxisYWithBrick = true;
				//		isClimbing = true;
				//		vx = 0;
				//		vy = 0;
				//	}
				//	if (isClimbUp)
				//	{
				//		isClimbing = true;
				//	}
				//}
				//else
				//{
				//	//	DebugOut(L"%d : Col y = false - dt=%d\n", GetTickCount(), dt);
				//	isCollisionAxisYWithBrick = false;// đang ko va chạm trục y
				//}
				if (nx != 0 || ny != 0)
				{
					isHurting = 0;
				}
			}

			if (dynamic_cast<ObjectHidden*>(coEventsResult[i]->obj))
			{
				if (coEventsResult[i]->obj->GetType() == eType::OBJECT_CLIMB)
				{
					if (ny == -1)
					{

						vy = 0;
						if (isJumping)
						{
							isJumping = false;
							y = y - PULL_UP_NINJA_AFTER_JUMPING;
						}
					}
					else
						y += dy;

					if (nx != 0)
					{
						if (isJumping)
						{
							isClimbing = true;
							vx = 0;
							vy = 0;
						}
					}
				}
				else if (coEventsResult[i]->obj->GetType() == eType::OBJECT_CLIMBUP)
				{
					isClimbing = true;
					vx = 0;
					vy = 0;
					isClimbUp = true;
				}
			}
			else
			{
				isClimbing = false;
				isClimbUp = false;
			}
		}

	}


	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];


}
void Ninja::CollisionWithEnemy(const vector<LPGAMEOBJECT> *coObjects)
{
	if (isFreeze)
		return;
	if (GetTickCount() - untouchable_start > NINJA_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = false;
	}
	if (untouchable == false)
	{
		vector<LPGAMEOBJECT> listEnemy;

		listEnemy.clear();
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if ((dynamic_cast<Enemy*>(coObjects->at(i)) && (coObjects->at(i)->GetType() != eType::BUTTERFLY) && (coObjects->at(i)->GetType() != eType::THEBIRD)))
			{
				if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() != INACTIVE)
					listEnemy.push_back(coObjects->at(i));
			}
			if (dynamic_cast<Weapon*>(coObjects->at(i)) && ((coObjects->at(i)->GetType() != eType::BULLET) || (coObjects->at(i)->GetType() == eType::GUNNERBULLET) || (coObjects->at(i)->GetType() == eType::SWORD)))
			{
				listEnemy.push_back(coObjects->at(i));
			}
		}

		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			if (listEnemy[i]->isCollitionObjectWithObject(this))
			{
				SetHurt();
			}
		}
	}




}

void Ninja::CollisionWithEnemyArea(const vector<LPGAMEOBJECT>* coObjects)
{
	float enemy_l1, enemy_t1, enemy_r1, enemy_b1;
	float enemy_l2, enemy_t2, enemy_r2, enemy_b2;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		Enemy * enemy = dynamic_cast<Enemy*>(coObjects->at(i));
		if (enemy == NULL)
			continue;
		if (enemy->GetStatus() == ACTIVE || enemy->GetStatus() == DEATH)
			continue;

		enemy->GetActiveBoundingBox(enemy_l1, enemy_t1, enemy_r1, enemy_b1, -1);
		enemy->GetActiveBoundingBox(enemy_l2, enemy_t2, enemy_r2, enemy_b2, 1);
		if (CheckAABBActiveArea(enemy_l1, enemy_t1, enemy_r1, enemy_b1))
		{
			if (dynamic_cast<Thief*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);
			}
			if (dynamic_cast<Dog*>(enemy))
			{
				//DebugOut(L"Active Ngao\n");
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);
			}
			if (dynamic_cast<Bird*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}

			if (dynamic_cast<Witch*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);
			}
			if (dynamic_cast<Soldier*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}
			if (dynamic_cast<Gunner*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}
			if (dynamic_cast<Runner*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}
		}
		else if (CheckAABBActiveArea(enemy_l2, enemy_t2, enemy_r2, enemy_b2) && direction == -1)
		{

			if (dynamic_cast<Thief*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
				{
					enemy->SetStatus(ACTIVE);

				}
			}
			if (dynamic_cast<Dog*>(enemy))
			{
				//DebugOut(L"Active Ngao\n");
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);
			}
			if (dynamic_cast<Bird*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}

			if (dynamic_cast<Witch*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);
			}
			if (dynamic_cast<Soldier*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}
			if (dynamic_cast<Gunner*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}
			if (dynamic_cast<Runner*>(enemy))
			{
				if (enemy->GetStatus() == INACTIVE)
					enemy->SetStatus(ACTIVE);

			}
			else
			{
				enemy->SetDirection(-direction);
				enemy->SetVx(enemy->GetVx() * (-1));
			}
		}
	}


}
void Ninja::CollisionWeaponWithNinja(const vector<LPGAMEOBJECT> *coObjects)
{
	if (untouchable == true)
		return;
	vector<LPGAMEOBJECT> listWeapon;

	listWeapon.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::SWORD || coObjects->at(i)->GetType() == eType::BULLET || coObjects->at(i)->GetType() == eType::GUNNERBULLET || coObjects->at(i)->GetType() == eType::WPWINDMILLSTAR)
			listWeapon.push_back(coObjects->at(i));
	for (UINT i = 0; i < listWeapon.size(); i++)
	{
		if (listWeapon[i]->isCollitionObjectWithObject(this) && dynamic_cast<Weapon*>(listWeapon[i])->GetFinish() == false)
		{
			if (!dynamic_cast<WPWindmillStar*>(listWeapon[i]))
				SubHealth(2);
			if(!dynamic_cast<GunnerBullet*>(listWeapon[i]))
				dynamic_cast<Weapon*>(listWeapon[i])->SetFinish(1);
			//DebugOut(L"Health = %d",Health);
		}
	}
}

void Ninja::CollisionWeaponWithObj(const vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPGAMEOBJECT> coEnemys;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy*>(coObjects->at(i)))
		{
			if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
				coEnemys.push_back(coObjects->at(i));
		}
	}
	for (auto weapon : subWeapon)
	{

		if (weapon->GetFinish() == false)
		{
			for (UINT i = 0; i < coEnemys.size(); i++)
				if (weapon->GetLastTimeAttack() > weapon->GetLastTimeAttacked()) // tránh trường hợp xét quá nhiều lần attack
				{

					if(weapon->GetType() == eType::WPWINDMILLSTAR && weapon->ableCollision(this))
						weapon->SetFinish(true);
					if (weapon->ableCollision(coEnemys.at(i)) == true)
					{

						//DebugOut(L"Co va cham");
						GameObject *obj = coEnemys.at(i);
						switch (obj->GetType())
						{
						case eType::BUTTERFLY:
						{
							//if (dynamic_cast<Enemy*>(coEnemys->at(i))->GetStatus() == ACTIVE)
							//{

							//}
							obj->SubHealth(1);
							break;
						}
						case eType::THEBIRD:
						{
							//if (dynamic_cast<Enemy*>(coEnemys->at(i))->GetStatus() == ACTIVE)
							//{

							//}
							obj->SubHealth(1);
							break;
						}
						case eType::THIEF:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));

							//}
							obj->SubHealth(1);
							break;
						}
						case eType::WITCH:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));

							//}
							obj->SubHealth(1);
							break;
						}
						case eType::DOG:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));

							//}
							obj->SubHealth(1);
							break;
						}
						case eType::SOLDIER:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));

							/*							}*/
							obj->SubHealth(1);
							break;
						}
						case eType::GUNNER:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));

							/*							}*/
							obj->SubHealth(1);
							break;
						}
						case eType::RUNNER:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));

							/*							}*/
							obj->SubHealth(1);
							break;
						}
						case eType::BIRD:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							//}
							obj->SubHealth(1);
							break;
						}
						default:
							break;
						}
						if (weapon->GetType() == eType::WPFIREWHEEL)
							weapon->SetFinish(true);
						if (weapon->GetType() == eType::WPTHROWINGSTAR)
							weapon->SetFinish(true);
						obj->SetLastTimeAttacked(weapon->GetLastTimeAttack());
					}

				}
		}
	}
}
void Ninja::CollisionWithItems(const vector<LPGAMEOBJECT> *coObjects)
{
}

//void Ninja::CollisionWithObjHidden(const vector<LPGAMEOBJECT> *coObjects)
//{
//	vector<LPGAMEOBJECT> listObjHidden;
//
//	listObjHidden.clear();
//	for (UINT i = 0; i < coObjects->size(); i++)
//		if (dynamic_cast<ObjectHidden*>(coObjects->at(i)))
//		{
//			listObjHidden.push_back(coObjects->at(i));
//		}
//
//	for (UINT i = 0; i < listObjHidden.size(); i++)
//	{
//		if (listObjHidden[i]->isCollitionObjectWithObject(this))
//		{
//			if (listObjHidden[i]->GetId() == 1)
//				isClimbing = true;
//			else if (listObjHidden[i]->GetId() == 0)
//				isClimbUp = true;
//		}
//		else
//			isClimbUp = false;
//	}
//}

bool Ninja::CheckAABBActiveArea(float l, float t, float r, float b) // kiem tra va cham trong vung active cua enemy bang AABB
{
	float ninja_l, ninja_t, ninja_r, ninja_b;
	this->GetBoundingBox(ninja_l, ninja_t, ninja_r, ninja_b);

	if (Game::GetInstance()->checkAABB(ninja_l, ninja_t, ninja_r, ninja_b, l, t, r, b))
		return true;

	return false;
}

//bool Ninja::isCollisionWithItem(Item * objItem)
//{
//	if (objItem->GetFinish() == true)
//		return false;
//
//	float l, t, r, b;
//	float l1, t1, r1, b1;
//	this->GetBoundingBox(l, t, r, b);  // lấy BBOX của Ninja
//
//	objItem->GetBoundingBox(l1, t1, r1, b1);
//	if (Game::GetInstance()->checkAABB(l, t, r, b, l1, t1, r1, b1) == true)
//	{
//		return true; // check with AABB
//	}
//
//	return isCollitionObjectWithObject(objItem);
//}

void Ninja::Attack(eType typeWeapon)
{
	typeWeapon;
	if (isAttacking)
		return;
	switch (typeWeapon)
	{
	case eType::NON_WEAPON_COLLECT:
		return;
	case eType::WPTHROWINGSTAR:
		if (strength >= 3)
		{
			WPThrowingStar *throwingstar = new WPThrowingStar();
			subWeapon.push_back(throwingstar);
			SetStrength(strength - 3);

			isAttacking = true; // set trang thái tấn công
			sprite->SelectFrame(0);
			sprite->ResetTime();
			//subWeapon>SetSpeed(0.2f * direction, 0);
			subWeapon.back()->SetSpeed(0.2f * direction, 0);
			subWeapon.back()->Attack(x, y, this->direction);
		}
		break;
	case eType::WPWINDMILLSTAR:
		if (/*strength >= 3*/true)
		{
			WPWindmillStar *windmillstar = new WPWindmillStar();
			subWeapon.push_back(windmillstar);
			SetStrength(strength - 3);

			isAttacking = true; // set trang thái tấn công
			sprite->SelectFrame(0);
			sprite->ResetTime();
			//subWeapon>SetSpeed(0.2f * direction, 0);
			subWeapon.back()->SetSpeed(0.5f * direction, 0);
			subWeapon.back()->Attack(x, y, this->direction);
		}
		break;
	case eType::WPFIREWHEEL:
		if (strength >= 3)
		{
			for (int i = 0; i < 3; i++)
			{
				WPFireWheel *fire = new WPFireWheel();
				subWeapon.push_back(fire);

				isAttacking = true; // set trang thái tấn công
				sprite->SelectFrame(0);
				sprite->ResetTime();
				//subWeapon>SetSpeed(0.2f * direction, 0);
				subWeapon.back()->SetSpeed(0.4f * direction, -0.05f - (i*0.1f));
				subWeapon.back()->Attack(x, y, this->direction);
			}
			//DebugOut(L"strength = %d\n", strength);

			SetStrength(strength - 3);

		}
		break;
	case eType::KATANA:
		if (subWeapon.front()->GetFinish()) // vũ khí đã kết thúc thì mới đc tấn công tiếp
		{
			//if (isUseDoubleShot && typeWeapon != eType::MORNINGSTAR && IsUsingWeapon(eType::WEAPON_DOUBLE_SHOT)) // Double shot, sub weapon , và vũ khí phụ còn hoạt động thì bỏ qua
			//	return;

			isAttacking = true; // set trang thái tấn công
			sprite->SelectFrame(0);
			sprite->ResetTime();
			subWeapon.front()->SetSpeed(0.2f * direction, 0);
			subWeapon.front()->Attack(x, y, this->direction); // set vị trí weapon theo Ninja
		}
		break;
	default:
		break;
	}
	//if (typeWeapon != eType::KATANA)
	//	isUseSubWeapon = true;
	//else
	//	isUseSubWeapon = false;


}

int Ninja::GetLives()
{
	return Lives;
}

void Ninja::SetLives(int l)
{
	Lives = l;
}

int Ninja::GetScore()
{
	return score;
}

void Ninja::SetScore(int s)
{
	score = s;
}

bool Ninja::GetFreeze()
{
	return isFreeze;
}

void Ninja::SetFreeze(int f)
{
	isFreeze = f;
	TimeFreeze = 0; // thời gian đã đóng băng
}

void Ninja::UpdateFreeze(DWORD dt)
{
	if (TimeFreeze + dt >= TIME_FREEZE_MAX)
	{
		SetFreeze(false); // kết thúc đóng băng
	}
	else
		TimeFreeze += dt;
}

void Ninja::StartUntouchable()
{
	untouchable = true;
	untouchable_start = GetTickCount();
}

void Ninja::SetAutoGoX(int DirectionGo, int directionAfterGo, float Distance, float Speed)
{
	if (isAutoGoX == true)
		return;

	isAutoGoX = true;// chưa vào chế độ autoGo thì set

	AutoGoX_Backup_X = x; // set lại vị trí trước khi đi tự động

						  //Backup trạng thái
	isWalking_Backup = isWalking;
	isJumping_Backup = isJumping;
	isSitting_Backup = isSitting;
	isAttacking_Backup = isAttacking;
	directionY_Backup = directionY;

	AutoGoX_Distance = Distance;
	AutoGoX_Speed = Speed;
	AutoGoX_DirectionGo = (float)DirectionGo;
	this->directionAfterGo = directionAfterGo;


	direction = DirectionGo;
	vx = Speed * DirectionGo;
	isWalking = 1;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;
}

bool Ninja::GetIsAutoGoX()
{
	return isAutoGoX;
}

void Ninja::RestoreBackupAutoGoX()
{
	isWalking = isWalking_Backup;
	isJumping = isJumping_Backup;
	isSitting = isSitting_Backup;
	isAttacking = isAttacking_Backup;
	directionY = directionY_Backup;

	direction = directionAfterGo; // set hướng sau khi đi

	isWalking = 0; // tắt trạng thái đang đi
	isAutoGoX = 0; // tắt trạng thái auto

	vx = 0;
	vy = 0;
	// đi xong thì cho Ninja đứng yên
}

void Ninja::SetPositionBackup(float X, float Y)
{
	PositionBackup = D3DXVECTOR2(X, Y);
}

void Ninja::SetDeadth()
{
	SetIsDeadth(true);
	TimeWaitedAfterDeath = 0;

	ResetSit();
	vx = 0;
	isWalking = 0;

	//sound->Play(eSound::musicLifeLost);

	Stop();
}

bool Ninja::GetIsDeadth()
{
	return isDeadth;
}

void Ninja::SetIsDeadth(bool b)
{
	isDeadth = b;
}

eType Ninja::GetTypeWeaponCollect()
{
	return TypeWeaponCollect;
}

void Ninja::SetTypeWeaponCollect(eType t)
{
	TypeWeaponCollect = t;
}

void Ninja::WeaponCollect(eType t)
{
	/*switch (t)
	{

	case WPTHROWINGSTAR:
	{
		if (mapWeapon[t] == NULL)
		{
			mapWeapon[t] = new WPThrowingStar();
		}
		break;
	}
	default:
		break;
	}
*/
//sound->Play(eSound::soundCollectWeapon);
	SetTypeWeaponCollect(t); // set kiểu vũ khí đang nhặt được
}

bool Ninja::IsUsingWeapon(eType typeWeapon)
{
	//if (this->mapWeapon.find(typeWeapon) != this->mapWeapon.end()) // có tồn tại
	//{
	//	if (this->mapWeapon[typeWeapon]->GetFinish() == false) //chưa kết thúc
	//		return true;
	//}
	return false;
}

bool Ninja::GetIsUseDoubleShot()
{
	return true;
}

void Ninja::SetIsUseDoubleShot(bool b)
{
}

void Ninja::Init()
{
	Health = NINJA_DEFAULT_HEALTH; // Ninja dính 16 phát là chết
	Lives = NINJA_DEFAULT_LIVES;
	strength = NINJA_DEFAULT_STRENGTH + 100;
	score = NINJA_DEFAULT_SCORE;

	Reset();
}

void Ninja::Reset()
{

	direction = 1;

	isSitting = 0;
	isJumping = 0;
	isWalking = 0;
	isAttacking = 0;

	isAutoGoX = 0;
	isHurting = 0;

	vx = 0;
	vy = 0;
	isFreeze = 0;
	TimeFreeze = 0;

	isDeadth = false;
	//TypeWeaponCollect = eType::NON_WEAPON_COLLECT;
}

bool Ninja::LoseLife()
{
	if (Lives - 1 < 0)
		return false;

	Health = NINJA_DEFAULT_HEALTH;
	Lives = Lives - 1;


	Reset();


	x = PositionBackup.x;
	y = PositionBackup.y;

	return true;
}
