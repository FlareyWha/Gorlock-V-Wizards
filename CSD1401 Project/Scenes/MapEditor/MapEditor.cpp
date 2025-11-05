#include "MapEditor.h"
#include "cprocessing.h"
#include "../../System/Map.h"
#include <iostream>
#include <map>

Map* mapEditorMap;
CP_Vector prevMousePos = CP_Vector_Zero();
CP_Vector currentTilePos = CP_Vector_Zero();
bool placedTile = false;

void mapEditorInit(void)
{
	mapEditorMap = Map::GetInstance();
	//map->loadMapTileImages();
	//mapEditorMap->saveMap("test");
	mapEditorMap->loadMap("Edit");

	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void mapEditorUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		setNewMapTile();
	}

	prevMousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	
	//Render map
	mapEditorMap->renderMap();
}

void mapEditorExit(void)
{
	mapEditorMap->resetMap(true);
}

void setNewMapTile(void)
{
	//Get the tile pos of the tile that the mouse is at
	CP_Vector tempTilePos = mapEditorMap->getTilePos(CP_Input_GetMouseX(), CP_Input_GetMouseY());

	//Get current pos and get the vector from old to current pos
	CP_Vector currentMousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	CP_Vector mousePosChange = CP_Vector_Subtract(currentMousePos, prevMousePos);

	//Get angle to be used for finding road
	float verticalAngle = CP_Vector_Angle(mousePosChange, CP_Vector_Set(0, -1));
	float horizontalAngle = CP_Vector_Angle(mousePosChange, CP_Vector_Set(-1, 0));

	//Places tile only if the cursor is on a new tile, this prevents placing multiple times
	if (!placedTile)
	{
		//Place tile based on angle which detemines the initial road to place down
		if (verticalAngle >= 0 && verticalAngle <= 45)
		{
			mapEditorMap->setTile(VERTICAL_TOP_ROAD, tempTilePos.x, tempTilePos.y);
			checkMapTileChanges(tempTilePos);

			std::cout << "Vertical Angle: " << verticalAngle << std::endl;
		}
		else if (verticalAngle >= 135 && verticalAngle <= 180)
		{
			mapEditorMap->setTile(VERTICAL_BOTTOM_ROAD, tempTilePos.x, tempTilePos.y);
			checkMapTileChanges(tempTilePos);

			std::cout << "Vertical Angle: " << verticalAngle << std::endl;
		}
		else if (horizontalAngle >= 0 && horizontalAngle <= 45)
		{
			mapEditorMap->setTile(HORIZONTAL_LEFT_ROAD, tempTilePos.x, tempTilePos.y);
			checkMapTileChanges(tempTilePos);

			std::cout << "Horizontal Angle: " << horizontalAngle << std::endl;
		}
		else if (horizontalAngle >= 135 && horizontalAngle <= 180)
		{
			mapEditorMap->setTile(HORIZONTAL_RIGHT_ROAD, tempTilePos.x, tempTilePos.y);
			checkMapTileChanges(tempTilePos);

			std::cout << "Horizontal Angle: " << horizontalAngle << std::endl;
		}
	}
	else if (tempTilePos.x != currentTilePos.x || tempTilePos.y != currentTilePos.y && placedTile)
	{
		//Reset bool check when in a different tile
		placedTile = false;
	}
}

void checkMapTileChanges(CP_Vector tilePos)
{
	currentTilePos = tilePos;
	placedTile = true;

	std::map<TILE_RELATIVE_POSITION, Tile> surroundingTiles = mapEditorMap->getSurroundingTiles(tilePos);

	std::cout << "Surrounding tiles: ";

	for (std::map<TILE_RELATIVE_POSITION, Tile>::iterator it = surroundingTiles.begin(); it != surroundingTiles.end(); it++)
	{
		std::cout << it->first << " | " << it->second.tileType << ", ";

		CP_Vector tempTilePos = mapEditorMap->getTilePos(it->second.pos.x, it->second.pos.y);

		std::map<TILE_RELATIVE_POSITION, Tile> relativeSurroundingTiles = mapEditorMap->getSurroundingTiles(tempTilePos);

		setUpdatedMapTile(tempTilePos, relativeSurroundingTiles);
	}

	setUpdatedMapTile(tilePos, surroundingTiles);

	std::cout << std::endl;

	//Start out placing dead-end road tile based on dir
	//Search 8 tiles around newly placed tile and get any placed ones
	//Repeat the same for the placed ones
	//Check if any of the placed ones are joined to other sides, if it is then change to the junction tiles
}

void setUpdatedMapTile(CP_Vector initialTilePos, std::map<TILE_RELATIVE_POSITION, Tile> surroundingTiles)
{
	bool active[4] = { false };

	//Tile arrangement
	// -0- 
	// 1-2
	// -3-

	for (std::map<TILE_RELATIVE_POSITION, Tile>::iterator it = surroundingTiles.begin(); it != surroundingTiles.end(); it++)
	{
		active[(int)it->first] = true;
	}
	
	if (active[0] && active[1] && active[2] && active[3])
	{
		mapEditorMap->setTile(JUNCTION_MIDDLE_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[0] && active[1] && active[2])
	{
		mapEditorMap->setTile(JUNCTION_MIDDLE_BOTTOM_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[3] && active[1] && active[2])
	{
		mapEditorMap->setTile(JUNCTION_MIDDLE_TOP_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[1] && active[0] && active[3])
	{
		mapEditorMap->setTile(JUNCTION_MIDDLE_RIGHT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[2] && active[0] && active[3])
	{
		mapEditorMap->setTile(JUNCTION_MIDDLE_LEFT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[0] && active[3])
	{
		mapEditorMap->setTile(VERTICAL_MIDDLE_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[1] && active[2])
	{
		mapEditorMap->setTile(HORIZONTAL_MIDDLE_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[0] && active[1])
	{
		mapEditorMap->setTile(CORNER_BOTTOM_RIGHT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[0] && active[2])
	{
		mapEditorMap->setTile(CORNER_BOTTOM_LEFT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[3] && active[1])
	{
		mapEditorMap->setTile(CORNER_TOP_RIGHT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[3] && active[2])
	{
		mapEditorMap->setTile(CORNER_TOP_LEFT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[0])
	{
		mapEditorMap->setTile(VERTICAL_BOTTOM_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[1])
	{
		mapEditorMap->setTile(HORIZONTAL_RIGHT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[2])
	{
		mapEditorMap->setTile(HORIZONTAL_LEFT_ROAD, initialTilePos.x, initialTilePos.y);
	}
	else if (active[3])
	{
		mapEditorMap->setTile(VERTICAL_TOP_ROAD, initialTilePos.x, initialTilePos.y);
	}
}
