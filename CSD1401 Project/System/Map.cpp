/*!
@file       Map.c
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definitions of functions used for the map
*//*_______________________________________________________________________*/

#include "Map.h"
#include "CSVManager.h"
#include "cprocessing.h"
#include <vector>
#include <string>
#include <cmath>

const char* Map::TILE_ASSETS_FILE_PATH = "Assets/Tiles/";

/*!
@brief Constructor. Makes it set the map array to empty
*//*______________________________________________________________*/
Map::Map()
{
	resetMap(false);
	loadMapTileImages();
}

/*!
@brief	Gets the image file path based on the tileType of the tile
@param	TILE_TYPE tileType - type of the tile based off the enum TILE_TYPE
@return string - filePath of the file to get
*//*______________________________________________________________*/
std::string Map::getImageFilePath(TILE_TYPE tileType)
{
	std::string filePath = TILE_ASSETS_FILE_PATH;

	switch (tileType)
	{
	case GROUND:
		filePath += "Ground.png";
		break;
	case GRASS:
		filePath += "Grass.png";
		break;
	case FLOWER:
		filePath += "Flower.png";
		break;
	case HORIZONTAL_LEFT_ROAD:
		filePath += "HorizontalLeft.png";
		break;
	case HORIZONTAL_MIDDLE_ROAD:
		filePath += "HorizontalMiddle.png";
		break;
	case HORIZONTAL_RIGHT_ROAD:
		filePath += "HorizontalRight.png";
		break;
	case VERTICAL_LEFT_ROAD:
		filePath += "VerticalTop.png";
		break;
	case VERTICAL_MIDDLE_ROAD:
		filePath += "VerticalMiddle.png";
		break;
	case VERTICAL_RIGHT_ROAD:
		filePath += "VerticalBottom.png";
		break;
	case CORNER_TOP_LEFT_ROAD:
		filePath += "CornerTopLeft.png";
		break;
	case CORNER_TOP_RIGHT_ROAD:
		filePath += "CornerTopRight.png";
		break;
	case CORNER_BOTTOM_LEFT_ROAD:
		filePath += "CornerBottomLeft.png";
		break;
	case CORNER_BOTTOM_RIGHT_ROAD:
		filePath += "CornerBottomRight.png";
		break;
	case JUNCTION_MIDDLE_TOP_ROAD:
		filePath += "JunctionMiddleTop.png";
		break;
	case JUNCTION_MIDDLE_LEFT_ROAD:
		filePath += "JunctionMiddleLeft.png";
		break;
	case JUNCTION_MIDDLE_RIGHT_ROAD:
		filePath += "JunctionMiddleRight.png";
		break;
	case JUNCTION_MIDDLE_BOTTOM_ROAD:
		filePath += "JunctionMiddleBottom.png";
		break;
	case JUNCTION_MIDDLE_ROAD:
		filePath += "JunctionMiddle.png";
		break;
	case STARTPOINT:
		filePath += "StartPoint.png";
		break;
	case ENDPOINT:
		filePath += "EndPoint.png";
		break;
	default:
		break;
	}

	return filePath;
}

/*!
@brief	Load all the map tile images and inserts them into the imageMap
@param	void
@return void
*//*______________________________________________________________*/
void Map::loadMapTileImages(void)
{
	tileTypesVector = { GROUND, GRASS, FLOWER, HORIZONTAL_LEFT_ROAD, HORIZONTAL_MIDDLE_ROAD, HORIZONTAL_RIGHT_ROAD, VERTICAL_LEFT_ROAD, VERTICAL_MIDDLE_ROAD, VERTICAL_RIGHT_ROAD, CORNER_TOP_LEFT_ROAD, CORNER_TOP_RIGHT_ROAD, CORNER_BOTTOM_LEFT_ROAD, CORNER_BOTTOM_RIGHT_ROAD, JUNCTION_MIDDLE_TOP_ROAD, JUNCTION_MIDDLE_BOTTOM_ROAD, JUNCTION_MIDDLE_LEFT_ROAD, JUNCTION_MIDDLE_RIGHT_ROAD, JUNCTION_MIDDLE_ROAD, STARTPOINT, ENDPOINT };

	for (int i = 0; i < tileTypesVector.size(); i++)
	{
		CP_Image tempImage = CP_Image_Load(getImageFilePath(tileTypesVector[i]).c_str());
		imageMap.insert({ tileTypesVector[i], tempImage });
	}
}

