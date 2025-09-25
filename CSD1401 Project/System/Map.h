/*!
@file       Map.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains declaration of functions used for the map
*//*_______________________________________________________________________*/

#pragma once
#include "SingletonTemplate.h"

class Map : public SingletonTemplate<Map>
{
	friend class SingletonTemplate<Map>;

public:
	bool loadMap();
	bool saveMap();

	enum TILE_TYPE
	{
		NONE = 0,
		TEST = 1,
		TOTAL
	};
};