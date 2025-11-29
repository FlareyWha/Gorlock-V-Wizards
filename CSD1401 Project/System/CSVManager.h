/*!
@file       CSVManager.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains declaration of functions used to read and write to CSV
*//*_______________________________________________________________________*/

#pragma once

#include <string>
#include <vector>

class CSVManager
{
private:
	static const char* MAP_FILE_PATH;

public:
	CSVManager();
	~CSVManager();

	static bool write(std::string fileName, const int TILE_ROW_NUM, const int TILE_COLUMN_NUM, std::vector<std::vector<int>> data);

	static std::vector<std::vector<int>> read(std::string fileName, const int TILE_ROW_NUM, const int TILE_COLUMN_NUM);
};

