/*!
@file       Map.cpp
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definitions of functions	
			used for the Map class
*//*_______________________________________________________________________*/

#include "Map.h"
#include "CSVManager.h"
#include "cprocessing.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

const char* Map::TILE_ASSETS_FILE_PATH = "Assets/Tiles/";

/*!
@brief Constructor. Makes it set the map array to empty and loads all map tile images
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
	case MIDDLE_ROAD:
		filePath += "Middle.png";
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
	case VERTICAL_TOP_ROAD:
		filePath += "VerticalTop.png";
		break;
	case VERTICAL_MIDDLE_ROAD:
		filePath += "VerticalMiddle.png";
		break;
	case VERTICAL_BOTTOM_ROAD:
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
	tileTypesVector = { GROUND, GRASS, FLOWER, MIDDLE_ROAD, HORIZONTAL_LEFT_ROAD, HORIZONTAL_MIDDLE_ROAD, HORIZONTAL_RIGHT_ROAD, VERTICAL_TOP_ROAD, VERTICAL_MIDDLE_ROAD, VERTICAL_BOTTOM_ROAD, CORNER_TOP_LEFT_ROAD, CORNER_TOP_RIGHT_ROAD, CORNER_BOTTOM_LEFT_ROAD, CORNER_BOTTOM_RIGHT_ROAD, JUNCTION_MIDDLE_TOP_ROAD, JUNCTION_MIDDLE_BOTTOM_ROAD, JUNCTION_MIDDLE_LEFT_ROAD, JUNCTION_MIDDLE_RIGHT_ROAD, JUNCTION_MIDDLE_ROAD, STARTPOINT, ENDPOINT };

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
	CP_Vector tilePos = getTilePos(xPos, yPos);

	Tile tile = map[(int)tilePos.x][(int)tilePos.y];

	return tile;
}

/*!
@brief	Gets a tile based on the x & y tile pos given
@param	xPos - x tile position
@param	yPos - y tile position
@return Tile
*//*______________________________________________________________*/
Tile Map::getTileFromTilePos(int xPos, int yPos)
{
	Tile tile = map[xPos][yPos];

	return tile;
}

/*!
@brief	Gets tile grid pos based on x & y position given
@param	xPos - x position
@param	yPos - y position
@return CP_Vector - tile grid pos
*//*______________________________________________________________*/
CP_Vector Map::getTilePos(float xPos, float yPos)
{
	int rowPos = 0, columnPos = 0;

	rowPos = floor(xPos / TILE_WIDTH);
	columnPos = floor(yPos / TILE_HEIGHT);

	if (rowPos >= NUM_ROW)
	{
		rowPos = NUM_ROW - 1;
	}
	else if (rowPos < 0)
	{
		rowPos = 0;
	}

	if (columnPos >= NUM_COLUMN)
	{
		columnPos = NUM_COLUMN - 1;
	}
	else if (columnPos < 0)
	{
		columnPos = 0;
	}

	return CP_Vector_Set(rowPos, columnPos);
}

CP_Vector Map::getTileWorldPos(CP_Vector tilePos)
{
	Tile tile = map[(int)tilePos.x][(int)tilePos.y];

	return tile.pos;
}

/*!
@brief	Set tile type based on given grid position
@param	rowPos - tile grid row pos
@param	columnPos - tile grid column pos
@return void
*//*______________________________________________________________*/
void Map::setTile(TILE_TYPE tile, int rowPos, int columnPos)
{
	map[rowPos][columnPos].tileType = tile;
}

/*!
@brief	Get up to 4 surrounding tiles based on tile grid pos given
		if they are "active" (not empty)
@param	tilePos - tile grid pos
@return std::map<TILE_RELATIVE_POSITION, Tile> - map that stores 0 - 4 tiles
*//*______________________________________________________________*/
std::map<TILE_RELATIVE_POSITION, Tile> Map::getSurroundingTiles(CP_Vector tilePos)
{
	std::map<TILE_RELATIVE_POSITION, Tile> tileMap;

	CP_Vector positions[4] = { CP_Vector_Set(tilePos.y - 1, tilePos.x), CP_Vector_Set(tilePos.y, tilePos.x - 1), CP_Vector_Set(tilePos.y, tilePos.x + 1), CP_Vector_Set(tilePos.y + 1, tilePos.x) };

	for (int i = 0; i < 4; i++)
	{
		if (checkSurroundingTile(positions[i]))
		{
			tileMap.insert({ static_cast<TILE_RELATIVE_POSITION>(i), map[(int)positions[i].y][(int)positions[i].x]});
		}

	}

	//Min 0 tiles returned, Max 4 tiles returned
	return tileMap;
}

