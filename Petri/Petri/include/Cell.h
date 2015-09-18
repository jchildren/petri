#pragma once

#include "cinder\Vector.h"

class Cell
{
public:
	Cell(ci::Vec2f pos);
	~Cell();

	float radius_;
	ci::Vec2f position_;
	ci::Vec2f velocity_;

	void update();
	void draw();
};

