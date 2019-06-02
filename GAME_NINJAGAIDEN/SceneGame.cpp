#include "SceneGame.h"
#include <stdlib.h>
#include <ctime>
SceneGame::SceneGame()
{
	LoadResources();

}

SceneGame::~SceneGame()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(grid);
}

void SceneGame::KeyState(BYTE * state)
{

	if (ninja->isHurting || ninja->GetIsDeadth() || isGameOver )
		return;

	//thoát khỏi trạng thái bám, leo
	if (Game::GetInstance()->IsKeyDown(DIK_Z))
	{
		if (ninja->GetIsClimbing())
		{

			if ((Game::GetInstance()->IsKeyDown(DIK_LEFT) && ninja->GetDirection() == 1) || (Game::GetInstance()->IsKeyDown(DIK_RIGHT) && ninja->GetDirection() == -1))
			{
				ninja->Stop();
				//ninja->SetSpeed(NINJA_WALKING_SPEED * ninja->GetDirection(), -NINJA_VJUMP);
				ninja->SetIsClimbing(false);
				ninja->SetIsClimbUp(false);
				ninja->SetVy(-NINJA_VJUMP);
				ninja->isJumping = 1;
				ninja->isWalking = 1;
			}

		}
	}

	//cho phép leo thang
	if (ninja->GetIsClimbUp() && ninja->GetIsClimbing())
	{
		if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			ninja->isUp = true;

			if (ninja->GetY() >= 170) // vị trí biên trên khi leo lên thang
			{
				ninja->SetVy(-1.0f);
			}
			else
			{
				ninja->SetVy(0);
			}
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			ninja->isUp = true;

			if (ninja->GetY() <= 287) //vị trí biên dưới khi leo xuống thang
			{
				ninja->SetVy(1.0f);
			}
			else
			{
				ninja->SetVy(0);
				ninja->SetIsClimbing(false);
				ninja->SetIsClimbUp(false);
			}
		}		
	}
	else
		ninja->isUp = false;

	//Đang bám thì không cho cử động
	if (ninja->GetIsClimbing())
		return;
	if (Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_X) && !ninja->isAttacking)
	{

		ninja->Attack(ninja->GetTypeWeaponCollect());
	}

	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{

		if (Game::GetInstance()->IsKeyDown(DIK_Z) || ninja->isJumping == true)
		{
			ninja->ResetSit();
			ninja->Jump();
		}
		else
			ninja->Sit();
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			ninja->ResetSit();
			ninja->Right();
			ninja->Go();
		}
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			ninja->ResetSit();
			ninja->Left();
			ninja->Go();
		}

		return;
	}

	// giai quyet dang di ma danh thi dung lai danh
	if (ninja->isAttacking && ninja->isWalking && !ninja->isJumping)
	{
		float vx, vy;
		ninja->GetSpeed(vx, vy);
		ninja->SetSpeed(0, vy);
		return;
	}

	// giai quyet dang nhay ma danh thi van danh va co vx 
	if (ninja->isAttacking)
	{
		float vx, vy;
		ninja->GetSpeed(vx, vy);
		//ninja->SetSpeed(0, vy);
		return;
	}

	
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		ninja->Right();
		ninja->Go();
	}
	else
	{
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			ninja->Left();
			ninja->Go();
		}
		else
		{
			ninja->Stop();
		}

	}
}

