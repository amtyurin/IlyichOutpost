#include "PassingMap.h"

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
