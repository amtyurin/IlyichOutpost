#include "Waypoint.h"

#include <algorithm>

Waypoint::Waypoint(void)
{
	way.resize(0);
}


Waypoint::~Waypoint(void)
{
}

void Waypoint::AddPoint(Cell *cell)
{
	if (cell->type == STATE_CELL_FREE)
	{
		way.push_back(cell);
	}
}

void Waypoint::RemovePoint(const Cell *cell)
{
	way.erase(std::remove(way.begin(), way.end(), cell), way.end());
}

Cell* Waypoint::GetPoint(const int index)
{
	if (index >= 0 && index < way.size())
	{
		return way[index];
	}
	else
		return NULL;
}