void SceneGame::OnKeyDown(int KeyCode)
{

	//if (ninja->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	//{
	//	return;
	//}
	if (isGameOver)
	{
		if (KeyCode == DIK_RETURN)
		{
			InitGame();
			isGameOver = false;
		}
	}
	if (ninja->GetIsDeadth())
	{
		return;
	}


	//	DestroyWindow(Game::GetInstance()->GetWindowHandle()); // thoát

	//if (ninja->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
	//	return;

	//if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
	//	return;


	//if (ninja->isHurting)
	//	return;


	//if (!(Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_A) && ninja->isAttacking == true) || !(Game::GetInstance()->IsKeyDown(DIK_LEFT)) || !(Game::GetInstance()->IsKeyDown(DIK_RIGHT)))
	//		ninja->Attack(eType::KATANA);

	if (!(Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_X)))
		if (Game::GetInstance()->IsKeyDown(DIK_X) && ninja->isAttacking == false)
			ninja->Attack(eType::KATANA);

	//if (ninja->isJumping && ninja->isWalking)
	//{
	//	return;
	//}

	//if (ninja->isSitting)
	//{
	//	if (Game::GetInstance()->IsKeyDown(DIK_A))
	//	{
	//		ninja->Attack(eType::KATANA);
	//	}
	//}
	//else
	//{
		//if (!(Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_A) /*&& simon->isProcessingOnStair == 0*/ && ninja->isAttacking == true))
		//	if (KeyCode == DIK_A) // không phải đang xử lí việc đi trên thang thì đc đánh
		//	{
		//		ninja->Attack(eType::KATANA);
		//	}
	//}
	if (KeyCode == DIK_Z)
	{
		if (ninja->isJumping)
			return;
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) || Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			ninja->Stop();
			ninja->SetSpeed(NINJA_WALKING_SPEED * ninja->GetDirection(), -NINJA_VJUMP);
			ninja->isJumping = 1;
			ninja->isWalking = 1;
		}
		else
		{
			ninja->Jump();
		}
	}
	//if (KeyCode == DIK_R)
	//{
	//	if (isDebug_RenderBBox==0)
	//		isDebug_RenderBBox = 1;
	//	else
	//		isDebug_RenderBBox = 0;
	//}

}

void SceneGame::OnKeyUp(int KeyCode)
{
	//if (ninja->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	//{
	//	return;
	//}

	//if (ninja->GetIsDeadth())
	//{
	//	return;
	//}

	//if (ninja->isSitting == true)
	//	ninja->ResetSit();

}

void SceneGame::LoadResources()
{
	TextureManager * textureManager = TextureManager::GetInstance();

	gameTime = new GameTime();
	TileMap = new Map();


	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	ninja = new Ninja(camera);
	grid = new Grid(9600, 480);
	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);
	InitGame();
}

void SceneGame::InitGame()
{
	LoadMap(eType::MAP2);
	ninja->Init();

	gameTime->SetTime(0); // đếm lại từ 0

}
bool FilterThief(vector<GameObject*>list, GameObject* obj)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (obj->BackupX == list[i]->BackupX)
			return true;
	}
	return false;
}
void SceneGame::ResetResource()
{

	grid->ReloadGrid();

	listObj.clear();

	listUnit.clear();

	camera->SetAllowFollowNinja(true);

	isGameOver = false;
	//countEnemy = 0;
	//isWaitProcessCreateThief = false;
	//timeCreateThief = 0;
}


