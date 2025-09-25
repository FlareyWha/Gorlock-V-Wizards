/*!
@file       Map.c
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definitions of functions used for the map
*//*_______________________________________________________________________*/
#include "Map.h"
#include "CSVManager.h"
#include <vector>

bool Map::loadMap()
{
	CSVManager::read("test", 32, 32);

	

	return false;
}

bool Map::saveMap()
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

	CSVManager::write("test", 32, 32, test);

	return false;
}
