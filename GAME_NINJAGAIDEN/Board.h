#ifndef __BOARD_H__
#define __BOARD_H__

#include "Sprite.h"
#include "Texture.h"
#include "Camera.h"
#include "define.h"
#include "Alphabet.h"
#include "Ninja.h"
#include "BoardHealth.h"
#include "TextureManager.h"

#define BOARD_DEFAULT_POSITION_X 0.0f
#define BOARD_DEFAULT_POSITION_Y 0.0f

class Board
{
private:
	Alphabet alpha;
	BoardHealth * boardHealth;

	CTexture *texture;
	CSprite * sprite;
	float x, y;

	string FillNumber(string s, UINT MaxNumber);


	//GSprite * _spriteIconDoubleShot;

public:
	Board(float X, float Y);
	void Render(Ninja * ninja, int state1, int state2, int RemainingTime);
	~Board();

	void SetTexture(CTexture * tex);
};





#endif 


