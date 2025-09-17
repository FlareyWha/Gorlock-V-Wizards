

#pragma once
#include "SingletonTemplate.h"

class Map : public SingletonTemplate<Map>
{
	friend class SingletonTemplate<Map>;

public:
	bool loadMap();

	enum TILE_TYPE
	{
		NONE = 0,
		TEST = 1,
		TOTAL
	};
};