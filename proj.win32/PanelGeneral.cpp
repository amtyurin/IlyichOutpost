#include "PanelGeneral.h"


PanelGeneral::PanelGeneral(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 4,1, ccp, size)
{
	this->SetCellBorderImage("panel_border_common.png");

	this->SetCellContentImage("coin.png", 0,0);
	this->DisplayText(1, "100","Arial",20,0,0,5,0);
}


PanelGeneral::~PanelGeneral(void)
{
}
