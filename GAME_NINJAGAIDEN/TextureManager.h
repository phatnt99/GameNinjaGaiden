#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <unordered_map>
#include "define.h"
#include "Texture.h"
class TextureManager
{
	unordered_map<eType, CTexture*> _ArrTextures;

public:
	static TextureManager* __Instance;
	static TextureManager* GetInstance();

	void AddTexture(eType type, CTexture* texture);
	CTexture* GetTexture(eType type);

	void LoadResource();

	TextureManager();
	~TextureManager();
};

#endif