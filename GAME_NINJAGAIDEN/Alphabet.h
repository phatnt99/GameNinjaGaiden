#ifndef __ALPHABET_H__
#define __ALPHABET_H__

#include "Sprite.h"
#include "Texture.h"
#include "define.h"

#include "TextureManager.h"

class Alphabet
{
private:
	CSprite * sprite;
	CTexture * texture;

public:
	Alphabet();
	~Alphabet();
	void Draw(float x, float y, const string & s);
};





#endif 



