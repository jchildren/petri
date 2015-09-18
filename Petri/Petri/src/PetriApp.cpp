#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "../include/CellController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PetriApp : public AppNative {
public:
	void prepareSettings(Settings* settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	CellController cell_controller_;
};

void PetriApp::prepareSettings(Settings* settings)
{
	settings->setWindowSize(800, 400);
	settings->setFrameRate(60.0f);
}

void PetriApp::setup()
{
	cell_controller_.addCells(250);
}

void PetriApp::mouseDown( MouseEvent event )
{
}

void PetriApp::update()
{
	cell_controller_.update();
}

void PetriApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	cell_controller_.draw();
}

CINDER_APP_NATIVE( PetriApp, RendererGl )
