#include "PanelGeneral.h"


PanelGeneral::PanelGeneral(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 4,1, ccp, size)
{
	this->SetCellBorderImage(FILE_NAME_IMAGE_PANEL_BORDER);

	this->SetCellContentImage(FILE_NAME_IMAGE_PANEL_COIN, 0,0);	
}


PanelGeneral::~PanelGeneral(void)
{
}
