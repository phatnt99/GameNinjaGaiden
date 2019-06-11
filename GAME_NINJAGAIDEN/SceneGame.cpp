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
				//DebugOut(L"\nVa cham OBJH\n");
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
	if (Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_X) && !ninja->isAttacking && !ninja->GetIsClimbing())
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
		{
			if (ninja->isAttacking) //đứng mà đang đánh thì đánh xong mới dc ngồi

			{
				ninja->SetSpeed(0, 0);
			}
			else
				ninja->Sit();
		}
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT) && !ninja->isAttacking)
		{
			ninja->ResetSit();
			ninja->Right();
			ninja->Go();
		}
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) && !ninja->isAttacking)
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
	//if (ninja->isAttacking)
	//{
	//	return;
	//}
	
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (!ninja->isJumping && !ninja->isAttacking || ninja->isJumping)
		{
			if (ninja->isJumping && ninja->GetDirection() == 1)
			{
				ninja->Right();
				ninja->Go();
			}
			else if (ninja->isJumping && ninja->GetDirection() == -1)
			{
				ninja->Right();
				ninja->Go(0.09f);
			}
			else
			{
				ninja->Right();
				ninja->Go();
			}
		}
	}
	else
	{
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			if (!ninja->isJumping && !ninja->isAttacking || ninja->isJumping)
			{
				if (ninja->isJumping && ninja->GetDirection() == -1)
				{
					ninja->Left();
					ninja->Go();
				}
				else if (ninja->isJumping && ninja->GetDirection() == 1)
				{
					ninja->Left();
					ninja->Go(0.09f);
				}
				else
				{
					ninja->Left();
					ninja->Go();
				}
			}
		}
		else
		{
			if (ninja->isAttacking && ninja->isSitting)
			{
				//float vx, vy;
				//ninja->GetSpeed(vx, vy);
				ninja->SetSpeed(0, 0);
			}
			else
			{
				ninja->Stop();
			}
			//if(ninja->subWeapon.front()->GetFinish() == true)

		}

	}
}

