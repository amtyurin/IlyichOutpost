#include "PanelTowers.h"


PanelTowers::PanelTowers(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 1,5, ccp, size)
{	
	this->SetCellBorderImage("panel_border_common.png");
}


PanelTowers::~PanelTowers(void)
{
}
