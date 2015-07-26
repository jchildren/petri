// Petri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>


class Cell {
public:
	Cell() {};
	~Cell() {};

	bool exists_ = false;
	bool alive_ = false;
	int x_location_;
	int y_location_;

	int energy() const { return energy_; }

	void move() {};
	void consume(int energy) {};
	void reproduce() {};
	void die() {};

private:
	int energy_;
	int metabolism_;
	int size_;

};

class Food {
public:
	Food() {};
	~Food() {};

	bool exists_ = false;
	int x_location_;
	int y_location_;

	int energy() const { return energy_; }

private:

	int energy_;
};

struct Dish {
public:
	Dish(int grid_size){ }
	std::vector<int, int> heat_grid_;
	std::vector<int, int> light_grid_;
};

int main()
{
	// initialise
	const int kGridSize = 512;

	const int kPopulationMax = 10;
	const int kFoodMax = 50;

	const int kReproduceEnergy = 10;

	Cell population[kPopulationMax];
	Food supply[kFoodMax];
	Dish petri(kGridSize);

	int total_population = 10;
	int total_food = 50;

	for (unsigned int i = 0; i < total_population; i++) {
		// set alive
		population[i].exists_ = true;
		population[i].alive_ = true;

		// set locations
		population[i].x_location_ = rand() % kGridSize;
		population[i].y_location_ = rand() % kGridSize;

	}

	for (unsigned int j = 0; total_food; j++) {
		supply[j].exists_ = true;
		
		supply[j].x_location_ = rand() % kGridSize;
		supply[j].y_location_ = rand() % kGridSize;
	}

	bool exit = false;

	while (!exit) {
		for (unsigned int i = 0; i < total_population; i++) {
			if (population[i].alive_ == true) {
				// move
				population[i].move();

				// consume
				for (unsigned int j = 0; j < total_food; j++) {
					if ((population[i].x_location_ == supply[j].x_location_) && (population[i].y_location_ == supply[j].y_location_)) {
						population[i].consume(supply[j].energy());

					}
				}

				// reproduce
				if ((total_population < kPopulationMax) && (population[i].energy() >= kReproduceEnergy)) {
					population[i].reproduce();
				}

				// death
				if (population[i].energy() <= 0) {
					population[i].die();
				}


			}

		}

		// compress locations

		// poll user input
	}
	
	return 0;
}

