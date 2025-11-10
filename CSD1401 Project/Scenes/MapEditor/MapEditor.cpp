#include "MapEditor.h"
#include "cprocessing.h"
#include "../../System/Map.h"
#include "../../Utils/Button.h"
#include "../../System/SceneManager.h"
#include "../../Utils/Utils.h"
#include <iostream>
#include <map>

Button back(0, 0, 0, 0, "");
Button save(0, 0, 0, 0, "");
Button startpointSwitch(0, 0, 0, 0, "");
Button roadSwitch(0, 0, 0, 0, "");
Button endpointSwitch(0, 0, 0, 0, "");
Map* mapEditorMap;
CP_Vector prevMousePos = CP_Vector_Zero();
CP_Vector currentTilePos = CP_Vector_Zero();
bool placedTile = false;
EDITOR_STATE currentEditorState = ROAD_EDIT;
CP_Font mapEditorFont;

CP_Vector startpointTilePos;
bool startpointActive = false;
CP_Vector endpointTilePos;
bool endpointActive = false;

void mapEditorInit(void)
{
	mapEditorMap = Map::GetInstance();
	Button::LoadResources();
	mapEditorFont = CP_Font_Load("Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
	//map->loadMapTileImages();
	//mapEditorMap->saveMap("test");
	mapEditorMap->loadMap("Edit");

	CP_Settings_ImageMode(CP_POSITION_CENTER);

	//Init buttons
	save = Button(1450, 700, 150, 40, "Save");
	back = Button(1520, 875, 150, 40, "Back");
	startpointSwitch = Button(1450, 300, 200, 40, "Startpoint Editor");
	roadSwitch = Button(1450, 350, 200, 40, "Road Editor");
	endpointSwitch = Button(1450, 400, 200, 40, "Endpoint Editor");
}

void mapEditorUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(132, 198, 105, 255));

	//Check button clicks
	if (back.IsClicked())
	{
		mapEditorExit();
		SceneManager::GetInstance()->ChangeScenes(Scenes::MAIN_MENU_SCENE);
	}
	else if (save.IsClicked())
	{
		//Save map
		mapEditorMap->saveMap("Edit");
	}
	else if (startpointSwitch.IsClicked())
	{
		currentEditorState = STARTPOINT_EDIT;
	}
	else if (roadSwitch.IsClicked())
	{
		currentEditorState = ROAD_EDIT;
	}
	else if (endpointSwitch.IsClicked())
	{
		currentEditorState = ENDPOINT_EDIT;
	}

	//TODO: Add checks to switch between different editor modes

	//Only draw roads if in area
	if (isAreaClicked(CP_Vector_Set(650, 450), 1300, 900, CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY())))
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			setNewMapTile();
		}
		else if (CP_Input_MouseDown(MOUSE_BUTTON_RIGHT))
		{
			deleteMapTile();
		}
	}

	prevMousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	
	//Render map
	mapEditorMap->renderMap();

	//Render buttons
	back.Draw();
	save.Draw();
	startpointSwitch.Draw();
	roadSwitch.Draw();
	endpointSwitch.Draw();

	CP_Font_Set(mapEditorFont);
	CP_Font_DrawText("Current Editor State: ", 1450, 100);
	switch (currentEditorState)
	{
	case STARTPOINT_EDIT:
		CP_Font_DrawText("Startpoint Editor", 1450, 150);
		break;

	case ROAD_EDIT:
		CP_Font_DrawText("Road Editor", 1450, 150);
		break;

	case ENDPOINT_EDIT:
		CP_Font_DrawText("Endpoint Editor", 1450, 150);
		break;

	default:
		break;
	}
}

void mapEditorExit(void)
{
	mapEditorMap->resetMap(true);
	Button::FreeResources();
}

void setNewMapTile(void)
{
	//Get the tile pos of the tile that the mouse is at
	CP_Vector tempTilePos = mapEditorMap->getTilePos(CP_Input_GetMouseX(), CP_Input_GetMouseY());

	//Places tile only if the cursor is on a new tile, this prevents placing multiple times
	if (!placedTile)
	{
		//Special cases for different editor states
		switch (currentEditorState)
		{
		case STARTPOINT_EDIT:
			if (startpointActive)
			{
				mapEditorMap->setTile(GROUND, startpointTilePos.x, startpointTilePos.y);
			}
			mapEditorMap->setTile(STARTPOINT, tempTilePos.x, tempTilePos.y);
			startpointTilePos = tempTilePos;
			startpointActive = true;
			checkRoadTileChanges(tempTilePos, false);
			break;

		case ROAD_EDIT:
			//Only allows road to be edited if the tile is not a startpoint or endpoint
			if (mapEditorMap->getTileFromTilePos(tempTilePos.x, tempTilePos.y).tileType != STARTPOINT && mapEditorMap->getTileFromTilePos(tempTilePos.x, tempTilePos.y).tileType != ENDPOINT)
			{
				mapEditorMap->setTile(MIDDLE_ROAD, tempTilePos.x, tempTilePos.y);
				checkRoadTileChanges(tempTilePos, true);
			}
			break;

		case ENDPOINT_EDIT:
			if (endpointActive)
			{
				mapEditorMap->setTile(GROUND, endpointTilePos.x, endpointTilePos.y);
			}
			mapEditorMap->setTile(ENDPOINT, tempTilePos.x, tempTilePos.y);
			endpointTilePos = tempTilePos;
			endpointActive = true;
			checkRoadTileChanges(tempTilePos, false);
			break;

		default:
			break;
		}

	}
	else if (tempTilePos.x != currentTilePos.x || tempTilePos.y != currentTilePos.y && placedTile)
	{
		//Reset bool check when in a different tile
		placedTile = false;
	}
}

void deleteMapTile(void)
{
	//Get the tile pos of the tile that the mouse is at
	CP_Vector tempTilePos = mapEditorMap->getTilePos(CP_Input_GetMouseX(), CP_Input_GetMouseY());

	mapEditorMap->setTile(GROUND, tempTilePos.x, tempTilePos.y);
	checkRoadTileChanges(tempTilePos, false);

	//Special cases for different editor states
	switch (currentEditorState)
	{
	case STARTPOINT_EDIT:
		startpointActive = false;
		break;

	case ROAD_EDIT:
		break;

	case ENDPOINT_EDIT:
		endpointActive = false;
		break;

	default:
		break;
	}

	placedTile = false;
}

void switchEditorState(EDITOR_STATE newState)
{
	currentEditorState = newState;
}

void checkRoadTileChanges(CP_Vector tilePos, bool checkInitial)
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

		setUpdatedRoadTile(tempTilePos, relativeSurroundingTiles);
	}

	if (checkInitial)
	{
		setUpdatedRoadTile(tilePos, surroundingTiles);
	}

	std::cout << std::endl;
}

void setUpdatedRoadTile(CP_Vector initialTilePos, std::map<TILE_RELATIVE_POSITION, Tile> surroundingTiles)
{
	bool active[4] = { false };

	if (mapEditorMap->getTileFromTilePos(initialTilePos.x, initialTilePos.y).tileType == STARTPOINT || mapEditorMap->getTileFromTilePos(initialTilePos.x, initialTilePos.y).tileType == ENDPOINT)
	{
		return;
	}

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
	else
	{
		mapEditorMap->setTile(MIDDLE_ROAD, initialTilePos.x, initialTilePos.y);
	}
}