/*!
@brief	Gets a tile based on the x & y postion given
@param	xPos - x position
@param	yPos - y position
@return Tile
*//*______________________________________________________________*/
Tile Map::getTile(float xPos, float yPos)
{
	int rowPos = 0, columnPos = 0;

	rowPos = floor(xPos / TILE_WIDTH);
	columnPos = floor(yPos / TILE_HEIGHT);

	rowPos = rowPos > TILE_WIDTH ? TILE_WIDTH : rowPos;
	columnPos = columnPos > TILE_HEIGHT ? TILE_HEIGHT : columnPos;

	Tile tile = map[rowPos][columnPos];

	return tile;
}

Tile** Map::getMap(void)
{
	return this->map;
}

int Map::getNumCol(void)
{
	return NUM_COLUMN;
}

int Map::getNumRow(void)
{
	return NUM_ROW;
}

/*!
@brief	Loads the map using CSVManager based off the fileName,
		stores this into in the map array
@param	string fileName - name of the file
@return bool
*//*______________________________________________________________*/
bool Map::loadMap(std::string fileName)
{
	//Get the map data from reading the file
	std::vector<std::vector<int>> mapData = CSVManager::read(fileName, NUM_COLUMN, NUM_ROW);

	//Reset the map
	resetMap(true);

	//Nested for loop to store the tile data read from file
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			//Save the data into the map array from the mapData recieved from reading the csv file.
			//mapData must be reversed cus the vector is gae
			map[i][j].tileType = static_cast<TILE_TYPE>(mapData[j][i]);
			map[i][j].pos = CP_Vector_Set((TILE_WIDTH * 0.5f) + TILE_WIDTH * i, (TILE_HEIGHT * 0.5f) + TILE_HEIGHT * j);
		}
	}

	return true;
}

/*!
@brief	Saves the map by using CSVManager to write to csv
@param	string fileName - name of the file
@return bool
*//*______________________________________________________________*/
bool Map::saveMap(std::string fileName)
{
	std::vector<std::vector<int>> test;

	for (int i = 0; i < 32; i++)
	{
		std::vector<int> column;

		for (int j = 0; j < 32; j++)
		{
			column.push_back(1);
		}

		test.push_back(column);
	}

	CSVManager::write(fileName, 32, 32, test);

	return false;
}

/*!
@brief	Render the map by using the data from the map array
@param	void
@return void
*//*______________________________________________________________*/
void Map::renderMap(void)
{
	//Render the map
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			CP_Image_Draw(imageMap[map[i][j].tileType], map[i][j].pos.x, map[i][j].pos.y, TILE_WIDTH, TILE_HEIGHT, 255);
		}
	}
}

/*!
@brief	Resets the map by clearing it then initialising it with
		empty values
@param	bool clear - whether to clear the map or not (used when first initialising the map)
@return void
*//*______________________________________________________________*/
void Map::resetMap(bool clear)
{
	clearMap(clear);

	//Resets the map with new blank data
	map = new Tile * [NUM_ROW];

	for (int i = 0; i < NUM_ROW; i++)
	{
		map[i] = new Tile[NUM_COLUMN];

		for (int j = 0; j < NUM_COLUMN; j++)
		{
			map[i][j].tileType = NONE;
			map[i][j].pos = CP_Vector_Zero();
		}
	}
}

/*!
@brief	Clears the map to prevent memory leak
@param	bool clear - whether to clear the map or not (used when first initialising the map)
@return void
*//*______________________________________________________________*/
void Map::clearMap(bool clear)
{
	//Clear the map
	if (clear)
	{
		for (int i = 0; i < NUM_ROW; i++)
		{
			delete map[i];
		}

		delete map;
	}
}

/*!
@brief	Frees all the images and clears the vectors (used when program is shutting down)
@param	void
@return void
*//*______________________________________________________________*/
void Map::freeImages(void)
{
	for (int i = 0; i < tileTypesVector.size(); i++)
	{
		CP_Image_Free(imageMap[tileTypesVector[i]]);
	}

	imageMap.clear();
	tileTypesVector.clear();
}
