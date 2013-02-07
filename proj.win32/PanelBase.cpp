#include "PanelBase.h"

using namespace cocos2d;

PanelBase::PanelBase(const int cellsX, const int cellsY, const CCPoint ccp, const CCSize size) 
{	
	panelSprite = CCSprite::create();
	
	this->cellsX = cellsX;
	this->cellsY = cellsY;

	this->cells = new PanelCell*[this->cellsX];
	for(int i = 0; i < this->cellsX; i++){
		this->cells[i] = new PanelCell[this->cellsY];
	}
	for(int x = 0; x < this->cellsX; x++){
		for(int y = 0; y < this->cellsY; y++){
			strcpy(this->cells[x][y].text, "");
			cells[x][y].spriteCell = NULL;
		}
	}

	this->panelSprite->setPosition(ccp);
	this->panelSprite->setContentSize(size);
}

PanelBase::~PanelBase(void)
{
	this->panelSprite->removeFromParent();
	this->panelSprite->removeAllChildrenWithCleanup(true);
}

void PanelBase::SetCellBorderImage(const char* image)
{
	int sizeX = this->panelSprite->getContentSize().width / this->cellsX;
	int sizeY = this->panelSprite->getContentSize().height / this->cellsY;

	CCSprite ***sprites = new CCSprite**[this->cellsX];
	for(int i = 0; i < this->cellsX; ++i){
		sprites[i] = new CCSprite*[this->cellsY];
	}

	sprites[0][0] = CCSprite::create(image);
	float scaleX = sizeX / sprites[0][0]->getContentSize().width;
	float scaleY = sizeY / sprites[0][0]->getContentSize().height;

	for(int i = 0; i < this->cellsX; ++i){
		for(int j = 0; j < this->cellsY; ++j){
			if (i != 0 || j != 0){
				sprites[i][j] = CCSprite::create(image);
			}
			sprites[i][j]->setScaleX(scaleX);
			sprites[i][j]->setScaleY(scaleY);
			sprites[i][j]->setPositionX(sizeX / 2 + i * sizeX);
			sprites[i][j]->setPositionY(sizeY / 2 + j * sizeY);
			
			cells[i][j].spriteCell = sprites[i][j];

			panelSprite->addChild(sprites[i][j], 1);
		}
	}
}

void PanelBase::SetCellContentImage(const char* image, const int cellX, const int cellY)
{
	if (cellX >= 0 && cellX < this->cellsX &&
		cellY >= 0 && cellY < this->cellsY){
		CCSprite * sprite = CCSprite::create(image);

		SetCellContentSprite(sprite, cellX, cellY, 0, 0);
	}
}

void PanelBase::SetCellContentSprite(CCSprite *sprite, const int cellX, const int cellY, const int locX, const int locY)
{
	if (cellX >= 0 && cellX < this->cellsX &&
		cellY >= 0 && cellY < this->cellsY){

		sprite->setPositionX(cells[cellX][cellY].spriteCell->getTextureRect().size.width / 2 + locX);
		sprite->setPositionY(cells[cellX][cellY].spriteCell->getTextureRect().size.height / 2 + locY);

		//cells[cellX][cellY].spriteCell->addChild(sprite, 1);
		return;
	}

	CCLog("SetCellContentSprite: Wrong cell index %d %d", cellX, cellY);
}

void PanelBase::DisplayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY)
{
	if (cellX >= 0 && cellX < this->cellsX &&
		cellY >= 0 && cellY < this->cellsY){
		if (strncmp(cells[cellX][cellY].text, text, TEXT_SIZE)){

			CCLabelTTF* pLabel = CCLabelTTF::create(text, font, size);
			int cellWidth = cells[cellX][cellY].spriteCell->getContentSize().width * cells[cellX][cellY].spriteCell->getScaleX();
			int cellHeight = cells[cellX][cellY].spriteCell->getContentSize().height * cells[cellX][cellY].spriteCell->getScaleY();
			pLabel->setPositionX(cellWidth / 2 + cellWidth * cellX + locX);
			pLabel->setPositionY(cellHeight / 2 + cellHeight * cellY + locY);
			pLabel->setColor(ccc3(255,255,51));

			panelSprite->removeChildByTag(tag);
			
			panelSprite->addChild(pLabel, 2, tag);

			strncpy(cells[cellX][cellY].text, text, TEXT_SIZE);

			return;
		}
		return;
	}

	CCLog("DisplayText: Wrong cell index %d %d", cellX, cellY);
}

void PanelBase::RemoveCellContentSprite(CCSprite *sprite)
{
	//sprite->removeFromParent();
}
