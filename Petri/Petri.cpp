// Petri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Position.h"

#include "Cell.h"
#include "Food.h"
#include "Dish.h"

int main()
{
	std::vector<int> consumed_cells;
	std::vector<int> consumed_food;
	
	// initialise
	const unsigned int kGridSize = 25;

	const unsigned int kPopulationMax = 15;
	const unsigned int kFoodMax = 50;

	const unsigned int kReproduceEnergy = 120;

	const unsigned int kCellStartEnergy = 100;
	const unsigned int kMaxFoodEnergy = 100;

	Cell population[kPopulationMax];
	Food supply[kFoodMax];
	Dish petri(kGridSize);

	unsigned int total_population = 15;
	unsigned int total_food = 30;

	for (unsigned int i = 0; i <= total_population; i++) {
		// set alive
		population[i].exists_ = true;
		population[i].alive_ = true;

		// set locations
		population[i].location_.x = rand() % kGridSize;
		population[i].location_.y = rand() % kGridSize;

		population[i].energy_ = kCellStartEnergy;

	}

	for (unsigned int j = 0; j < total_food; j++) {
		supply[j].exists_ = true;
		
		supply[j].location_.x = rand() % kGridSize;
		supply[j].location_.y = rand() % kGridSize;

		supply[j].energy_ = rand() % kMaxFoodEnergy;
	}

	bool exit = false;
	unsigned int w = 1;

	while (w < 50) {
		for (unsigned int i = 0; i < total_population; i++) {
			if (population[i].alive_ == true) {
				// move
				population[i].move();

				// consume
				for (unsigned int j = 0; j < total_food; j++) {
					if (population[i].location_ == supply[j].location_) {
						population[i].consume(supply[j].energy_, 1);
						supply[j].exists_ = false;
						consumed_food.push_back(j);
					}
				}

				for (unsigned int j = 0; j < total_population; j++) {
					if (j == i) {
						continue;
					}
					else if (population[i].location_ == population[j].location_){
						if ((population[i].size() > population[j].size()) || (population[j].alive_ == false)) {
							population[i].consume(population[j].energy_, population[j].size());
							population[j].exists_ = false;
							population[j].alive_ = false;
							consumed_cells.push_back(j);
						}
						else if ((population[j].size() > population[i].size()) || (population[i].alive_ == false)) {
							population[j].consume(population[i].energy_, population[i].size());
							population[i].exists_ = false;
							population[i].alive_ = false;
							consumed_cells.push_back(i);
							continue;
						}
					}

				}

				// reproduce
				if ((total_population < kPopulationMax) && (population[i].energy_ >= kReproduceEnergy)) {
					population[i].reproduce();
					total_population++;
					population[total_population] = population[i];
					population[i].energy_ = population[i].energy_ / 2;
					population[total_population].energy_ = population[total_population].energy_ / 2;
					population[total_population].move_delay_ = 0;
					population[total_population].move();
				}
	
				// death
				if (population[i].energy_ <= 0) {
					population[i].alive_ = false;
				}


			}

		}

		// compress population into sequential class members
		for (unsigned int i = 0; i < consumed_cells.size(); i++, total_population--) {
			// copy
			population[consumed_cells[i]] = population[total_population];
			population[total_population].exists_ = false;
			std::cout << "Cell" << total_population << "no longer exists";
		}

		// clear the vector to allow size to return to 0
		consumed_cells.clear();

		// compress population into sequential class members
		for (unsigned int i = 0; i < consumed_food.size(); i++, total_food--) {
			// copy
			supply[consumed_food[i]] = supply[total_food];
			supply[total_food].exists_ = false;
		}

		// clear the vector to allow size to return to 0
		consumed_food.clear();

		// add new food
		supply[total_food].exists_ = true;

		supply[total_food].location_.x = rand() % kGridSize;
		supply[total_food].location_.y = rand() % kGridSize;

		supply[total_food].energy_ = rand() % kMaxFoodEnergy;

		total_food++;

		// poll user input

		// display grid

		// TODO: Optimise this horrible loop
		for (unsigned int i = 0; i < kGridSize; i++) {
			for (unsigned int j = 0; j < kGridSize; j++) { 
				bool occupied = false;
				position display_location;
				display_location.x = i;
				display_location.y = j;
				for (unsigned int k = 0; k < total_population; k++) {
					if (population[k].location_ == display_location) {
						if (population[k].alive_ == true) {
							std::cout << population[k].energy_;
						}
						else {
							std::cout << "-";
						}
						occupied = true;
					}
				}
				for (unsigned int k = 0; k < total_food; k++) {
					if (supply[k].location_ == display_location) {
						std::cout << ".";
						occupied = true;
					}
				}
				if (occupied == false) {
					std::cout << " ";
				}
				else {
					occupied = false;
				}

			}
			std::cout << "\n";
		}
		
		for (unsigned int i = 0; i < kGridSize; i++) {
			std::cout << "=";
		}
		std::cout << "\n";

		std::cout.flush();
		Sleep(1500);

		w++;
	}
	
	return 0;
}

