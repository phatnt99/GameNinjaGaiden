#ifndef __NINJA_H__
#define __NINJA_H__


#include "GameObject.h"
#include "Weapon.h"
#include "Katana.h"
#include "debug.h"
#include "Enemy.h"
#include "Thief.h"
#include "Dog.h"
#include "Bird.h"
#include "Witch.h"
#include "Soldier.h"
#include "Brick.h"
#include "Sword.h"
#include "Butterfly.h"
#include "Effect.h"
#include "Item.h"
#include "WPThrowingStar.h"
#include "WPFireWheel.h"
#include "ObjectHidden.h"
#include "Gunner.h"
#include "Runner.h"
#include "Bom.h"
#include "GunnerBullet.h"
#include "Bullet.h"
#include "WPWindmillStar.h"
//#include "Sound.h"
//#include "ThrowingAxe.h"
//#include "Dagger.h"
//#include "HolyWater.h"
//#include "StopWatch.h"
//#include "Boomerang.h"

#define NINJA_POSITION_DEFAULT  0.0f, 150.0f


#define NINJA_BBOX_WIDTH 50
#define NINJA_BBOX_HEIGHT 74
#define NINJA_BBOX_SITTING_HEIGHT 74
#define NINJA_BBOX_JUMPING_HEIGHT 74

#define PULL_UP_NINJA_AFTER_SITTING 2.0f // Kéo NINJA lên 18px sau khi ngồi rồi đứng dậy, tránh overlaping do BBOX bottom thu lại khi ngồi

#define NINJA_VJUMP 0.50f
#define NINJA_VJUMP_HURTING 0.5f // nhảy lúc bị đau
#define PULL_UP_NINJA_AFTER_JUMPING 2.0f // Kéo NINJA lên 18px sau khi nhảy, tránh overlaping do BBOX bottom thu lại khi nhảy

#define NINJA_GRAVITY 0.005f 
#define NINJA_GRAVITY_JUMPING 0.001f 
#define NINJA_GRAVITY_HURTING 0.003f

#define NINJA_WALKING_SPEED 0.3f //0.2f 

#define NINJA_STATE_IDLE 0
#define NINJA_STATE_WALKING 1

#define NINJA_ANI_WALKING_BEGIN 5
#define NINJA_ANI_WALKING_END 7

#define NINJA_ANI_IDLE 1

#define NINJA_ANI_JUMPING_BEGIN 16
#define NINJA_ANI_JUMPING_END 19

#define NINJA_ANI_SITTING 9
#define NINJA_DEADTH 19



/*Ani đang ngồi đánh*/
#define NINJA_ANI_SITTING_ATTACKING_BEGIN 10
#define NINJA_ANI_SITTING_ATTACKING_END 12

/*Ani đang đứng đánh*/
#define NINJA_ANI_STANDING_ATTACKING_BEGIN 2
#define NINJA_ANI_STANDING_ATTACKING_END 4


/* Time Ani attack */
#define NINJA_TIME_WAIT_ANI_ATTACKING 120// thời gian thời của mỗi frame khi tấn công


#define NINJA_ANI_HURTING 19


#define NINJA_ANI_CLIMB 24

#define NINJA_ANI_CLIMB_GO_UP_BEGIN 24
#define NINJA_ANI_CLIMB_GO_UP_END 25




#define NINJA_SPEED_ONSTAIR 0.09f 

#define NINJA_ANI_STAIR_STANDING_UP 12
#define NINJA_ANI_STAIR_STANDING_DOWN 10


#define TIME_FREEZE_MAX 500


#define NINJA_DEFAULT_HEALTH 16
#define NINJA_DEFAULT_STRENGTH 0
#define NINJA_DEFAULT_SCORE 0
#define NINJA_DEFAULT_LIVES 2
#define NINJA_DEFAULT_RESTORE 6

#define NINJA_UNTOUCHABLE_TIME 1000 


class Ninja : public GameObject
{
private:
	CSprite * _sprite_deadth;

	int strength; // strength cua ninja
	int Lives; // số mạng của NINJA
	int score; // điểm

