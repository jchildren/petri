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
	for (auto c = cell_list_.begin(); c != cell_list_.end(); ++c){
		c->update();
	}
}

void CellController::draw()
{
	for (auto c = cell_list_.begin(); c != cell_list_.end(); ++c){
		c->draw();
	}
}

void CellController::addCells(int amount)
{
	for (int i = 0; i<amount; i++)
	{
		float x = ci::Rand::randFloat(ci::app::getWindowWidth());
		float y = ci::Rand::randFloat(ci::app::getWindowHeight());
		cell_list_.push_back(Cell(ci::Vec2f(x, y)));
	}
}

void CellController::removeCells(int amount)
{
	for (int i = 0; i<amount; i++)
	{
		cell_list_.pop_back();
	}
}