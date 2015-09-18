#pragma once
#include "Cell.h"
#include <list>

class CellController
{
public:
	CellController();
	~CellController();

	void update();
	void draw();
	void addCells(int amount);
	void removeCells(int amount);

	std::list<Cell> cell_list_;
};