	bool isFreeze; // Trạng thái đóng băng thay đổi màu liên tục
	DWORD TimeFreeze; // thời gian đã đóng băng

	D3DXVECTOR2 PositionBackup;

	int flag = 0;
	bool isWalking_Backup;
	bool isJumping_Backup;
	bool isSitting_Backup;
	bool isAttacking_Backup;
	int directionY_Backup;
	int directionAfterGo;

	float AutoGoX_Distance; // khoảng cách NINJA cần tự đi
	float AutoGoX_Speed; // vận tốc đi tự động
	float AutoGoX_DirectionGo; // hướng tự động đi
	float AutoGoX_Backup_X; // lưu vị trí trước khi đi tự động

	bool isAutoGoX = 0; // đang ở chế độ auto go?

	bool isDeadth;
	bool isClimbing;
	bool isClimbUp;
	bool isGetNewStage;

	bool untouchable;
	DWORD untouchable_start;

	eType TypeWeaponCollect = eType::WPWINDMILLSTAR; // loại vũ khí phụ đang giữ

	Camera * camera;
	//Sound * sound;

	vector<Effect*> listEffect;

public:
	bool isUp;
	bool isAttacking;
	bool isHurting;
	bool isWalking;
	bool isJumping;
	bool isSitting;


	int directionY; // hướng đi theo trục y của NINJA


	bool isCollisionAxisYWithBrick = false; // Đang va chạm với đất theo trục y

	DWORD TimeWaitedAfterDeath;


public:
	Ninja(Camera* camera);
	~Ninja();

	unordered_map<eType, Weapon*> mapWeapon;
	list<Weapon*> subWeapon;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void GetBoundingBoxBrick(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

	void Sit();

	void Stop();
	void ResetSit();

	void Go();
	void Jump();
	void Right();
	void Left();

	void SetHurt();

	void SetStrength(int h);
	int GetStrength();

	void CollisionWithBrick(const vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithEnemyArea(const vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWeaponWithObj(const vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWeaponWithNinja(const vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithEnemy(const vector<LPGAMEOBJECT> *coObjects = NULL);
	//void CollisionWithObjHidden(const vector<LPGAMEOBJECT> *coObjects = NULL);
	//void CollisionIsOnStair(vector<LPGAMEOBJECT> *coObjects = NULL);
	//bool isCollisionWithItem(Item * objItem);

	void Attack(eType typeWeapon);

	int GetLives();
	void SetLives(int l);
	int GetScore();
	void SetScore(int s);

	bool GetFreeze();
	void SetFreeze(int f);
	void UpdateFreeze(DWORD dt);

	void StartUntouchable();



	void SetAutoGoX(int DirectionGo, int DirectionBackup, float Dx, float Speed); // set các thông số auto và backup các trạng thái hiện tại
	bool GetIsAutoGoX(); // kiểm tra có đang ở chế độ auto go?

	void RestoreBackupAutoGoX(); // khôi phục trạng thái 

	bool LoseLife(); // thiết lập lại 1 số thứ sau khi NINJA mất mạng
	void SetPositionBackup(float X, float Y);  // lưu vị trí cần backup để NINJA die thì bắt đầu lại từ đây


	void SetDeadth();
	bool GetIsDeadth();
	void SetIsDeadth(bool b);

	bool GetIsClimbing() { return isClimbing; }
	void SetIsClimbing(bool b) { isClimbing = b; }

	bool GetIsClimbUp() { return isClimbUp; }
	void SetIsClimbUp(bool b) { isClimbUp = b; }


	bool GetIsNewStage() { return isGetNewStage; }
	void SetIsNewStage(bool b) { isGetNewStage =b ; }
	eType GetTypeWeaponCollect();
	void SetTypeWeaponCollect(eType t);
	void WeaponCollect(eType t);
	bool IsUsingWeapon(eType typeWeapon);

	bool GetIsUseDoubleShot();
	void SetIsUseDoubleShot(bool b);

	void Init(); // khởi tạo lại các trạng thái, HeartCollect, Heath, Lives, Score
	void Reset(); // khởi tạo lại các trạng thái.
	bool CheckAABBActiveArea(float l,float t, float r, float b);
};






#endif