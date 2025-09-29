#include "MapEditor.h"
#include "cprocessing.h"
#include "../../System/Map.h"

Map* mapEditorMap;


void mapEditorInit(void)
{
	mapEditorMap = Map::GetInstance();
	//map->loadMapTileImages();
	mapEditorMap->saveMap("test");
	mapEditorMap->loadMap("Map1");

	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void mapEditorUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	//Render map
	mapEditorMap->renderMap();
}

void mapEditorExit(void)
{
	mapEditorMap->resetMap(true);
	//map->DestroyInstance();
}
