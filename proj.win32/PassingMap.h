#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "Waypoint.h"
#include "GameSettings.h"
#include "BuildCells.h"

class PassingMap
{
private:
	PassingMap(void);
	PassingMap(PassingMap const&);              // Don't Implement
    void operator=(PassingMap const&); // Don't implement	

	static Cell map[GameSettings::MAP_WIDTH_MAX][GameSettings::MAP_HEIGHT_MAX];	

	static cocos2d::CCSprite *spriteAll;	

	static void AddIntermediateParts(cocos2d::CCSprite *spriteAll, cocos2d::CCPoint prevPos, cocos2d::CCPoint nextPos);
public:

	static void ClearMap();

	static CellState GetCellSTate(const int x, const int y);
	static Cell* GetCell(const int x, const int y);
	static Cell* GetCellByScreenCoords(const float x, const float y);
	static void SetCellState(const int x, const int y, const CellState state);

	static void ShowDebugGrid(cocos2d::CCScene *scene, CellState type);	
	static void HideDebugGrid(cocos2d::CCScene *scene);

	static void ShowRoad(Waypoint *way, cocos2d::CCScene *scene);
	static void ShowWaypoint(Waypoint *way, cocos2d::CCScene *scene);

	static void ShowBuildCells(BuildCells *cells);

	static void InitCells();

	static Waypoint* GenerateWaypoint();
	static BuildCells* GenerateBuildCells();
	static Waypoint* GenerateSymmetricWaypoint(int startX, int startY, int finishX, int finishY, Waypoint *way);
	static BuildCells* GenerateSymmetricBuildCellsForAI(int startX, int startY, int finishX, int finishY, BuildCells *cells);
	
	~PassingMap(void);
};
