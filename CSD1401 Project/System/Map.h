/*!
@file       Map.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains declaration of functions used for the map
*//*_______________________________________________________________________*/

#pragma once
#include "SingletonTemplate.h"
#include "cprocessing.h"
#include <string>
#include <map>
#include <vector>

enum TILE_TYPE
{
	NONE = 0,
	GROUND = 1,
	GRASS = 2,
	FLOWER = 3,
	HORIZONTAL_LEFT_ROAD = 101,
	HORIZONTAL_MIDDLE_ROAD = 102,
	HORIZONTAL_RIGHT_ROAD = 103,
	VERTICAL_LEFT_ROAD = 104,
	VERTICAL_MIDDLE_ROAD = 105,
	VERTICAL_RIGHT_ROAD = 106,
	CORNER_TOP_LEFT_ROAD = 107,
	CORNER_TOP_RIGHT_ROAD = 108,
	CORNER_BOTTOM_LEFT_ROAD = 109,
	CORNER_BOTTOM_RIGHT_ROAD = 110,
	JUNCTION_MIDDLE_TOP_ROAD = 111,
	JUNCTION_MIDDLE_LEFT_ROAD = 112,
	JUNCTION_MIDDLE_RIGHT_ROAD = 113,
	JUNCTION_MIDDLE_BOTTOM_ROAD = 114,
	JUNCTION_MIDDLE_ROAD = 115,
	STARTPOINT = 201,
	ENDPOINT = 202,
	TOTAL
};

struct Tile
{
	CP_Vector pos;
	TILE_TYPE tileType;
};

class Map : public SingletonTemplate<Map>
{
	friend class SingletonTemplate<Map>;

private:
	static const char* TILE_ASSETS_FILE_PATH;
	const int TILE_WIDTH = 16;
	const int TILE_HEIGHT = 16;
	const int NUM_TILES_ROW = 32;
	const int NUM_TILES_COLUMN = 32;

	Tile** map;

	std::vector<TILE_TYPE> tileTypesVector;

public:
	std::string getImageFilePath(TILE_TYPE tileType);
	bool loadMapTileImages();

	bool loadMap(std::string fileName);
	bool saveMap(std::string fileName);

	bool renderMap();

	bool clearMap();

	std::map<TILE_TYPE, CP_Image> imageMap;
};