#include "PanelTowers.h"


PanelTowers::PanelTowers(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 1,5, ccp, size)
{	
	this->SetCellBorderImage("panel_border_common.png");

	this->SetCellContentImage(FILE_NAME_IMAGE_TOWER_MACHINE_GUN, 0,0);
	this->SetCellContentImage(FILE_NAME_IMAGE_TOWER_HEAVY_GUN, 0,1);
}


PanelTowers::~PanelTowers(void)
{
}
