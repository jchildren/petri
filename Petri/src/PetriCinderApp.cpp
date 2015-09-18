#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PetriCinderApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void PetriCinderApp::setup()
{
}

void PetriCinderApp::mouseDown( MouseEvent event )
{
}

void PetriCinderApp::update()
{
}

void PetriCinderApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( PetriCinderApp, RendererGl )
