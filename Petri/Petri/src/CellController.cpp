#include "..\include\CellController.h"
#include "cinder\app\AppNative.h"
#include "cinder\Rand.h"

CellController::CellController()
{
}


CellController::~CellController()
{
}

void CellController::update()
{
	for (auto c = population_.begin(); c != population_.end(); ++c){
		c->update();
	}

	for (auto c1 = population_.begin(); c1 != population_.end(); ++c1){
		for (auto c2 = population_.begin(); c2 != population_.end(); ++c2){
			if (c1 != c2){
				if (c2->can_consume(*c1)){
					c1->radius_ += c2->radius_;
					population_.erase(c2);
					break;
				}
			}
		}
	}
}

void CellController::draw()
{
	for (auto c = population_.begin(); c != population_.end(); ++c){
		c->draw();
	}
}

void CellController::addCells(int amount)
{
	for (int i = 0; i<amount; i++)
	{
		float x = ci::Rand::randFloat(ci::app::getWindowWidth());
		float y = ci::Rand::randFloat(ci::app::getWindowHeight());
		population_.push_back(Cell(ci::Vec2f(x, y)));
	}
}

void CellController::removeCells(int amount)
{
	for (int i = 0; i<amount; i++)
	{
		population_.pop_back();
	}
}