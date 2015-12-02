// Petri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Structures
#include "Position.h"

// Classes
#include "Cell.h"
#include "Food.h"
#include "Dish.h"


bool can_consume_cell(Cell active_cell, Cell cell_to_check) {
	if (&active_cell == &cell_to_check) {
		return false;
	}
	else if (active_cell.location() == cell_to_check.location()) {
		if (active_cell.size() >= cell_to_check.size()) {
			active_cell.consume_cell(cell_to_check);
		}
		else {
			cell_to_check.consume_cell(active_cell);
		}
		// Two cells enter, one cell leaves!
		return true;
	}
	else {
		return false;
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

	std::vector<Cell> population;

	for (unsigned int i = 0; i < total_population; i++) {
		population.push_back(Cell(kGridSize, kCellStartEnergy));
	}

	std::list<Food> supply;

	for (unsigned int i = 0; i < total_food; i++) {
		supply.push_back(Food(kGridSize, kMaxFoodEnergy));
	}

	bool exit = false;
	unsigned int w = 1;

	while (w < 50) {

		/*
		// Process step
		*/
		for (auto cell = population.begin(); cell != population.end(); ++cell) {
			if (cell->alive() == true) {
				// move
				cell->move(kGridSize);

				for (auto food = supply.begin(); food != supply.end(); ++food) {
					if (cell->location() == food->location()) {
						total_food = supply.size();
						cell->consume_food(*food);
						food = supply.erase(food);
					}
				}

				for (auto target = population.begin(); target != population.end(); ++target) {
					switch (can_consume_cell(*cell, *target))
					{
					case false:
						continue;
					case true:
						target = population.erase(target);
						break;
					default:
						break;
					} 
				}
				

				// reproduce
				if ((total_population < kPopulationMax) && (cell->reproduce())) {
					population.push_back(Cell(kGridSize, cell->energy() / 2));
					cell->set_energy(cell->energy() / 2);

					total_population = population.size();
				}



				// death
				if (cell->energy() <= 0) {
					cell->set_alive(false);
				}
			}
		}

		if (total_food < kFoodMax) {
			supply.push_back(Food(kGridSize, kMaxFoodEnergy));

			total_food = supply.size();
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
				for (Cell cell : population) {
					if (cell.location() == display_location) {
						if (cell.alive() == true) {
							std::cout << cell.energy();
						}
						else {
							std::cout << "-";
						}
						occupied = true;
					}
				}
				for (Food food : supply) {
					if (food.location() == display_location) {
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

	population.clear();
	supply.clear();
	
	return 0;
}