void SceneGame::Update(DWORD dt)
{
	if (isGameOver)
		return;

	if (gameTime->GetTime() >= GAME_TIME_MAX || ninja->GetHealth() < 1)
	{
		if (ninja->GetIsDeadth())
		{
			ninja->GetSprite()->SelectFrame(NINJA_DEADTH);

			bool ret = ninja->LoseLife();

			if (ret)
			{
				camera->RestorePosition();
				camera->RestoreBoundary();

				gameTime->SetTime(0);

				ResetResource();
			}
			else
			{
				EndTime = GetTickCount();
				timeWait = GetTickCount();
				isGameOver = true;
			}

			return;
		}
		else
		{
			ninja->SetDeadth();
		}
	}
	//rơi xuống vực -> chết
	else if (ninja->GetIsDeadth())
	{
		bool ret = ninja->LoseLife();
		ninja->GetSprite()->SelectFrame(8);

		if (ret)
		{
			camera->RestorePosition();
			camera->RestoreBoundary();

			gameTime->SetTime(0);

			ResetResource();
		}
		else
		{
			EndTime = GetTickCount();
			timeWait = GetTickCount();
			isGameOver = true;
		}

		return;
	}
	int count = 0;
	listObj.clear();
	listUnit.clear(); // lay obj co trong vung camera thong qua unit
	grid->GetListObject(listUnit, camera);

	for (UINT i = 0; i < listUnit.size(); i++)
	{
		LPGAMEOBJECT obj = listUnit[i]->GetObj();
		listObj.push_back(obj);
	}
	ninja->Update(dt, &listObj);
	if (camera->AllowFollowNinja())
		camera->SetPosition(ninja->GetX() - SCREEN_WIDTH / 2 + 30, camera->GetYCam()); // cho camera chạy theo ninja

	camera->Update(dt);

	gameTime->Update(dt);

	DWORD now = GetTickCount();
	//DebugOut(L"now = %d \ttimeBegin = %d\n", now, timeBeginFreeze);
	if (now - timeBeginFreeze > timeFreeze)
	{
		ninja->SetFreeze(0);
		for (UINT i = 0; i < listObj.size(); i++)
		{
			LPGAMEOBJECT obj = listObj[i];
			if (dynamic_cast<Bird*>(listObj[i]))
			{
				Bird *bird = dynamic_cast<Bird*>(listObj[i]);
				if(ninja->isJumping == false)
					bird->Update(dt, ninja->GetX(), ninja->GetY(), &listObj);
				else
					bird->Update(dt, ninja->GetX(), -1, &listObj);
			}
			if (dynamic_cast<Witch*>(listObj[i]))
			{
				Witch *witch = dynamic_cast<Witch*>(listObj[i]);
				witch->Update(dt, ninja->GetX(), grid, &listObj);
			}
			if (dynamic_cast<Soldier*>(listObj[i]))
			{
				Soldier *soldier = dynamic_cast<Soldier*>(listObj[i]);
				soldier->Update(dt, ninja->GetX(), grid, &listObj);
			}
			if (dynamic_cast<Gunner*>(listObj[i]))
			{
				Gunner *gunner = dynamic_cast<Gunner*>(listObj[i]);
				gunner->Update(dt, ninja->GetX(), grid, &listObj);
			}
			if (dynamic_cast<Runner*>(listObj[i]))
			{
				Runner *runner = dynamic_cast<Runner*>(listObj[i]);
				runner->Update(dt, ninja->GetX(), grid, &listObj);
			}
			else
				obj->Update(dt, &listObj);
		}
	}

	CheckDropItem();
	SetInactiveEnemy();
	UpdateGrid();
	CheckCollision(dt);


}
void SceneGame::CheckDropItem()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::BUTTERFLY)
		{
			Butterfly *but = dynamic_cast<Butterfly*>(listObj[i]);

			if (but->GetStatus() == INACTIVE && but->IsDropItem() == false)
			{
				but->SetDropItem(true);
				if (but->GetIndexItem() == eType::STRENGTH_5)
				{
					Strength *streng = new Strength(but->GetX(), but->GetY(), STRENGTH_5);
					Unit *unit1 = new Unit(grid, streng, streng->GetX(), streng->GetY());
				}
				else if (but->GetIndexItem() == eType::STRENGTH_10)
				{
					Strength *streng1 = new Strength(but->GetX(), but->GetY(), STRENGTH_10);
					Unit *unit2 = new Unit(grid, streng1, streng1->GetX(), streng1->GetY());
				}
				else if (but->GetIndexItem() == eType::BONUS_5)
				{
					Bonus *bonus = new Bonus(but->GetX(), but->GetY(), BONUS_5);
					Unit *unit3 = new Unit(grid, bonus, bonus->GetX(), bonus->GetY());
				}
				else if (but->GetIndexItem() == eType::BONUS_10)
				{
					Bonus *bonus1 = new Bonus(but->GetX(), but->GetY(), BONUS_10);
					Unit *unit4 = new Unit(grid, bonus1, bonus1->GetX(), bonus1->GetY());
				}
				else if (but->GetIndexItem() == eType::FIREWHEEL)
				{
					Firewheel *firewheel = new Firewheel(but->GetX(), but->GetY());
					Unit *unit5 = new Unit(grid, firewheel, firewheel->GetX(), firewheel->GetY());
				}
				else if (but->GetIndexItem() == eType::THROWINGSTAR)
				{
					Throwingstar *throwing = new Throwingstar(but->GetX(), but->GetY());
					Unit *unit6 = new Unit(grid, throwing, throwing->GetX(), throwing->GetY());
				}
				else if (but->GetIndexItem() == eType::WINDMILL)
				{
					Windmillstar *windmill = new Windmillstar(but->GetX(), but->GetY());
					Unit *unit6 = new Unit(grid, windmill, windmill->GetX(), windmill->GetY());
				}
				else if (but->GetIndexItem() == eType::TIMEFREEZE)
				{
					Timefreeze *timefreeze = new Timefreeze(but->GetX(), but->GetY());
					Unit *unit7 = new Unit(grid, timefreeze, timefreeze->GetX(), timefreeze->GetY());
				}
				else if (but->GetIndexItem() == eType::RESTORE)
				{
					Restore *restore = new Restore(but->GetX(), but->GetY());
					Unit *unit8 = new Unit(grid, restore, restore->GetX(), restore->GetY());

				}
			}
		}
		else if (listObj[i]->GetType() == eType::THEBIRD)
		{
			TheBird *bird = dynamic_cast<TheBird*>(listObj[i]);

			if (bird->GetStatus() == INACTIVE && bird->IsDropItem() == false)
			{
				bird->SetDropItem(true);
				if (bird->GetIndexItem() == eType::STRENGTH_5)
				{
					Strength *streng = new Strength(bird->GetX(), bird->GetY(), STRENGTH_5);
					Unit *unit1 = new Unit(grid, streng, streng->GetX(), streng->GetY());
				}
				else if (bird->GetIndexItem() == eType::STRENGTH_10)
				{
					Strength *streng1 = new Strength(bird->GetX(), bird->GetY(), STRENGTH_10);
					Unit *unit2 = new Unit(grid, streng1, streng1->GetX(), streng1->GetY());
				}
				else if (bird->GetIndexItem() == eType::BONUS_5)
				{
					Bonus *bonus = new Bonus(bird->GetX(), bird->GetY(), BONUS_5);
					Unit *unit3 = new Unit(grid, bonus, bonus->GetX(), bonus->GetY());
				}
				else if (bird->GetIndexItem() == eType::BONUS_10)
				{
					Bonus *bonus1 = new Bonus(bird->GetX(), bird->GetY(), BONUS_10);
					Unit *unit4 = new Unit(grid, bonus1, bonus1->GetX(), bonus1->GetY());
				}
				else if (bird->GetIndexItem() == eType::FIREWHEEL)
				{
					Firewheel *firewheel = new Firewheel(bird->GetX(), bird->GetY());
					Unit *unit5 = new Unit(grid, firewheel, firewheel->GetX(), firewheel->GetY());
				}
				else if (bird->GetIndexItem() == eType::THROWINGSTAR)
				{
					Throwingstar *throwing = new Throwingstar(bird->GetX(), bird->GetY());
					Unit *unit6 = new Unit(grid, throwing, throwing->GetX(), throwing->GetY());
				}
				else if (bird->GetIndexItem() == eType::WINDMILL)
				{
					Windmillstar *windmill = new Windmillstar(bird->GetX(), bird->GetY());
					Unit *unit6 = new Unit(grid, windmill, windmill->GetX(), windmill->GetY());
				}
				else if (bird->GetIndexItem() == eType::TIMEFREEZE)
				{
					Timefreeze *timefreeze = new Timefreeze(bird->GetX(), bird->GetY());
					Unit *unit7 = new Unit(grid, timefreeze, timefreeze->GetX(), timefreeze->GetY());
				}
				else if (bird->GetIndexItem() == eType::RESTORE)
				{
					Restore *restore = new Restore(bird->GetX(), bird->GetY());
					Unit *unit8 = new Unit(grid, restore, restore->GetX(), restore->GetY());

				}
			}
		}
	}
}
void SceneGame::SetInactiveEnemy()
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (!camera->checkObjectInCamera(listObj[i]->GetX(), listObj[i]->GetY(), listObj[i]->GetWidth(), listObj[i]->GetHeight()))
		{
			if (dynamic_cast<GunnerBullet*>(listObj[i]) && !camera->checkObjectInCamera(listObj[i]->GetX(), listObj[i]->GetY(), listObj[i]->GetWidth(), listObj[i]->GetHeight()))
			{
				dynamic_cast<GunnerBullet*>(listObj[i])->SetFinish(true);
			}
			else
			{
				Enemy *enemy = dynamic_cast<Enemy*>(listObj[i]);
				if (enemy == NULL || dynamic_cast<Butterfly*>(listObj[i]) != NULL || dynamic_cast<TheBird*>(listObj[i]) != NULL)
					continue;
				if (enemy->GetStatus() == ACTIVE)
				{
					enemy->SetStatus(INACTIVE);
				}
			}

		}


		
	}
	if (!camera->checkObjectInCamera(ninja->subWeapon.back()->GetX(), ninja->subWeapon.back()->GetY(), ninja->subWeapon.back()->GetWidth(), ninja->subWeapon.back()->GetHeight()))
	{
		ninja->subWeapon.back()->SetFinish(true);
	}
}
void SceneGame::UpdateGrid()
{
	for (int i = 0; i < listUnit.size(); i++)
	{
		LPGAMEOBJECT obj = listUnit[i]->GetObj();

		//if (obj->IsEnable() == false)
		//	continue;

		float newPos_x, newPos_y;
		obj->GetPosition(newPos_x, newPos_y);
		listUnit[i]->Move(newPos_x, newPos_y);
	}
}
void SceneGame::Render()
{
	if (!isGameOver)
	{
		TileMap->DrawMap(camera, 255, 255, 255);

		for (UINT i = 0; i < listObj.size(); i++)
		{
			listObj[i]->Render(camera);
		}


		ninja->Render(camera);

		board->Render(ninja, 3, StateCurrent, GAME_TIME_MAX - gameTime->GetTime());
	}
	else
	{
		//DebugOut(L"\nNOW = %d\nEND = %d\nRET =%d \n", GetTickCount(),EndTime, GetTickCount() - EndTime);
		if (GetTickCount() - EndTime < 5000)
		{
			switch (count++)
			{
			case 1:
				TileMap->DrawMap(camera, 243, 0, 200);
				break;
			case 2:
				TileMap->DrawMap(camera, 233,86,60);
				break;
			case 3:
				TileMap->DrawMap(camera, 255,125,34);
				break;
			case 4:
				count = 1;
				//TileMap->DrawMap(camera, 193, 47, 0);
				TileMap->DrawMap(camera, 255, 255, 255);
				break;
			default:
				TileMap->DrawMap(camera, 255, 255, 255);
				break;
			}
			for (UINT i = 0; i < listObj.size(); i++)
			{
				listObj[i]->Render(camera);
			}


			ninja->Render(camera);

			board->Render(ninja, 3, StateCurrent, GAME_TIME_MAX - gameTime->GetTime());
		}
		else
		{
			TileMap->DrawMap(camera, 0, 0, 0);
			Text.Draw(200, 200, "GAME OVER");
		}
	}

	//	for (int i = 0; i < 4; i++)
	//	{
	//		TimeWaitedChangeColorBackground = GetTickCount();
	//		if (TimeWaitedChangeColorBackground - timeWait >= LimitTimeWaitChangeColorBackground)
	//		{
	//			TimeWaited_UseCross_ChangeColorBackground = 0;
	//			LimitTimeWait_UseCross_ChangeColorBackground = rand() % 100;
	//		switch (i)
	//		{
	//		case 1:
	//			timeWait = GetTickCount();
	//			TileMap->DrawMap(camera, 243, 0, 200);
	//			break;
	//		case 2:
	//			TileMap->DrawMap(camera, 0, 3, 189);
	//			break;
	//		case 3:
	//			TileMap->DrawMap(camera, 255, 125, 34);
	//			break;
	//		case 4:
	//			TileMap->DrawMap(camera, 193, 47, 0);
	//			break;
	//		}

	//	}
	//}
	
}