/*!
@brief	Check whether the surrounding tile is valid by checking if it within bounds and the tile is not
		a ground tile
@param	tilePos - tile grid pos
@return bool - true is valid, false is not
*//*______________________________________________________________*/
bool Map::checkSurroundingTile(CP_Vector tilePos)
{
	if (tilePos.x < 0 || tilePos.x >= NUM_COLUMN || tilePos.y < 0 || tilePos.y >= NUM_ROW || map[(int)tilePos.y][(int)tilePos.x].tileType == GROUND)
	{
		return false;
	}

	return true;
}

/*!
@brief	Check whether tile of given tileType is active when entering map for first	  time
@param	TILE_TYPE tileType - tile to check for
@return CP_Vector - return tile pos if active, else return zero vector
*//*______________________________________________________________*/
CP_Vector Map::testTileActive(TILE_TYPE tileType)
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			if (map[i][j].tileType == tileType)
			{
				return getTilePos(map[i][j].pos.x, map[i][j].pos.y);
			}
		}
	}

	return CP_Vector_Zero();
}

/*!
@brief	Get the map
@param	void
@return Tile** - map
*//*______________________________________________________________*/
Tile** Map::getMap(void)
{
	return this->map;
}

/*!
@brief	Get number of columns
@param	void
@return int - number of columns
*//*______________________________________________________________*/
int Map::getNumCol(void)
{
	return NUM_COLUMN;
}

/*!
@brief	Get number of rows
@param	void
@return int - number of rows
*//*______________________________________________________________*/
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
	std::string file;

	if (loadEditedMap)
	{
		file = "Edit";
	}
	else
	{
		file = fileName;
	}

	//Get the map data from reading the file
	std::vector<std::vector<int>> mapData = CSVManager::read(file, NUM_COLUMN, NUM_ROW);

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

			if (map[i][j].tileType == STARTPOINT)
				spawnpoint = map[i][j].pos;
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
	std::vector<std::vector<int>> mapData;

	for (int i = 0; i < NUM_COLUMN; i++)
	{
		std::vector<int> columnData;

		for (int j = 0; j < NUM_ROW; j++)
		{
			columnData.push_back(map[j][i].tileType);
		}

		mapData.push_back(columnData);
	}

	if (CSVManager::write(fileName, NUM_ROW, NUM_COLUMN, mapData))
	{
		std::cout << "Write sucessful!!!!" << std::endl;
		return true;
	}

	std::cout << "Write unsucessful!!!!" << std::endl;

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
void Map::freeImages(bool free)
{
	if (free)
	{
		for (int i = 0; i < tileTypesVector.size(); i++)
		{
			CP_Image_Free(imageMap[tileTypesVector[i]]);
		}

		imageMap.clear();
		tileTypesVector.clear();
	}
}

/*!
@brief	Get dimensions of map in CP_Vector form
@param	void
@return CP_Vector - map dimensions
*//*______________________________________________________________*/
CP_Vector Map::getDimensions()
{
	return CP_Vector_Set(NUM_ROW, NUM_COLUMN);
}

/*!
@brief	Get size of tile
@param	void
@return int - size of tile
*//*______________________________________________________________*/
int Map::getTileSize()
{
	return TILE_WIDTH;
}

/*!
@brief	Set the bool that controls whether to load the edited map
@param	bool loadEditedMap - the new value to set
@return void
*//*______________________________________________________________*/
void Map::setLoadEditedMap(bool loadEditedMap)
{
	this->loadEditedMap = loadEditedMap;
}

/*!
@brief	Get spawnpoint of the enemies
@param	void
@return CP_Vector - vector of spawnpoint
*//*______________________________________________________________*/
CP_Vector Map::getSpawnpoint(void)
{
	return spawnpoint;
}

/*!
@brief	Set spawnpoint of the enemies
@param	CP_Vector - vector of spawnpoint
@return void
*//*______________________________________________________________*/
void Map::setSpawnpoint(CP_Vector spawnpoint)
{
	this->spawnpoint = spawnpoint;
}

