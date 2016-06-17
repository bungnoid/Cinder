////////////////////////////////////////////////////////////////////////////////
// Cinder Drawing Experiment: Drawing the Flag of Italy
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FlagOfItalyApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void FlagOfItalyApp::setup()
{
    // NOTHING TO DO HERE
}

void FlagOfItalyApp::mouseDown( MouseEvent event )
{
    // NOTHING TO DO HERE
}

void FlagOfItalyApp::update()
{
    // NOTHING TO DO HERE
}

//
// *** DRAWING CODE: The Flag of Italy ***
//
void FlagOfItalyApp::draw()
{
    // Define color constants for the Flag of Italy
    const Color red  ( 0.80f, 0.17f, 0.21f );
    const Color green( 0.00f, 0.57f, 0.27f );
    const Color white( 1.00f, 1.00f, 1.00f );

    // Rendering window size
    const int w = getWindowWidth();
    const int h = getWindowHeight();

    // Clear out the window with white
    gl::clear( white );

    // Draw the green left bar
    gl::color( green );
    gl::drawSolidRect( Rectf( 0, 0, w / 3.0f, h ) );

    // Draw the red right bar
    gl::color( red );
    gl::drawSolidRect( Rectf( 2.0f * w/3.0f, 0, w, h ) );
}

CINDER_APP_NATIVE( FlagOfItalyApp, RendererGl )

////////////////////////////////////////////////////////////////////////////////
