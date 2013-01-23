#include "Waypoint.h"

#include <algorithm>

Waypoint::Waypoint(void)
{
	way.resize(0);
	position = 0;
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

Cell* Waypoint::GetFirstPoint()
{
	if (way.size() > 0)
	{
		position = 0;
		return way[position];
	}
	else
		return NULL;
}

Cell* Waypoint::GetNextPoint()
{	
	if (position + 1< way.size())
	{		
		position++;
		return way[position];
	}
	else
		return NULL;
}