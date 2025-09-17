/*!
@file       CSVManager.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definition of functions used to read and write to CSV
*//*_______________________________________________________________________*/

#include "CSVManager.h"
#include <sstream>
#include <fstream>

const char* CSVManager::MAP_FILE_PATH = "./Assets/Maps/";

CSVManager::CSVManager()
{
	
}

CSVManager::~CSVManager()
{
}

/**
 @brief Write to a CSV file
 @param fileName A string containing the name of the input file
 @param TILE_ROW_NUM A const int containing the number of tiles in the x-axis
 @param TILE_COLUMN_NUM A const int containing the number of tiles in the y-axis
 @param data A vector containing the value of the vector which represents the tile map
 @return boolean variable
 */
bool CSVManager::write(std::string fileName, const int TILE_ROW_NUM, const int TILE_COLUMN_NUM, std::vector<std::vector<int>> data)
{
	bool writeSucessful = false;

	//Opens the file at the location it is in
	std::ofstream file;
	file.open(MAP_FILE_PATH + fileName);

	//Checks if the number of columns is correct
	if (data.size() == TILE_COLUMN_NUM)
	{
		//Sets the iterator for the row to the beginning of x vector
		std::vector<std::vector<int>>::iterator rowIterator = data.begin();

		//Checks if the number of rows is correct
		if ((*rowIterator).size() == TILE_ROW_NUM)
		{
			//Writes the values into the file
			for (rowIterator = data.begin(); rowIterator != data.end(); rowIterator++)
			{
				//Set iterator for the column
				std::vector<int>::iterator columnIterator;

				//Loop through the column values
				for (columnIterator = (*rowIterator).begin(); columnIterator != (*rowIterator).end(); columnIterator++)
				{
					//Insert column value into file
					file << *columnIterator;

					//Use a comma token to split the values
					if (columnIterator != (*rowIterator).end())
						file << ',';
				}

				//Adds endline to file so that it starts from next row
				file << std::endl;
			}
		}

		writeSucessful = true;
	}


	//Closes the file
	file.close();

	return writeSucessful;
}

/**
 @brief Read from a CSV file
 @param fileName A string containing the name of the output file
 @param TILE_ROW_NUM A const int containing the number of tiles in the x-axis
 @param TILE_COLUMN_NUM A const int containing the number of tiles in the y-axis
 @return vector<vector<int>> data
 */
std::vector<std::vector<int>> CSVManager::read(std::string fileName, const int TILE_ROW_NUM, const int TILE_COLUMN_NUM)
{
	//Double vector to store the tile data
	std::vector<std::vector<int>> rowValues;

	//Creates an input filestream and opens the file
	std::ifstream file;
	file.open(MAP_FILE_PATH + fileName);

	std::string line;
	int value = 0;
	bool readResult = true;

	//Gets the values of an entire row, repeats until end of csv file
	while (getline(file, line))
	{
		//Create stringstream to allow the program to read the values
		std::stringstream ss(line);

		//Create vector to store the column values
		std::vector<int> columnValues;

		while (ss >> value)
		{
			//Add the current column value to the vector
			columnValues.push_back(value);

			//If value is a comma, ignore it 
			if (ss.peek() == ',')
				ss.ignore();
		}

		//Push the whole column into the data vector
		if (columnValues.size() == TILE_COLUMN_NUM)
			rowValues.push_back(columnValues);
		else
		{
			columnValues.clear();
			readResult = false;
		}
	}

	//Close the file
	file.close();

	//Check if the rows are correct
	if (rowValues.size() != TILE_ROW_NUM)
	{

		readResult = false;
	}

	//Clear the vector if there are any issues
	if (!readResult)
	{
		for (int i = 0; i < (int)rowValues.size(); i++)
		{
			rowValues[i].clear();
		}

		rowValues.clear();
	}

	return rowValues;
}
