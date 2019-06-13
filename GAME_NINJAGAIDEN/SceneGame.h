#ifndef __SCENEGAME_H__
#define __SCENEGAME_H__

#include "Scene.h"
#include "Camera.h"
#include "Sprite.h"
#include "Ninja.h" 
#include "Camera.h"
#include "Map.h"
#include "GameTime.h"
#include "Grid.h"
#include "Thief.h"
#include "Brick.h"
#include "Bonus.h"
#include "Firewheel.h"
#include "Throwingstar.h"
#include "Timefreeze.h"
#include "Restore.h"
#include "Board.h"
#include "TheBird.h"
#include "Gunner.h"
#include "Runner.h"
#include "Boss.h"
#include "Windmillstar.h"
#include "Sound.h"
#define GAME_TIME_MAX 150





#define TIME_FOR_DEATH 4000

class SceneGame : public Scene
{
private:

	Ninja * ninja;
	Map * TileMap;
	Camera *camera;
	Grid *grid;
	Board *board;
	Sound * sound;
	vector<LPGAMEOBJECT> listObj;
	vector<Unit*> listUnit;
	GameTime * gameTime;
	int StateCurrent;

	eType mapCurrent;
	int timeFreeze = 5000;
	DWORD timeBeginFreeze;
	Alphabet Text;
	bool isGameOver;
	DWORD EndTime;
	float remainTime;
	Boss *boss;
	int count;
public:
	SceneGame();
	~SceneGame();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();

	void InitGame(eType map = MAP1); // khởi tạo lại như chơi từ đầu
	void ResetResource(); // reset lai resource khi simon mất 1 mạng



	void Update(DWORD dt);
	void UpdateGrid();
	void Render();
	void SetInactiveEnemy();

	void LoadMap(eType);



	void CheckCollision(DWORD dt);
	void CheckCollisonOfNinja(DWORD dt);
	void CheckDropItem();
	void CollisionWithItems(DWORD dt);

	void ReplayMusicGame(int map);
};
#endif