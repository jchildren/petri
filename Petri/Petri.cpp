// Petri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <vector>
#include <iostream>

struct position {
	int x;
	int y;

	bool operator==(const position& rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

};

class Molecule {
public:
	Molecule() {};
	~Molecule() {};

	bool exists_ = false;
	position location_;
	int energy_;


};

class Cell: public Molecule {
public:
	Cell();
	bool alive_ = false;

	int size() const { return size_; }

	void move();
	void consume(int energy, int size) { energy_ = energy_ + energy; size_ = size_ + size; };
	void reproduce() {};

private:
	int metabolism_;
	int size_;
	int move_delay_;

};

class Food: public Molecule {
public:

private:

};

struct Dish {
public:
	Dish(int grid_size){ }
	position heat_grid_;
	position light_grid_;
};

Cell::Cell() {
	size_ = 10 + rand() % 10;
	metabolism_ = rand() % 10;
}

void Cell::move() {
	energy_ = energy_ - metabolism_;

	if (move_delay_ = 0) {
		int direction = rand() % 4;

		if (direction == 0) {
			location_.x = location_.x + 1;
		}
		else if (direction == 1) {
			location_.y = location_.y + 1;
		}
		else if (direction == 2) {
			location_.x = location_.x - 1;
		}
		else if (direction == 3) {
			location_.y = location_.y - 1;
		}

		move_delay_ = size_ - metabolism_;
	}
	else {
		move_delay_ = move_delay_ - 1;
	}

}


int main()
{
	std::vector<int> consumed_cells;
	std::vector<int> consumed_food;
	
	// initialise
	const unsigned int kGridSize = 50;

	const unsigned int kPopulationMax = 10;
	const unsigned int kFoodMax = 50;

	const unsigned int kReproduceEnergy = 200;

	const unsigned int kCellStartEnergy = 100;
	const unsigned int kMaxFoodEnergy = 100;

	Cell population[kPopulationMax];
	Food supply[kFoodMax];
	Dish petri(kGridSize);

	unsigned int total_population = 10;
	unsigned int total_food = 50;

	for (unsigned int i = 0; i < total_population; i++) {
		// set alive
		population[i].exists_ = true;
		population[i].alive_ = true;

		// set locations
		population[i].location_.x = rand() % kGridSize;
		population[i].location_.y = rand() % kGridSize;

	}

	for (unsigned int j = 0; j < total_food; j++) {
		supply[j].exists_ = true;
		
		supply[j].location_.x = rand() % kGridSize;
		supply[j].location_.y = rand() % kGridSize;
	}

	bool exit = false;
	unsigned int w = 1;

	while (w < 100) {
		for (unsigned int i = 0; i < total_population; i++) {
			if (population[i].alive_ == true) {
				// move
				population[i].move();

				// consume
				for (unsigned int j = 0; j < total_food; j++) {
					if (population[i].location_ == supply[j].location_) {
						population[i].consume(supply[j].energy_, 1);
						supply[j].exists_ = false;
					}
				}

				for (unsigned int j = 0; j < total_population; j++) {
					if (j == i) {
						continue;
					}
					else if ((population[i].size() > population[j].size()) || (population[j].alive_ = false)) {
						population[i].consume(population[j].energy_, population[j].size());
						population[j].exists_ = false;
						population[j].alive_ = false;
						consumed_cells.push_back(j);
					}
				}

				// reproduce
				if ((total_population < kPopulationMax) && (population[i].energy_ >= kReproduceEnergy)) {
					population[i].reproduce();
					total_population++;
				}

				// death
				if (population[i].energy_ <= 0) {
					population[i].alive_ = false;
				}


			}

		}

		// compress locations

		// poll user input

		// display grid

		for (unsigned int i = 0; i < kGridSize; i++) {
			for (unsigned int j = 0; j < kGridSize; j++) {
				for (unsigned int k = 0; k < kPopulationMax; k++) {
					if ((population[k].location_.x == i) && (population[k].location_.y == j)) {
						std::cout << "+";
					}
				}
				for (unsigned int k = 0; k < kFoodMax; k++) {
					if ((supply[k].location_.x == i) && (supply[k].location_.y == j)) {
						std::cout << ".";
					}
				}

			}
			std::cout << "\n";
		}

		w++;
	}
	
	return 0;
}

