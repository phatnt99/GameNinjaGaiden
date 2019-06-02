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
#include "Windmillstar.h"
#define GAME_TIME_MAX 150

#define REGION_CREATE_PANTHER_LEFT 1090.0f
#define REGION_CREATE_PANTHER_RIGHT 2305.0f

#define CAMERA_POSITION_Y_LAKE 374.0f

#define CAMERA_BOUNDARY_LAKE_LEFT 3075.0f
#define CAMERA_BOUNDARY_LAKE_RIGHT (4111.0f-SCREEN_WIDTH)

#define CAMERA_BOUNDARY_BOSS_RIGHT (5648.0f - SCREEN_WIDTH)

#define CROSS_LIMITTIME 1000 // thời gian tối đa khi dùng Cross

#define TIME_FOR_THIEF 1000
#define TIME_WAIT_FOR_PROCESS_THIEF 2500

class SceneGame : public Scene
{
private:

	int iii = 0;
	Ninja * ninja;
	Map * TileMap;
	Camera *camera;
	Grid *grid;
	Board *board;
	vector<LPGAMEOBJECT> listObj;
	vector<Unit*> listUnit;
	GameTime * gameTime;
	int StateCurrent;

	CSprite * spriteLagerHeart;
	int GameOverSelect;

	eType mapCurrent;
	int timeFreeze = 5000;
	DWORD timeBeginFreeze;
	Alphabet Text;
	bool isGameOver;
	DWORD EndTime;
	DWORD TimeWaitedChangeColorBackground; // thời gian đã chờ của việc thay đổi màu nền
	DWORD LimitTimeWaitChangeColorBackground = 3000; // thời gian cần chờ để đỏi màu nền
	DWORD timeWait;

	int count = 1;
public:
	SceneGame();
	~SceneGame();

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();

	void InitGame(); // khởi tạo lại như chơi từ đầu
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
	//Item * GetNewItem(int Id, eType Type, float X, float Y);


	void ProcessClearState3(DWORD dt);
	void ProcessInvisibilityPotion(DWORD dt);
	void ProcessCross(DWORD dt);

	void ReplayMusicGame();
};
#endif