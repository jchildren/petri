// Petri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Structures
#include "Position.h"

// Classes
#include "Cell.h"
#include "Food.h"
#include "Dish.h"

int main()
{
	
	// initialise
	const unsigned int kGridSize = 25;

	const unsigned int kPopulationMax = 15;
	const unsigned int kFoodMax = 30;

	const unsigned int kReproduceEnergy = 120;

	const unsigned int kCellStartEnergy = 100;
	const unsigned int kMaxFoodEnergy = 100;

	Dish petri(kGridSize);

	unsigned int total_population = 15;
	unsigned int total_food = 30;

	Cell *population[kPopulationMax];

	for (unsigned int i = 0; i < total_population; i++) {
		population[i] = new Cell;
		population[i]->add(kGridSize, kCellStartEnergy);
	}


	Food *supply[kFoodMax];

	for (unsigned int i = 0; i < total_food; i++) {
		supply[i] = new Food;
		supply[i]->add(kGridSize, kMaxFoodEnergy);
	}

	bool exit = false;
	unsigned int w = 1;

	while (w < 50) {

		/*
		// Process step
		*/

		for (unsigned int i = 0; i < total_population; i++) {
			if (population[i]->alive() == true) {
				// move
				population[i]->move(kGridSize);

				// consume
				for (unsigned int j = 0; j < total_food; j++) {
					if (population[i]->location() == supply[j]->location()) {
						population[i]->consume(supply[j]->energy(), 1);

						std::cout << j << " consumed";
	
						// copy
						delete[] supply[j];
						supply[j] = NULL;
						supply[j] = new Food;
						supply[j] = supply[total_food - 1];
						supply[total_food - 1] = nullptr;

						total_food--;
					}
				}

				for (unsigned int j = 0; j < total_population; j++) {
					if (j == i) {
						continue;
					}
					else if (population[i]->location() == population[j]->location()) {
						if ((population[i]->size() > population[j]->size()) || (population[j]->alive() == false)) {
							population[i]->consume(population[j]->energy(), population[j]->size());
							population[j]->set_alive(false);
							// copy
							delete[] population[j];
							population[j] = NULL;
							population[j] = new Cell;
							population[j] = population[total_population - 1];
							population[total_population - 1] = nullptr;

							total_population--;
						}
						else if ((population[j]->size() > population[i]->size()) || (population[i]->alive() == false)) {
							population[j]->consume(population[i]->energy(), population[i]->size());
							// copy
							delete[] population[i];
							population[i] = NULL;
							population[i] = new Cell;
							population[i] = population[total_population - 1];
							population[total_population - 1] = nullptr;

							total_population--;
							break;
						}

						std::cout << "Cell" << total_population << "no longer exists";
					}

				}

				// reproduce
				if ((total_population < kPopulationMax)&& population[i]->reproduce()) {
					total_population++;
					population[total_population] = new Cell;
					population[total_population] = population[i];
					population[i]->set_energy(population[i]->energy() / 2);
					population[total_population]->set_energy(population[total_population]->energy() / 2);
					population[total_population]->set_move_delay(0);
					population[total_population]->move(kGridSize);
				}
				

				// death
				if (population[i]->energy() <= 0) {
					population[i]->set_alive(false);
				}


			}
		}

		if (total_food < kFoodMax) {
			supply[total_food] = new Food;
			supply[total_food]->add(kGridSize, kCellStartEnergy);

			total_food++;
		}

		/*
		// Input step
		*/

		// poll user input

		/*
		// Display step
		*/

		// display grid

		// TODO: Optimise this horrible loop
		for (unsigned int i = 0; i < kGridSize; i++) {
			for (unsigned int j = 0; j < kGridSize; j++) { 
				bool occupied = false;
				position display_location;
				display_location.x = i;
				display_location.y = j;
				for (unsigned int k = 0; k < total_population; k++) {
					if (population[k]->location() == display_location) {
						if (population[k]->alive() == true) {
							std::cout << population[k]->energy();
						}
						else {
							std::cout << "-";
						}
						occupied = true;
					}
				}
				for (unsigned int k = 0; k < total_food; k++) {
					if (supply[k]->location() == display_location) {
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

