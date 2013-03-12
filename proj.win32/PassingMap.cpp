#include "PassingMap.h"

using namespace cocos2d;

PassingMap::PassingMap(void)
{	
}


PassingMap::~PassingMap(void)
{
}

Cell PassingMap::map[GameSettings::MAP_WIDTH_MAX][GameSettings::MAP_HEIGHT_MAX];
CCSprite *PassingMap::spriteAll;

void PassingMap::ClearMap()
{
	int posX = 0;
	int posY = 0;

	for (int ax = 0; ax < GameSettings::MAP_WIDTH_MAX; ax++)
	{
		for (int ay = 0; ay < GameSettings::MAP_HEIGHT_MAX; ay++)
		{
			map[ax][ay].type = STATE_CELL_FREE;
			map[ax][ay].x = posX + GameSettings::MAP_CELL_SIZE / 2;
			map[ax][ay].y = posY + GameSettings::MAP_CELL_SIZE / 2;
			map[ax][ay].sprite= NULL;
			map[ax][ay].indX = ax;
			map[ax][ay].indY = ay;

			posY += GameSettings::MAP_CELL_SIZE;
		}
		
		posX += GameSettings::MAP_CELL_SIZE;
 	    posY = 0;
	}	
	spriteAll = NULL;
}


void PassingMap::ShowDebugGrid(CCScene *scene, CellState type)
{	
	if (spriteAll == NULL)
		spriteAll = CCSprite::create();

	for (int ax = 0; ax < GameSettings::MAP_WIDTH_MAX; ax++)
	{
		for (int ay = 0; ay < GameSettings::MAP_HEIGHT_MAX; ay++)
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
					case STATE_CELL_BUILD_FOR_US:
						cell_filename = FILE_NAME_IMAGE_STATE_CELL_BUILD;
						break;
					case STATE_CELL_BUILD_FOR_ENEMY:
						cell_filename = FILE_NAME_IMAGE_STATE_CELL_BUILD_ENEMY;
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

				// display indexes
				char text[10];
				snprintf(text, 10, "%d,%d", ax, ay);
				CCLabelTTF* pLabel = CCLabelTTF::create(text, "Arial", 16);
				pLabel->setPositionX(16);
				pLabel->setPositionY(10);	
				cellSprite->addChild(pLabel, 2);
				//

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
		spriteAll->removeAllChildren();
		spriteAll->removeFromParent();		
		spriteAll = NULL;
	}
}

CellState PassingMap::GetCellSTate(const int x,const int y)
{
	if (x >= 0 && x < GameSettings::MAP_WIDTH_MAX &&
		y >= 0 && y < GameSettings::MAP_HEIGHT_MAX)
	{
		return PassingMap::map[x][y].type;
	}
	else
		return STATE_CELL_BUSY;
}

Cell* PassingMap::GetCell(const int x, const int y)
{
	if (x >= 0 && x < GameSettings::MAP_WIDTH_MAX &&
		y >= 0 && y < GameSettings::MAP_HEIGHT_MAX)
	{
		return &PassingMap::map[x][y];
	}
	else
		return NULL;
}

void PassingMap::SetCellState(const int x, const int y, const CellState cState)
{
	if (x >= 0 && x < GameSettings::MAP_WIDTH_MAX &&
		y >= 0 && y < GameSettings::MAP_HEIGHT_MAX)
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
	int cellX = x / GameSettings::MAP_CELL_SIZE;
	int cellY = y / GameSettings::MAP_CELL_SIZE;
	return &PassingMap::map[cellX][cellY];
}


void PassingMap::InitCells(){
	for (int x = 0; x < GameSettings::MAP_WIDTH_MAX; ++x){
		for (int y = 0; y < GameSettings::MAP_HEIGHT_MAX; ++y){
			map[x][y].x = x*GameSettings::MAP_CELL_SIZE + GameSettings::MAP_CELL_SIZE / 2;
			map[x][y].y = y*GameSettings::MAP_CELL_SIZE + GameSettings::MAP_CELL_SIZE / 2;
			//CCLog ("%d %d", map[x][y].x, map[x][y].y);
		}
	}
}

Waypoint* PassingMap::GenerateWaypoint(){
	Waypoint *way = new Waypoint();
	way->AddPoint(PassingMap::GetCell(0,1));
	way->AddPoint(PassingMap::GetCell(2,2));
	way->AddPoint(PassingMap::GetCell(3,4));
	way->AddPoint(PassingMap::GetCell(4,8));
	way->AddPoint(PassingMap::GetCell(5,12));
	way->AddPoint(PassingMap::GetCell(5,14));
	way->AddPoint(PassingMap::GetCell(6,15));
	way->AddPoint(PassingMap::GetCell(10,15));
	way->AddPoint(PassingMap::GetCell(18,13));
	way->AddPoint(PassingMap::GetCell(18,11));
	way->AddPoint(PassingMap::GetCell(16,10));
	way->AddPoint(PassingMap::GetCell(14,8));
	way->AddPoint(PassingMap::GetCell(12,9));

	return way;
}

BuildCells* PassingMap::GenerateBuildCells(){
	BuildCells *buildCells = new BuildCells();
	buildCells->cells.push_back(PassingMap::GetCell(15,5));
	buildCells->cells.push_back(PassingMap::GetCell(5,3));
	buildCells->cells.push_back(PassingMap::GetCell(3,8));
	buildCells->cells.push_back(PassingMap::GetCell(7,15));
	buildCells->cells.push_back(PassingMap::GetCell(9,10));
	buildCells->cells.push_back(PassingMap::GetCell(16,5));	
	buildCells->cells.push_back(PassingMap::GetCell(7,17));
	buildCells->cells.push_back(PassingMap::GetCell(9,8));

	for(unsigned int i = 0; i < buildCells->cells.size(); i++){
		PassingMap::SetCellState(buildCells->cells[i]->indX, buildCells->cells[i]->indY, STATE_CELL_BUILD_FOR_US);
	}

	return buildCells;
}

Waypoint* PassingMap::GenerateSymmetricWaypoint(int startX, int startY, int finishX, int finishY, Waypoint *way)
{
	return NULL;
}

BuildCells* PassingMap::GenerateSymmetricBuildCellsForAI(int startX, int startY, int finishX, int finishY, BuildCells *cells)
{
	return NULL;
}