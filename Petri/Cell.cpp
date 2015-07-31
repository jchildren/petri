#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
	: reproduce_energy_(0)
	, size_(0)
	, alive_(false)
	, metabolism_(0)
	, move_delay_(0) 
{
	size_ = 10 + rand() % 10;
	metabolism_ = rand() % 10;
	move_delay_ = 1;
	reproduce_energy_ = 120;
}


Cell::~Cell()
{
}


int Cell::move(int grid_size) {

	int direction = 0;

	if (move_delay_ == 0) {
		energy_ = energy_ - metabolism_;
		direction = rand() % 4;

		if ((direction == 0) && (location_.x < grid_size - 1)) {
			location_.x = location_.x + 1;
		}
		else if ((direction == 1) && (location_.y < grid_size - 1)) {
			location_.y = location_.y + 1;
		}
		else if ((direction == 2) && (location_.x > 0)) {
			location_.x = location_.x - 1;
		}
		else if ((direction == 3) && (location_.y > 0)) {
			location_.y = location_.y - 1;
		}

		move_delay_ = 1;
	}
	else {
		move_delay_ = move_delay_ - 1;
	}

	return 0;
}

// Virtual function based on the molecule verison of add() so set Cells to alive (molecules are not alive)
int Cell::add(int grid_size, int energy)
{

	// set locations
	location_.x = rand() % grid_size;
	location_.y = rand() % grid_size;

	reproduce_energy_ = 80 + (rand() % 40);

	energy_ = energy;

	alive_ = true;
	return 0;
}


// Derived from the Molecule virtual function, computes the parameters of the object after a time step
int Cell::time_step()
{
	return 0;
}


// Member function that processes cell consumption of other objects
int Cell::consume(int energy, int size)
{
	energy_ = energy_ + energy; size_ = size_ + size;
	return 0;

}

bool Cell::reproduce() {
	if (energy_ <= reproduce_energy_) {
		return true;
	}
	else {
		return false;
	}
}

int Cell::consume_food(Food* food_to_eat, Food* food_to_move) {
	
	energy_ = energy_ + food_to_eat->energy(); 
	size_ = size_ + 1;

	// move and dellocate
	*food_to_eat = *food_to_move;
	delete[] food_to_move;

	return 0;
}

int Cell::consume_cell(Cell* cell_to_eat, Cell* cell_to_move) {
	
	energy_ = energy_ + cell_to_eat->energy();
	size_ = size_ + size_;

	// move and deallocate
	*cell_to_eat = *cell_to_move;
	delete[] cell_to_move;

	return 0;
}