void SceneGame::LoadMap(eType x)
{
	mapCurrent = x;

	switch (x)
	{
	case eType::MAP1:
		grid->SetFile("Resources/map/readObjectMap1.txt");
		TileMap->LoadMap(eType::MAP1);

		camera->SetAllowFollowNinja(true);

		camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
		camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

		camera->SetPosition(0, 0);

		camera->SetAllowFollowNinja(true);

		ninja->SetPosition(NINJA_POSITION_DEFAULT);
		ninja->SetPositionBackup(NINJA_POSITION_DEFAULT);
		StateCurrent = 1;
		break;
	case eType::MAP2:
		grid->SetFile("Resources/map/readObjectMap2.txt");
		TileMap->LoadMap(eType::MAP2);

		camera->SetAllowFollowNinja(true);

		camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
		camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

		camera->SetPosition(0, 0);

		camera->SetAllowFollowNinja(true);

		ninja->SetPosition(200, 50);
		ninja->SetPositionBackup(NINJA_POSITION_DEFAULT);
		StateCurrent = 2;
		break;
	}

	ResetResource();
}

void SceneGame::CheckCollision(DWORD dt)
{
	//CheckCollisionWeapon(listObj); // kt va chạm vũ khí với các object nền

	//CheckCollisionSimonWithItem();
	//CheckCollisionSimonWithObjectHidden();
	//CheckCollisionSimonWithGate(); //va chạm với cửa

	//if (!isProcessingGoThroughTheDoor1 && !isProcessingGoThroughTheDoor2) // ko phải đang xử lí qua cửa
	CheckCollisonOfNinja(dt); // kt vũ khí với enemy và simon với enemy

	//CheckCollisionWithBoss(); // kt vũ khí với enemy và simon với boss

}

