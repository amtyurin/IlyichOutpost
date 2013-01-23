#include "PassingMap.h"

PassingMap::PassingMap(void)
{
}


PassingMap::~PassingMap(void)
{
}

Cell PassingMap::map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];

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

			posY += MAP_CELL_SIZE;
		}
		
		posX += MAP_CELL_SIZE;
 	    posY = 0;
	}
}


void PassingMap::ShowDebugGrid(CCScene *scene)
{
	CCSprite *spriteAll = CCSprite::create();

	for (int ax = 0; ax < MAP_WIDTH_MAX; ax++)
	{
		for (int ay = 0; ay < MAP_HEIGHT_MAX; ay++)
		{
			char *cell_filename = NULL;
			switch(PassingMap::map[ax][ay].type)
			{
				case STATE_CELL_FREE:
					cell_filename = "\\cells\\free_cell.png";
					break;
				case STATE_CELL_BUSY:
					cell_filename = "\\cells\\busy_cell.png";
					break;
				case STATE_CELL_BUILD:
					cell_filename = "\\cells\\build_cell.png";
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
		}
	}

	scene->addChild(spriteAll, 10);
}

CellState PassingMap::GetCellSTate(int x, int y)
{
	if (x >= 0 && x < MAP_WIDTH_MAX &&
		y >= 0 && y < MAP_HEIGHT_MAX)
	{
		return PassingMap::map[x][y].type;
	}
	else
		return STATE_CELL_BUSY;
}

void PassingMap::SetCellState(int x, int y, CellState cState)
{
	if (x >= 0 && x < MAP_WIDTH_MAX &&
		y >= 0 && y < MAP_HEIGHT_MAX)
	{
		PassingMap::map[x][y].type = cState;
	}
}