void SceneGame::OnKeyDown(int KeyCode)
{

	if (KeyCode == DIK_H)
	{
		ninja->GetFullHeath();
	}

	if (isGameOver)
	{
		if (KeyCode == DIK_RETURN)
		{
			if (StateCurrent == 3)
				mapCurrent = MAP2;

			InitGame(mapCurrent);
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
		if (Game::GetInstance()->IsKeyDown(DIK_X) && ninja->isAttacking == false && !ninja->GetIsClimbing())
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
			sound->Play(eSound::jump);
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

	sound = Sound::GetInstance();
	gameTime = new GameTime();
	TileMap = new Map();


	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	ninja = new Ninja(camera);
	grid = new Grid(9600, 480);
	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);
	InitGame();
}

void SceneGame::InitGame(eType map)
{
	LoadMap(map);
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
	remainTime = 0;
	count = 1;
	boss = NULL;

	ReplayMusicGame(StateCurrent);
}


void SceneGame::Update(DWORD dt)
{
	if (isGameOver)
		return;
	if(GAME_TIME_MAX - gameTime->GetTime() < 10)
		sound->Play(eSound::warningtime);
	//hết thời gian / hết máu -> chết
	if (gameTime->GetTime() >= GAME_TIME_MAX || ninja->GetHealth() < 1)
	{
		if (ninja->GetIsDeadth())
		{

			ninja->GetSprite()->SelectFrame(NINJA_DEADTH);

			if (GetTickCount() - ninja->timeWait > 4000 || ninja->GetLives() - 1 < 0)
			{
				bool ret = ninja->LoseLife();

				if (ret)
				{
					camera->RestorePosition();
					camera->RestoreBoundary();

					gameTime->SetTime(0);
					if(StateCurrent == 3) // nếu đang ở màn 3 thì về màn 2
						LoadMap(MAP2);
					ResetResource();
				}
				else
				{
					EndTime = GetTickCount();
					isGameOver = true;
					sound->StopAll();
				}
			}
			else
			{
				sound->StopAll();
				sound->Play(eSound::loselife);
			}
		}
		else
		{
			ninja->SetDeadth();
			ninja->timeWait = GetTickCount();
		}
	}
	//rơi xuống vực -> chết
	else if (ninja->isFall)
	{
		if (GetTickCount() - ninja->timeWait > 4000 || ninja->GetLives() - 1 < 0)
		{
			bool ret = ninja->LoseLife();
			ninja->GetSprite()->SelectFrame(8);

			if (ret)
			{
				camera->RestorePosition();
				camera->RestoreBoundary();

				gameTime->SetTime(0);
				if (StateCurrent == 3) // nếu đang ở màn 3 thì về màn 2
					LoadMap(MAP2);
				ResetResource();
			}
			else
			{
				EndTime = GetTickCount();
				isGameOver = true;
				sound->StopAll();
			}
		}
		else
		{
			sound->StopAll();
			sound->Play(eSound::loselife);
		}

		return;
	}
	else if (ninja->GetIsNewStage())
	{
		camera->RestorePosition();
		camera->RestoreBoundary();

		gameTime->SetTime(0);

		LoadMap(mapCurrent == MAP1 ? MAP2 : (mapCurrent == MAP2 ? MAP3 : mapCurrent));

		ResetResource();
		ninja->SetIsNewStage(false);
	}
	else
	{
		listObj.clear();
		listUnit.clear(); // lay obj co trong vung camera thong qua unit
		grid->GetListObject(listUnit, camera);

		for (UINT i = 0; i < listUnit.size(); i++)
		{
			LPGAMEOBJECT obj = listUnit[i]->GetObj();
			listObj.push_back(obj);
			if (obj->GetType() == BOSS)
				boss = dynamic_cast<Boss*>(obj);
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
					bird->Update(dt, ninja->GetX(), ninja->GetY(), ninja->GetDirection(), &listObj);
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
				if (dynamic_cast<Boss*>(listObj[i]))
				{
					Boss *boss = dynamic_cast<Boss*>(listObj[i]);
					boss->Update(dt, ninja->GetX(), grid, &listObj);
				}
				else
					obj->Update(dt, &listObj);
			}
		}
		else
			sound->Play(eSound::timefreez);

		if (boss != nullptr)
		{
			if (boss->GetIsDeath() && remainTime == 0)
			{
				if (ninja->GetStrength() == 0)
				{
					ninja->SetScore(ninja->GetScore() + 6000); //điểm kill boss
					remainTime = GAME_TIME_MAX*1.0 - gameTime->GetTime();
				}
				else
					ninja->SetStrength(ninja->GetStrength() - 1);
			}

			if (boss->GetIsDeath() && remainTime > 0)
			{
				sound->Play(eSound::remainingtime);
				ninja->SetScore(ninja->GetScore() + 90);
				remainTime -= 0.5;
				//DebugOut(L"\nTRU CON %f\n", remainTime);
				if (remainTime == 0)
					remainTime = -1;
			}
		}


		CheckDropItem();
		SetInactiveEnemy();
		UpdateGrid();
		CheckCollision(dt);

	}

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
			if (dynamic_cast<Weapon*>(listObj[i]) && !camera->checkObjectInCamera(listObj[i]->GetX(), listObj[i]->GetY(), listObj[i]->GetWidth(), listObj[i]->GetHeight()))
			{
				dynamic_cast<Weapon*>(listObj[i])->SetFinish(true);
			}
			else
			{
				Enemy *enemy = dynamic_cast<Enemy*>(listObj[i]);
				if (enemy == NULL || dynamic_cast<Butterfly*>(listObj[i]) != NULL || dynamic_cast<TheBird*>(listObj[i]) != NULL)
					continue;
				if (enemy->GetStatus() == ACTIVE)
				{
					//DebugOut(L"INACTIVE\n");
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

		if(!ninja->isFall)
			ninja->Render(camera);

		if (remainTime > 0)
		{
			//DebugOut(L"if 1\tisDeath = %d\t remain = %f\n", boss->GetIsDeath() == true ? 1 : 0, remainTime);
			board->Render(ninja, 3, StateCurrent, remainTime, boss);

		}
		if (remainTime == 0)
		{
			//DebugOut(L" if 2\t isDeath = %d\t remain = %d\n", boss->GetIsDeath() == true ? 1 : 0, remainTime);
			board->Render(ninja, 3, StateCurrent, GAME_TIME_MAX - gameTime->GetTime(), boss);

		}
		else if (remainTime <= -1)
		{
			sound->StopAll();
			TileMap->DrawMap(camera, 0, 0, 0);
			Text.Draw(200, 200, "GAME CLEAR");
		}

	}
	else
	{
		//DebugOut(L"\nNOW = %d\nEND = %d\nRET =%d \n", GetTickCount(),EndTime, GetTickCount() - EndTime);
		if (GetTickCount() - EndTime < 4000)
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

			board->Render(ninja, 3, StateCurrent, GAME_TIME_MAX - gameTime->GetTime(), boss);
			sound->Play(eSound::loselife);
		}
		else
		{
			sound->StopAll();
			TileMap->DrawMap(camera, 0, 0, 0);
			Text.Draw(200, 200, "GAME OVER");
		}
	}

	
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
	case eType::MAP3:
		grid->SetFile("Resources/map/readObjectMap3.txt");
		TileMap->LoadMap(eType::MAP3);

		camera->SetAllowFollowNinja(true);

		camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
		camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

		camera->SetPosition(0, 0);

		camera->SetAllowFollowNinja(true);

		ninja->SetPosition(50, 309);
		ninja->SetPositionBackup(50, 309);
		StateCurrent = 3;
		break;
	}

	ResetResource();
}

void SceneGame::CheckCollision(DWORD dt)
{
	CheckCollisonOfNinja(dt); // kt vũ khí với enemy và simon với enemy

}

void SceneGame::CheckCollisonOfNinja(DWORD dt)
{
	ninja->CollisionWithEnemy(&listObj);

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
				sound->Play(eSound::soundCollectItem);
			}
		}
	}
}

void SceneGame::ReplayMusicGame(int map)
{
	sound->StopAll();// tắt hết nhạc
	switch (map)
	{
	case 1:
		sound->Play(eSound::musicState1, true); // mở lại nhạc nền
		break;
	case 2:
		sound->Play(eSound::musicState2, true); // mở lại nhạc nền
		break;
	case 3:
		sound->Play(eSound::musicState3, true); // mở lại nhạc nền
		break;

	}

}