void SceneGame::CheckCollisonOfNinja(DWORD dt)
{
	//ninja->CollisionWithEnemy(&listObj);

	ninja->CollisionWeaponWithObj(&listObj);
	ninja->CollisionWeaponWithNinja(&listObj);
	ninja->CollisionWithEnemyArea(&listObj);
	CollisionWithItems(dt);

}

void SceneGame::CollisionWithItems(DWORD dt)
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<Item*> (listObj[i]))
		{
			if (!dynamic_cast<Item*>(listObj[i])->GetFinish() && dynamic_cast<Item*>(listObj[i])->isCollitionObjectWithObject(ninja))
			{
				switch (dynamic_cast<Item*>(listObj[i])->GetType())
				{
				case eType::STRENGTH_5:
					ninja->SetStrength(ninja->GetStrength() + 5);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::STRENGTH_10:
					ninja->SetStrength(ninja->GetStrength() + 10);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::TIMEFREEZE:
					ninja->SetFreeze(1);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					timeBeginFreeze = GetTickCount();
					break;
				case eType::BONUS_5:
					ninja->SetScore(ninja->GetScore() + 500);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::BONUS_10:
					ninja->SetScore(ninja->GetScore() + 1000);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::RESTORE:
					ninja->SetHealth(ninja->GetHealth() + 6);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::THROWINGSTAR:
					ninja->WeaponCollect(WPTHROWINGSTAR);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::FIREWHEEL:
					ninja->WeaponCollect(WPFIREWHEEL);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				case eType::WINDMILL:
					ninja->WeaponCollect(WPWINDMILLSTAR);
					dynamic_cast<Item*> (listObj[i])->SetFinish(true);
					break;
				default:
					break;
				}
			}
		}
	}
	//DebugOut(L"strenth = %d\tscore = %d\thelth = %d\n", ninja->GetStrength(), ninja->GetScore(), ninja->GetHealth());

}

