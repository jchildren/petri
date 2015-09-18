#include "..\include\Cell.h"
#include "cinder\gl\gl.h"
#include "cinder\Rand.h"

Cell::Cell(ci::Vec2f pos)
{
	position_ = pos;
	velocity_ = ci::Rand::randVec2f() * ci::Rand::randFloat(1.0f);
	radius_ = ci::Rand::randFloat(5.0f);
}

Cell::~Cell()
{
}

void Cell::update()
{
	ci::Vec2f center = ci::Vec2f::zero();
	ci::Vec2f dir_center   = position_ - center;
    float dist_center  = dir_center.length();
    float max_dist   = 300.0f;
    if( dist_center > max_dist ){
        float pull_strength = 0.0001f;
        velocity_ -= dir_center.normalized() * ( ( dist_center - max_dist ) * pull_strength );
    }

	position_ += velocity_;
}

void Cell::draw()
{
	ci::gl::drawSolidCircle(position_, radius_);
}

bool Cell::can_consume(Cell target)
{
	bool is_nearby = false;
	bool is_bigger = false;
	
	if (within_radius(target.position_)){
		is_nearby = true;
	}

	if (target.radius_ > radius_){
		is_bigger = true;
	}

	return is_nearby && is_bigger;
}

bool Cell::within_radius(ci::Vec2f pos)
{
	ci::Vec2f displacement = position_ - pos;

	if (displacement.length() < radius_){
		return true;
	}

	return false;
}