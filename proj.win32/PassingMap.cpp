#include "PassingMap.h"

PassingMap::PassingMap(void)
{
}


PassingMap::~PassingMap(void)
{
}

Cell PassingMap::map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

void PassingMap::ClearMap()
{
	for (int ax = 0; ax < MAP_HEIGHT_MAX; ax++)
	{
		for (int ay = 0; ay < MAP_WIDTH_MAX; ay++)
		{
			PassingMap::map[ax][ay].type = STATE_CELL_FREE;
		}
	}
}


void PassingMap::ShowDebugGrid(CCScene *scene)
{
	CCSprite *spriteAll = CCSprite::create();
	int posX = 0;
	int posY = 0;

	for (int ax = 0; ax < MAP_HEIGHT_MAX; ax++)
	{
		for (int ay = 0; ay < MAP_WIDTH_MAX; ay++)
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

			cellSprite->setPositionX(posX);
            cellSprite->setPositionY(posY);

			spriteAll->addChild(cellSprite, 1);

			posX += MAP_CELL_SIZE;
		}
		posY += MAP_CELL_SIZE;
 	    posX = 0;
	}

	scene->addChild(spriteAll, 10);
}

CellState PassingMap::GetCellSTate(int x, int y)
{
	if (x >= 0 && x < MAP_HEIGHT_MAX &&
		y >= 0 && y < MAP_WIDTH_MAX)
	{
		return PassingMap::map[x][y].type;
	}
	else
		return STATE_CELL_BUSY;
}

void PassingMap::SetCellState(int x, int y, CellState cState)
{
	if (x >= 0 && x < MAP_HEIGHT_MAX &&
		y >= 0 && y < MAP_WIDTH_MAX)
	{
		PassingMap::map[x][y].type = cState;
	}
}
