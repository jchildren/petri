#include "..\include\Cell.h"
#include "cinder\gl\gl.h"
#include "cinder\Rand.h"

Cell::Cell(ci::Vec2f pos)
{
	position_ = pos;
	velocity_ = ci::Rand::randVec2f() * ci::Rand::randFloat(5.0f);
	radius_ = 5.0f;
}

Cell::~Cell()
{
}

void Cell::update()
{
	position_ += velocity_;
}

void Cell::draw()
{
	ci::gl::drawSolidCircle(position_, radius_);
}