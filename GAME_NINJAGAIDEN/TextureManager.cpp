#include "TextureManager.h"

TextureManager* TextureManager::__Instance = NULL;

TextureManager * TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}

void TextureManager::AddTexture(eType type, CTexture *texture)
{
	_ArrTextures[type] = texture;
}

CTexture * TextureManager::GetTexture(eType type)
{
	return _ArrTextures[type];
}

void TextureManager::LoadResource()
{

	// Weapon
	AddTexture(eType::KATANA, new CTexture("Resources/Weapon/katana1.png",4,1,4));
	AddTexture(eType::WPTHROWINGSTAR, new CTexture("Resources/weapon/throwingstar.png", 2, 1, 2));
	AddTexture(eType::WPWINDMILLSTAR, new CTexture("Resources/weapon/windmillstar.png", 2, 1, 2));
	AddTexture(eType::BULLET, new CTexture("Resources/weapon/bullet.png"));
	AddTexture(eType::SWORD, new CTexture("Resources/weapon/sword.png",4,1,4));
	AddTexture(eType::WPFIREWHEEL, new CTexture("Resources/weapon/fire.png", 1, 1, 1));
	AddTexture(eType::GUNNERBULLET, new CTexture("Resources/weapon/gunner_bullet.PNG"));

	//player
	AddTexture(eType::NINJA, new CTexture("Resources/ninja1.png", 8, 4, 32));
	AddTexture(eType::NINJA_TRANSPARENT, new CTexture("Resources/ninja1_trans.png", 8, 4, 32));
	//AddTexture(eType::NINJA_DEADTH, new CTexture("Resources/simondeath.png"));

	//map
	AddTexture(eType::MAP1, new CTexture("Resources/map/tileset_map1.png", 14, 7, 98));
	AddTexture(eType::MAP2, new CTexture("Resources/map/tileset_map2.png", 47, 5, 235));

	//ground
	AddTexture(eType::BRICK_TRANSPARENT, new CTexture("Resources/ground/brick_transparent.png"));
	AddTexture(eType::OBJECT_HIDDEN, new CTexture("Resources/ground/brick_transparent.png"));
	AddTexture(eType::BUTTERFLY, new CTexture("Resources/ground/butterfly.png", 2,1,2));
	AddTexture(eType::THEBIRD, new CTexture("Resources/ground/bird2.png", 2, 1, 2));


	//BBOX
	AddTexture(eType::RENDERBBOX, new CTexture("Resources/bbox.png"));

	//enemy
	AddTexture(eType::BIRD, new CTexture("Resources/enemy/bird.png",2,1,2));
	AddTexture(eType::THIEF, new CTexture("Resources/enemy/thief.png",3,1,3));
	AddTexture(eType::WITCH, new CTexture("Resources/enemy/Witch.png", 3, 1, 3));
	AddTexture(eType::DOG, new CTexture("Resources/enemy/dog.png", 2, 1, 2));
	AddTexture(eType::SOLDIER, new CTexture("Resources/enemy/soldier.png", 4, 1, 4));
	AddTexture(eType::EFFECT, new CTexture("Resources/enemy/effectnormal.png", 4, 1, 4));
	AddTexture(eType::GUNNER, new CTexture("Resources/enemy/gunner.png", 2, 1, 2));
	AddTexture(eType::RUNNER, new CTexture("Resources/enemy/runner.PNG", 2, 1, 2));



	//item
	AddTexture(eType::STRENGTH, new CTexture("Resources/item/strength.PNG",2,1,2));
	AddTexture(eType::BONUS, new CTexture("Resources/item/bonus.PNG", 2, 1, 2));
	AddTexture(eType::FIREWHEEL, new CTexture("Resources/item/firewheel.PNG"));
	AddTexture(eType::THROWINGSTAR, new CTexture("Resources/item/throwingstar.PNG"));
	AddTexture(eType::TIMEFREEZE, new CTexture("Resources/item/timefreeze.PNG"));
	AddTexture(eType::RESTORE, new CTexture("Resources/item/restore.PNG"));
	AddTexture(eType::WINDMILL, new CTexture("Resources/item/windmill.PNG"));


	//board
	AddTexture(eType::ALPHABET, new CTexture("Resources/board/Font/alphabet.png", 26, 2, 37));
	AddTexture(eType::BOARD, new CTexture("Resources/board/blackboard.png", 1, 1, 1));
	AddTexture(eType::BOARD_TRANS, new CTexture("Resources/board/blackboard.png", 1, 1, 1, 0, 0, 0));
	AddTexture(eType::BOARDHEALTH, new CTexture("Resources/board/Bloodd.png", 2, 1, 2));



}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
