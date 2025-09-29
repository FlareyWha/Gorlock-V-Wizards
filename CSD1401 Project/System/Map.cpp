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
#include <iostream>

const char* Map::TILE_ASSETS_FILE_PATH = "Assets/Tiles/";

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

bool Map::loadMapTileImages()
{
	tileTypesVector = { GROUND, GRASS, FLOWER, HORIZONTAL_LEFT_ROAD, HORIZONTAL_MIDDLE_ROAD, HORIZONTAL_RIGHT_ROAD, VERTICAL_LEFT_ROAD, VERTICAL_MIDDLE_ROAD, VERTICAL_RIGHT_ROAD, CORNER_TOP_LEFT_ROAD, CORNER_TOP_RIGHT_ROAD, CORNER_BOTTOM_LEFT_ROAD, CORNER_BOTTOM_RIGHT_ROAD, JUNCTION_MIDDLE_TOP_ROAD, JUNCTION_MIDDLE_BOTTOM_ROAD, JUNCTION_MIDDLE_LEFT_ROAD, JUNCTION_MIDDLE_RIGHT_ROAD, JUNCTION_MIDDLE_ROAD, STARTPOINT, ENDPOINT };

	for (int i = 0; i < tileTypesVector.size(); i++)
	{
		CP_Image tempImage = CP_Image_Load(getImageFilePath(tileTypesVector[i]).c_str());
		imageMap.insert({ tileTypesVector[i], tempImage });
	}

	return true;
}

bool Map::loadMap(std::string fileName)
{
	//Get the map data from reading the file
	std::vector<std::vector<int>> mapData = CSVManager::read(fileName, NUM_COLUMN, NUM_ROW);

	std::vector<std::vector<int>>::iterator rowIterator = mapData.begin();

	
	map = new Tile* [NUM_ROW];

	for (int i = 0; i < NUM_ROW; i++)
	{
		map[i] = new Tile [NUM_COLUMN];

		for (int j = 0; j < NUM_COLUMN; j++)
		{
			map[i][j].tileType = NONE;
			map[i][j].pos = CP_Vector_Zero();
		}
	}

	//Nested for loop to store the tile data read from file
	for (int i = 0; i < NUM_ROW; i++)
	{
		//std::vector<int>::iterator columnIterator = (*rowIterator).begin();

		for (int j = 0; j < NUM_COLUMN; j++)
		{
			std::cout << mapData[j][i] << std::endl;

			map[i][j].tileType = static_cast<TILE_TYPE>(mapData[j][i]);
			map[i][j].pos = CP_Vector_Set((TILE_WIDTH * 0.5f) + TILE_WIDTH * i, (TILE_HEIGHT * 0.5f) + TILE_HEIGHT * j);
		}

		//rowIterator++;
	}

	return true;
}

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

bool Map::renderMap()
{
	//Render the map
	for (int i = 0; i < NUM_ROW; i++)
	{
		for (int j = 0; j < NUM_COLUMN; j++)
		{
			CP_Image_Draw(imageMap[map[i][j].tileType], map[i][j].pos.x, map[i][j].pos.y, TILE_WIDTH, TILE_HEIGHT, 255);
		}
	}

	return false;
}

bool Map::clearMap()
{
	for (int i = 0; i < NUM_ROW; i++)
	{
		delete map[i];
	}

	delete map;

	return true;
}
