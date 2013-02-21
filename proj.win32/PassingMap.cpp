#include "PassingMap.h"

using namespace cocos2d;

PassingMap::PassingMap(void)
{	
}


PassingMap::~PassingMap(void)
{
}

Cell PassingMap::map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
CCSprite *PassingMap::spriteAll;

void PassingMap::ClearMap()
{
	int posX = 0;
	int posY = 0;

	for (int ax = 0; ax < MAP_WIDTH_MAX; ax++)
	{
		for (int ay = 0; ay < MAP_HEIGHT_MAX; ay++)
		{
			map[ax][ay].type = STATE_CELL_FREE;
			map[ax][ay].x = posX + MAP_CELL_SIZE / 2;
			map[ax][ay].y = posY + MAP_CELL_SIZE / 2;
			map[ax][ay].sprite= NULL;

			posY += MAP_CELL_SIZE;
		}
		
		posX += MAP_CELL_SIZE;
 	    posY = 0;
	}	
	spriteAll = NULL;
}


void PassingMap::ShowDebugGrid(CCScene *scene, CellState type)
{	
	if (spriteAll != NULL){
		spriteAll->removeFromParent();
		spriteAll->removeAllChildren();
		spriteAll = NULL;
	}
	spriteAll = CCSprite::create();

	for (int ax = 0; ax < MAP_WIDTH_MAX; ax++)
	{
		for (int ay = 0; ay < MAP_HEIGHT_MAX; ay++)
		{
			if (PassingMap::map[ax][ay].type == type){
				char *cell_filename = NULL;
				switch(PassingMap::map[ax][ay].type)
				{
					case STATE_CELL_FREE:
						cell_filename = FILE_NAME_IMAGE_STATE_CELL_FREE;
						break;
					case STATE_CELL_BUSY:
						cell_filename = FILE_NAME_IMAGE_STATE_CELL_BUSY;
						break;
					case STATE_CELL_BUILD:
						cell_filename = FILE_NAME_IMAGE_STATE_CELL_BUILD;
						break;
					default:
						CCLOG("ERROR: Cell type is not right");
						continue;
						break;
				}

				CCSprite *cellSprite = CCSprite::create(cell_filename);
				CC_BREAK_IF(! cellSprite);

				cellSprite->setPositionX(map[ax][ay].x);
				cellSprite->setPositionY(map[ax][ay].y);

				spriteAll->addChild(cellSprite, 1);		
				map[ax][ay].sprite = cellSprite;
			}
		}
	}
	
	scene->addChild(spriteAll, 10);
}

void PassingMap::HideDebugGrid(CCScene *scene)
{
	if (spriteAll != NULL){
		spriteAll->removeFromParent();
		//spriteAll->removeAllChildren();
		spriteAll = NULL;
	}
}

CellState PassingMap::GetCellSTate(const int x,const int y)
{
	if (x >= 0 && x < MAP_WIDTH_MAX &&
		y >= 0 && y < MAP_HEIGHT_MAX)
	{
		return PassingMap::map[x][y].type;
	}
	else
		return STATE_CELL_BUSY;
}

Cell* PassingMap::GetCell(const int x, const int y)
{
	if (x >= 0 && x < MAP_WIDTH_MAX &&
		y >= 0 && y < MAP_HEIGHT_MAX)
	{
		return &PassingMap::map[x][y];
	}
	else
		return NULL;
}

void PassingMap::SetCellState(const int x, const int y, const CellState cState)
{
	if (x >= 0 && x < MAP_WIDTH_MAX &&
		y >= 0 && y < MAP_HEIGHT_MAX)
	{
		PassingMap::map[x][y].type = cState;
	}
}

void PassingMap::ShowWaypoint(Waypoint *way, CCScene *scene)
{
	CCSprite *spriteAll = CCSprite::create();
	int i = 0;
	Cell *cell = way->GetPoint(i);

	while(cell)
	{
		CCSprite *cellSprite = CCSprite::create(FILE_NAME_IMAGE_STATE_CELL_BUSY);
		CC_BREAK_IF(! cellSprite);

		cellSprite->setScale(0.6f);
		cellSprite->setPositionX(cell->x);
        cellSprite->setPositionY(cell->y);

		spriteAll->addChild(cellSprite, 1);

		i++;
		cell = way->GetPoint(i);
	}

	scene->addChild(spriteAll, 20);
}

void PassingMap::ShowRoad(Waypoint *way, CCScene *scene)
{
	CCSprite *spriteAll = CCSprite::create();
	int i = 0;
	Cell *cell = way->GetPoint(i);
	CCPoint prevPos = ccp(-100,-100);
	CCPoint nextPos = ccp(-100,-100);

	if (cell) prevPos = ccp(cell->x, cell->y);
	while(cell)
	{			
		nextPos = ccp(cell->x, cell->y);

		AddIntermediateParts(spriteAll, prevPos, nextPos);

		prevPos = nextPos;

		i++;
		cell = way->GetPoint(i);
	}

	scene->addChild(spriteAll, 0);
}

void PassingMap::AddIntermediateParts(CCSprite *spriteAll, CCPoint prevPos, CCPoint nextPos)
{
	CCSprite *cellSprite = CCSprite::create(FILE_NAME_IMAGE_BACKGROUND_ROAD);	

	int partsCount = ccpDistance(prevPos, nextPos) / ( cellSprite->getContentSize().width / 2.5);
	
	int shiftX = partsCount == 0 ? 0 : (nextPos.x - prevPos.x) / partsCount;
	int shiftY = partsCount == 0 ? 0 : (nextPos.y - prevPos.y) / partsCount;
	for(int i = 0; i <= partsCount; i++){
		CCPoint nextPoint = ccp(prevPos.x + i * shiftX, prevPos.y + i * shiftY);
		cellSprite->setPosition(nextPoint);
		spriteAll->addChild(cellSprite, 1);
		cellSprite = CCSprite::create(FILE_NAME_IMAGE_BACKGROUND_ROAD);
	}
}

Cell* PassingMap::GetCellByScreenCoords(const float x, const float y){
	int cellX = x / MAP_CELL_SIZE;
	int cellY = y / MAP_CELL_SIZE;
	return &PassingMap::map[cellX][cellY];
}


void PassingMap::InitCells(){
	for (int x = 0; x < MAP_WIDTH_MAX; ++x){
		for (int y = 0; y < MAP_HEIGHT_MAX; ++y){
			map[x][y].x = x*MAP_CELL_SIZE + MAP_CELL_SIZE / 2;
			map[x][y].y = y*MAP_CELL_SIZE + MAP_CELL_SIZE / 2;
			//CCLog ("%d %d", map[x][y].x, map[x][y].y);
		}
	}
}
