#include "PanelBase.h"


PanelBase::PanelBase(CCScene *scene, const int cellsX, const int cellsY, const CCPoint ccp, const CCSize size) 
{	
	panelSprite = CCSprite::create();

	scene->addChild(panelSprite);

	this->cellsX = cellsX;
	this->cellsY = cellsY;

	panelSprite->setPosition(ccp);
	panelSprite->setContentSize(size);
}

PanelBase::~PanelBase(void)
{
	panelSprite->removeFromParent();
	panelSprite->removeAllChildrenWithCleanup(true);
}

void PanelBase::SetCellBorderImage(const char* image)
{
	int sizeX = panelSprite->getContentSize().width / this->cellsX;
	int sizeY = panelSprite->getContentSize().height / this->cellsY;

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

			panelSprite->addChild(sprites[i][j], 1);
		}
	}
}

void PanelBase::SetCellContentImage(const char* image, const int cellX, const int cellY)
{
	CCSprite * sprite = CCSprite::create(image);

	SetCellContentSprite(sprite, cellX, cellY);
}

void PanelBase::SetCellContentSprite(CCSprite *sprite, const int cellX, const int cellY)
{
	if (cellX >= 0 && cellX < cellsX &&
		cellY >= 0 && cellY < cellsY)
	{
		int sizeX = panelSprite->getContentSize().width / this->cellsX;
		int sizeY = panelSprite->getContentSize().height / this->cellsY;

		float scaleX = sizeX / sprite->getContentSize().width;
		float scaleY = sizeY / sprite->getContentSize().height;

		sprite->setScaleX(scaleX * 0.8);
		sprite->setScaleY(scaleY * 0.8);
		sprite->setPositionX(sizeX / 2 + cellX * sizeX);
		sprite->setPositionY(sizeY / 2 + cellY * sizeY);

		panelSprite->addChild(sprite, 1);

		return;
	}

	CCLog("Wrong cell index %d %d", cellX, cellY);
}
