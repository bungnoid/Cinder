////////////////////////////////////////////////////////////////////////////////
// Cinder Drawing Experiment: Drawing the Flag of Japan
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FlagOfJapanApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void FlagOfJapanApp::setup()
{
    // NOTHING TO DO HERE
}

void FlagOfJapanApp::mouseDown( MouseEvent event )
{
    // NOTHING TO DO HERE
}

void FlagOfJapanApp::update()
{
    // NOTHING TO DO HERE
}

//
// *** DRAWING CODE: The Flag of Japan ***
//
void FlagOfJapanApp::draw()
{
    // Define colors to draw the flag of Japan
    const Color red  ( 1, 0, 0 );
    const Color white( 1, 1, 1 );

    // Clear out the window with white
    gl::clear( white );

    // Draw a solid red circle at the center of the window
    gl::color( red );
    gl::drawSolidCircle( getWindowCenter(), getWindowWidth()/6.0f );
}

CINDER_APP_NATIVE( FlagOfJapanApp, RendererGl )

////////////////////////////////////////////////////////////////////////////////
