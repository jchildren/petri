#include "stdafx.h"
#include "Food.h"


Food::Food()
{
}

Food::Food(int grid_size, int energy)
{

	// set locations
	location_.x = rand() % grid_size;
	location_.y = rand() % grid_size;

	energy_ = energy;

}


Food::~Food()
{
}
