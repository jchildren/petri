#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
	size_ = 10 + rand() % 10;
	metabolism_ = rand() % 10;
	move_delay_ = 1;
}


Cell::~Cell()
{
}


void Cell::move() {

	int direction = 0;

	if (move_delay_ == 0) {
		energy_ = energy_ - metabolism_;
		direction = rand() % 4;

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

		move_delay_ = 1;
	}
	else {
		move_delay_ = move_delay_ - 1;
	}
}