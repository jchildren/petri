#pragma once
#include "Molecule.h"
#include "Food.h"

class Cell :
	protected Molecule
{
public:
	Cell();
	Cell(int grid_size, int energy);
	virtual ~Cell();

private:
	// Boolean variable that determines whether the cell is active
	bool alive_;
	// Rate at which a cell consumes energy on each time step
	// Higher metabolism means more activity but faster energy consumption
	int metabolism_;
	// Energy required for cell to reproduce through mitosis
	int reproduce_energy_;
	// Integer value for cell size that determines whether a Cell can consume other objects
	int size_;
	// Integer defining the number of time steps before a cell moves
	int move_delay_;
public:
	/*
	// Functions related to cell lifetime
	*/
	
	// Function based on the molecule verison of add() so set Cells to alive (molecules are not alive)
	int add(int grid_size, int energy);
	// Derived from the Molecule virtual function, computes the parameters of the object after a time step
	int time_step();
	// 
	int move(int grid_size);
	// Member function that processes cell consumption of other objects
	int consume(int energy, int size);
	//
	bool reproduce();

	int consume_food(Food food_to_eat);
	int consume_cell(Cell cell_to_eat);

	/*
	// Accessor functions
	*/

	// Accesor function for alive_
	bool alive() const { return alive_; }
	// Accesor function for size_
	int size() const { return size_; }
	// Accessor function for energy_
	int energy() const { return energy_; }
	// Accesor function for location_
	position location() const { return location_; }

	/*
	// Mutator functions
	*/

	// Mutator for energy_
	void set_energy(int energy) { energy_ = energy; }
	// Mutator for alive_
	void set_alive(bool alive) { alive_ = alive; }
	// Mutator for move_delay_
	void set_move_delay(int move_delay) { move_delay_ = move_delay; }
};

