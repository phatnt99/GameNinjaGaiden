#include "Ninja.h"

Ninja::Ninja(Camera* camera)
{
	texture = TextureManager::GetInstance()->GetTexture(eType::NINJA);
	sprite = new CSprite(texture, 100);
	type = eType::NINJA;
	sound = Sound::GetInstance();
	Health = 10;
	Lives = 5;
	this->camera = camera;
	subWeapon.push_back(new Katana());
	isGetNewStage = false;
	isFall = false;
	Init();
}


Ninja::~Ninja()
{

}

void Ninja::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (direction == 1)
	{
		if (isSitting == true)
		{
			left = x + 12;
			top = y + 20;
			right = x + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 12;
			top = y + 10;
			right = left + NINJA_BBOX_WIDTH - 10;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				//top = y + 30;
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;
			}
			if (isClimbing)
			{
				left = x + 12;
				top = y + 10;
				right = left + NINJA_BBOX_WIDTH - 15;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}
	else
	{
		if (isSitting == true)
		{
			left = x + 20;
			top = y + 20;
			right = x + 12 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 30;
			top = y + 10;
			right = x + 10 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

			}
			if (isClimbing)
			{
				left = x + 30;
				top = y + 10;
				right = x + 12 + NINJA_BBOX_WIDTH;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}

}

void Ninja::GetBoundingBoxBrick(float & left, float & top, float & right, float & bottom)
{
	if (direction == 1)
	{
		if (isSitting == true)
		{
			left = x + 12;
			top = y + 60;
			right = x + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 20;
			top = y + 60;
			right = left + NINJA_BBOX_WIDTH - 24;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				//top = y + 30;
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

			}
			if (isClimbing)
			{
				left = x + 20;
				top = y + 10;
				right = left + NINJA_BBOX_WIDTH - 30;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
		}
	}
	else
	{
		if (isSitting == true)
		{
			left = x + 20;
			top = y + 20;
			right = x + 12 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_SITTING_HEIGHT - 3;
		}
		else
		{
			left = x + 35;
			top = y + 10;
			right = x + 10 + NINJA_BBOX_WIDTH;
			bottom = y + NINJA_BBOX_HEIGHT;

			if (isJumping)
			{
				bottom = y + NINJA_BBOX_JUMPING_HEIGHT;

			}
			if (isClimbing)
			{
				left = x + 50;
				top = y + 10;
				right = x + 12 + NINJA_BBOX_WIDTH;
				bottom = y + NINJA_BBOX_HEIGHT;
			}
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
						sprite->SelectFrame(NINJA_ANI_IDLE);		

					}
			}
		}


		/* Update về sprite */
		if (isSitting) //đảm bảo ninja không rớt
			vy = 0;
		GameObject::Update(dt);
		//if(isWalking == true)
		//	x += dx;
		if (isJumping)
		{
			dx = vx * dt;
			dy = vy * dt;
			vy += NINJA_GRAVITY_JUMPING * dt;
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
		float l, r, t, b;
		GetBoundingBox(l, t, r, b);
		//DebugOut(L"BAN DAU left = %f\tright = %f\t top=%f\tbottom = %f\n", l, r, t, b);
		CollisionWithBrick(coObjects);
	}



	//for (auto& objWeapon : subWeapon)
	//{
	//	if (objWeapon.second->GetFinish() == false) // vũ khi này chưa kết thúc thì update
	//	{
	//		if (objWeapon.second->GetType() == eType::KATANA)
	//		{
	//			//if(isUseSubWeapon == true)
	//			//	continue;
	//			objWeapon.second->SetPosition(this->x, this->y);
	//			objWeapon.second->SetSpeed(vx, vy); // set vận tốc để kt va chạm
	//			objWeapon.second->UpdatePositionFitCharacter();
	//		}

	//		objWeapon.second->Update(dt, coObjects);
	//	}
	//}

	for (auto obj : subWeapon)
	{
		if (obj->GetFinish() == false)
		{
			if (obj->GetType() == eType::KATANA)
			{
				obj->SetPosition(this->x, this->y);
				obj->SetSpeed(vx, vy); // set vận tốc để kt va chạm
				obj->UpdatePositionFitCharacter(isSitting==true? 1:0);
			}
			else if (obj->GetType() == eType::WPWINDMILLSTAR)
			{
				dynamic_cast<WPWindmillStar*>(obj)->yNinja = y;
				dynamic_cast<WPWindmillStar*>(obj)->xNinja = x;
				obj->BackupX = x;
				obj->backupY = y + 18;
			}
			//DebugOut(L"NINJA isAttack = %d\n", isAttacking == 1 ? true : false);
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
	//if (true)
	//	RenderBoundingBox(camera);

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

void Ninja::Go(float Vx)
{
	vx = Vx * direction;
	isWalking = 1;

}

void Ninja::Sit()
{

	vx = 0;
	vy = 0;
	isWalking = 0;

	isJumping = 0;
	if (isSitting == false)
	{
		y = y + PULL_UP_NINJA_AFTER_SITTING;
	}

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
	sound->Play(eSound::jump);
}

void Ninja::Stop()
{
	//if (isAttacking == true)
		//return;

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

void Ninja::SetHurt(int t)
{
	if (isHurting == true)
		return;

	isWalking = 0;
	isAttacking = 0;
	isJumping = 0;

	ResetSit();

	subWeapon.front()->SetFinish(true);

	if (!isClimbing && !isClimbUp) 
	{
		//if (e->nx != 0)
		//{
		vx = NINJA_WALKING_SPEED * -direction;
		vy = -NINJA_VJUMP_HURTING;
		isHurting = 1;
		DebugOut(L"VA CHAM vx = %f \n", vx);
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

	if (t == 0) //enemy
	{
		sound->Play(eSound::touchEnemy);
		SubHealth(1); // chạm enemy -1 máu
	}
	else if (t == 1) //weapon enemy
	{
		sound->Play(eSound::touchEnemy);
		SubHealth(2);
	}
	else//boss
	{
		sound->Play(eSound::touchboss);
		SubHealth(2); // chạm enemy -1 máu
	}
	StartUntouchable(); // không cho các object đụng tiếp

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
		isFall = true;
		timeWait = GetTickCount();
		return;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> listEnemy;

	listEnemy.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == eType::BRICK || coObjects->at(i)->GetType() == eType::OBJECT_CLIMB || coObjects->at(i)->GetType() == eType::OBJECT_CLIMBUP || coObjects->at(i)->GetType() == eType::DOOR || coObjects->at(i)->GetId() == 141) //obj runner mà ninja sẽ phải chạm để nhảy
		{

			listEnemy.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&listEnemy, coEvents, flag);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

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
				{
					y += dy;
				}
				
				if (nx != 0 || ny != 0)
				{
					isHurting = false;
				}
			}

			if (dynamic_cast<ObjectHidden*>(coEventsResult[i]->obj))
			{
				if (ny == -1)
					isHurting = false;
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
							sound->Play(eSound::jump);
						}
					}
				}
				else if (coEventsResult[i]->obj->GetType() == eType::OBJECT_CLIMBUP)
				{
					isClimbing = true;
					vx = 0;
					vy = 0;
					isClimbUp = true;
					sound->Play(eSound::jump);
				}
				else if (coEventsResult[i]->obj->GetType() == eType::DOOR)
				{
					//if(nx!=0)
						isGetNewStage = true;
				}
				else if (coEventsResult[i]->obj->GetId() == 141)
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
					{
						y += dy;
				
					}

					if (nx != 0 || ny != 0)
					{
						isHurting = false;
					}
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
			//if (dynamic_cast<Weapon*>(coObjects->at(i)) && ((coObjects->at(i)->GetType() != eType::BULLET) || (coObjects->at(i)->GetType() == eType::GUNNERBULLET) || (coObjects->at(i)->GetType() == eType::SWORD)))
			//{
			//	if (dynamic_cast<Weapon*>(coObjects->at(i))->GetFinish() == false)
			//		listEnemy.push_back(coObjects->at(i));
			//}
		}

		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			if (listEnemy[i]->isCollitionObjectWithObject(this))
			{
				SetHurt(listEnemy[i]->GetType() == BOSS ? 2 : 0);
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
	if (isFreeze)
		return;
	if (GetTickCount() - untouchable_start > NINJA_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = false;
	}
	if (untouchable == false)
	{
		vector<LPGAMEOBJECT> listWeapon;

		listWeapon.clear();

		for (UINT i = 0; i < coObjects->size(); i++)
			if (coObjects->at(i)->GetType() == eType::BOM || coObjects->at(i)->GetType() == eType::SWORD || coObjects->at(i)->GetType() == eType::BULLET || coObjects->at(i)->GetType() == eType::GUNNERBULLET || coObjects->at(i)->GetType() == eType::WPWINDMILLSTAR)
				listWeapon.push_back(coObjects->at(i));
		for (UINT i = 0; i < listWeapon.size(); i++)
		{
			if (listWeapon[i]->isCollitionObjectWithObject(this) && dynamic_cast<Weapon*>(listWeapon[i])->GetFinish() == false)
			{
				if (!dynamic_cast<WPWindmillStar*>(listWeapon[i]))
				{
					SetHurt(1);
				}
				if (!dynamic_cast<GunnerBullet*>(listWeapon[i]))
					dynamic_cast<Weapon*>(listWeapon[i])->SetFinish(1);
				//DebugOut(L"Health = %d",Health);
			}
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
		else if (coObjects->at(i)->GetType() == BOM || coObjects->at(i)->GetType() == SWORD || coObjects->at(i)->GetType() == BULLET || coObjects->at(i)->GetType() == GUNNERBULLET)
		{
			if(dynamic_cast<Weapon*>(coObjects->at(i))->GetFinish() == false)
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

					if (weapon->GetType() == eType::WPWINDMILLSTAR && weapon->ableCollision(this))
						weapon->SetFinish(true);
					if (weapon->ableCollision(coEnemys.at(i)) == true)
					{

						//DebugOut(L"Co va cham");
						GameObject *obj = coEnemys.at(i);
						switch (obj->GetType())
						{
						case eType::BUTTERFLY:
						{
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
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							obj->SubHealth(1);
							score += 100;
							break;
						}
						case eType::WITCH:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							//}
							obj->SubHealth(1);
							score += 300;

							break;
						}
						case eType::DOG:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY() - 30));
							sound->Play(eSound::bum);
							//}
							obj->SubHealth(1);
							score += 200;
							break;
						}
						case eType::SOLDIER:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							/*							}*/
							obj->SubHealth(1);
							score += 200;
							break;
						}
						case eType::GUNNER:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							/*							}*/
							obj->SubHealth(1);
							score += 200;
							break;
						}
						case eType::RUNNER:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							/*							}*/
							obj->SubHealth(1);
							score += 300;
							break;
						}
						case eType::BIRD:
						{
							//if (dynamic_cast<Enemy*>(coObjects->at(i))->GetStatus() == ACTIVE)
							//{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							//}
							obj->SubHealth(1);
							score += 300;
							break;
						}
						case eType::BOM:
						{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							dynamic_cast<Bom*>(obj)->SetFinish(true);
							score += 100;
							break;
						}
						case eType::SWORD:
						{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							dynamic_cast<Sword*>(obj)->SetFinish(true);
							score += 100;
							break;
						}
						case eType::GUNNERBULLET:
						{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							dynamic_cast<GunnerBullet*>(obj)->SetFinish(true);
							score += 200;
							break;
						}
						case eType::BULLET:
						{
							listEffect.push_back(new Effect(obj->GetX(), obj->GetY()));
							sound->Play(eSound::bum);
							dynamic_cast<Bullet*>(obj)->SetFinish(true);
							score += 100;
							break;
						}
						case eType::BOSS:
						{
							if (weapon->isAttacked == true)
							{
								obj->SubHealth(1);
								weapon->isAttacked = false;
							}
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



bool Ninja::CheckAABBActiveArea(float l, float t, float r, float b) // kiem tra va cham trong vung active cua enemy bang AABB
{
	float ninja_l, ninja_t, ninja_r, ninja_b;
	this->GetBoundingBox(ninja_l, ninja_t, ninja_r, ninja_b);

	if (Game::GetInstance()->checkAABB(ninja_l, ninja_t, ninja_r, ninja_b, l, t, r, b))
		return true;

	return false;
}



void Ninja::Attack(eType typeWeapon)
{
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
			subWeapon.back()->SetSpeed(0.4f * direction, 0);
			subWeapon.back()->Attack(x, y, this->direction);
			sound->Play(eSound::throwingstar);
		}
		break;
	case eType::WPWINDMILLSTAR:
		if (strength >= 5)
		{
			if (subWeapon.back()->GetFinish()) // vũ khí đã kết thúc thì mới đc tấn công tiếp
			{
				WPWindmillStar *windmillstar = new WPWindmillStar();
				subWeapon.push_back(windmillstar);
				SetStrength(strength - 5);

				isAttacking = true; // set trang thái tấn công
				sprite->SelectFrame(0);
				sprite->ResetTime();
				//subWeapon>SetSpeed(0.2f * direction, 0);
				subWeapon.back()->SetSpeed(0.4f * direction, 0);
				subWeapon.back()->Attack(x, y, this->direction);
				sound->Play(eSound::millstar);
			}
		}
		break;
	case eType::WPFIREWHEEL:
		if (strength >= 5)
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
			sound->Play(eSound::firewheel);
			SetStrength(strength - 5);

		}
		break;
	case eType::KATANA:
		if (subWeapon.front()->GetFinish()) // vũ khí đã kết thúc thì mới đc tấn công tiếp
		{
			isAttacking = true; // set trang thái tấn công
			sprite->SelectFrame(0);
			sprite->ResetTime();
			subWeapon.front()->SetSpeed(0.2f * direction, 0);
			subWeapon.front()->Attack(x, y, this->direction); // set vị trí weapon theo Ninja
			subWeapon.front()->isAttacked = true;
			sound->Play(eSound::katana);
		}
		break;
	default:
		break;
	}
	


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

void Ninja::SetFreeze(bool f)
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
	isGetNewStage = false;
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
	
	SetTypeWeaponCollect(t); // set kiểu vũ khí đang nhặt được
}

void Ninja::Init()
{
	Health = NINJA_DEFAULT_HEALTH; // Ninja dính 16 phát là chết
	Lives = NINJA_DEFAULT_LIVES;
	strength = NINJA_DEFAULT_STRENGTH;
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

	isHurting = 0;

	vx = 0;
	vy = 0;
	isFreeze = 0;
	TimeFreeze = 0;

	isDeadth = false;
	isFall = false;
	isClimbing = false;
	isClimbUp = false;
	score = 0;

	TypeWeaponCollect = eType::NON_WEAPON_COLLECT;
}

bool Ninja::LoseLife()
{
	if (Lives - 1 < 0)
		return false;

	Health = NINJA_DEFAULT_HEALTH;
	Lives = Lives - 1;
	strength > 9 ? strength -= 9 : strength = 0;

	Reset();


	x = PositionBackup.x;
	y = PositionBackup.y;

	return true;
}
