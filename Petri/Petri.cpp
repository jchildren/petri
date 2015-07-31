// Petri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Structures
#include "Position.h"

// Classes
#include "Cell.h"
#include "Food.h"
#include "Dish.h"


int check_consume_cell(Cell* active_cell, Cell* cell_to_check, Cell* last_cell) {
	if (active_cell == cell_to_check) {
		return 0;
	}
	else if (active_cell->location() == cell_to_check->location()) {
		if (active_cell->size() >= cell_to_check->size()) {
			if (active_cell != last_cell) {
				active_cell->consume_cell(cell_to_check, last_cell);
			}
			else {
				active_cell->consume(cell_to_check->energy(), cell_to_check->size());
			}
		}
		else {
			cell_to_check->consume_cell(active_cell, last_cell);
		}
		// Two cells enter, one cell leaves!
		return 1;
	}
	else {
		return 0;
	}
}

int main()
{
	
	// initialise
	const unsigned int kGridSize = 25;

	const unsigned int kPopulationMax = 30;
	const unsigned int kFoodMax = 50;

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

				for (unsigned j = 0; j < total_food; j++) {
					if (population[i]->location() == supply[j]->location()) {
						total_food--;
						population[i]->consume_food(supply[j], supply[total_food]);
						supply[total_food] = nullptr;
					}
				}

				for (unsigned j = 0; j < total_population; j++) {
					switch (check_consume_cell(population[i], population[j], population[total_population - 1]))
					{
					case 0:
						continue;
					case 1:
						if (i != total_population - 1) {
							total_population--;
							population[total_population] = nullptr;
						}
						break;
					default:
						break;
					} 
				}
				

				// reproduce
				if ((total_population < kPopulationMax) && (population[i]->reproduce())) {
					population[total_population] = new Cell;
					*population[total_population] = *population[i];
					population[i]->set_energy(population[i]->energy() / 2);
					population[total_population]->set_energy(population[total_population]->energy() / 2);
					population[total_population]->set_move_delay(0);
					population[total_population]->move(kGridSize);

					total_population++;
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
		std::cout << "\n" << total_population;

		std::cout.flush();
		Sleep(1500);

		w++;
	}

	// clean up memory
	for (unsigned int i = 0; i < total_population; i++) {
		delete[] population[i];
	}

	for (unsigned int i = 0; i < total_food; i++) {
		delete[] supply[i];
	}
	
	
	return 0;
}

