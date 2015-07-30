#pragma once
#include "Position.h"
class Dish
{
public:
	Dish();
	~Dish();

	Dish(int grid_size) { }
	position heat_grid_;
	position light_grid_;
};

