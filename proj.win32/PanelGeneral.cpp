#include "PanelGeneral.h"


PanelGeneral::PanelGeneral(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 4,1, ccp, size)
{
	this->SetCellBorderImage("panel_border_common.png");
}


PanelGeneral::~PanelGeneral(void)
{
}
