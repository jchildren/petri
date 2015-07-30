#pragma once
#include "Molecule.h"

class Cell :
	public Molecule
{
public:
	Cell();
	~Cell();

	bool alive_ = false;

	int size() const { return size_; }

	void move();
	void consume(int energy, int size) { energy_ = energy_ + energy; size_ = size_ + size; };
	void reproduce() {};

	int move_delay_;

private:
	int metabolism_;
	int size_;
};

