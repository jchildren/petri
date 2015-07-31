#include "stdafx.h"
#include "Molecule.h"


Molecule::Molecule()
	: energy_(0),
	location_()
{
}


Molecule::~Molecule()
{
}


// Virtual function for adding molecule based classes to the grid
int Molecule::add(int grid_size, int energy)
{

	// set locations
	location_.x = rand() % grid_size;
	location_.y = rand() % grid_size;

	energy_ = energy;

	return 0;
}


// Computes the parameters of the class after a time step
int Molecule::time_step()
{
	return 0;
}
