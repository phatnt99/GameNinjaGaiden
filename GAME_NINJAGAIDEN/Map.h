#ifndef __MAP_H__
#define __MAP_H__

#include "TextureManager.h"
#include "Sprite.h"
#include "define.h"

class Map
{
private:
	CTexture *texture;
	CSprite *sprite;

	int ColumnTile, RowTile, TotalTiles;

	int ColumnMap, RowMap;

	int HeightBoard; // chiều cao board

	int TileMap[500][500];

public:
	Map();
	~Map();
	void LoadMap(eType type);
	void ReadMapTXT(char * filename);
	void DrawMap(Camera * camera, int R, int G, int B);

	int GetMapWidth();
	int GetMapHeight();
};


#endif