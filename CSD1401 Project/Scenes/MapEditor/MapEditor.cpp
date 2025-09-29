#include "MapEditor.h"
#include "cprocessing.h"
#include "../../System/Map.h"

Map* map;


void mapEditorInit(void)
{
	map = Map::GetInstance();
	map->loadMapTileImages();
	map->saveMap("test");
	map->loadMap("Map1");

	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void mapEditorUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	//Render map
	map->renderMap();
}

void mapEditorExit(void)
{
	map->clearMap();
	map->DestroyInstance();
}
