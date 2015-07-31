#pragma once
#include "Position.h"
class Molecule
{
public:
	Molecule();
	virtual ~Molecule();

	// Integer energy value that can dictate and object's behaviour
	int energy_;
	// Structure consisting of integer x and y co-ordinates that determines the objects
	// position on the grid
	position location_;


	// Virtual function for adding molecule based classes to the grid
	virtual int add(int grid_size, int energy);
	// Computes the parameters of the class after a time step
	virtual int time_step();
	
	
	// Accessor function for energy_
	virtual int energy() const { return energy_; }
	// Accesor function for location_
	virtual position location() const { return location_; }
	
};

