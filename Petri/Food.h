#pragma once
#include "Molecule.h"
class Food :
	public Molecule
{
public:
	Food();
	virtual ~Food();

	// Accessor function for energy_
	int energy() const { return energy_; }
	// Accesor function for location_
	position location() const { return location_; }
};

