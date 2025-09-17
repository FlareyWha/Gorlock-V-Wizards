/*!
@file       CSVManager.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains declaration of functions used to read and write to CSV
*//*_______________________________________________________________________*/

#pragma once

#include <string>
#include <vector>

static class CSVManager
{
private:
	static const char* MAP_FILE_PATH;

public:
	CSVManager();

	~CSVManager();

	/**
	 @brief Write to a CSV file
	 @param fileName A string containing the name of the input file
	 @param TILE_ROW_NUM A const int containing the number of tiles in the x-axis
	 @param TILE_COLUMN_NUM A const int containing the number of tiles in the y-axis
	 @param data A vector containing the value of the vector which represents the tile map
	 @return boolean variable
	 */
	static bool write(std::string fileName, const int TILE_ROW_NUM, const int TILE_COLUMN_NUM, std::vector<std::vector<int>> data);

	/**
	 @brief Read from a CSV file
	 @param fileName A string containing the name of the output file
	 @param TILE_ROW_NUM A const int containing the number of tiles in the x-axis
	 @param TILE_COLUMN_NUM A const int containing the number of tiles in the y-axis
	 @return vector<vector<int>> data
	 */
	static std::vector<std::vector<int>> read(std::string fileName, const int TILE_ROW_NUM, const int TILE_COLUMN_NUM);
};

