#pragma once
#include "Position.h"
class Molecule
{
public:
	Molecule();
	~Molecule();

	bool exists_ = false;
	position location_;
	int energy_;
};

