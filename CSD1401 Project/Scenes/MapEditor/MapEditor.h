#pragma once
#include "../../System/Map.h"

void mapEditorInit(void);
void mapEditorUpdate(void);
void mapEditorExit(void);

void setNewMapTile(void);
void deleteMapTile(void);

void checkMapTileChanges(CP_Vector tilePos, bool checkInitital);

void setUpdatedMapTile(CP_Vector initialTilePos, std::map<TILE_RELATIVE_POSITION, Tile> surroundingTiles);