#pragma once
#include "../../System/Map.h"

enum EDITOR_STATE
{
	STARTPOINT_EDIT,
	ROAD_EDIT,
	ENDPOINT_EDIT,
	TOTAL_EDITOR_STATE
};

void mapEditorInit(void);
void mapEditorUpdate(void);
void mapEditorExit(void);

void setNewMapTile(void);
void deleteMapTile(void);

void switchEditorState(EDITOR_STATE newState);

void checkRoadTileChanges(CP_Vector tilePos, bool checkInitital);

void setUpdatedRoadTile(CP_Vector initialTilePos, std::map<TILE_RELATIVE_POSITION, Tile> surroundingTiles);