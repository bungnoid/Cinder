////////////////////////////////////////////////////////////////////////////////
// Basic circle animation.
// Starts from the center of the window, and moves the circle
// towards the right bottom corner, increasing the circle
// center X and Y coordinates.
//
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Anim1App : public AppNative 
{
public:
    void prepareSettings( Settings* settings );
    void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
    Vec2f mPosition;    // Circle's center position
};


void Anim1App::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60 );
}

void Anim1App::setup()
{
    // Start from the center of the window
    mPosition = getWindowCenter();
}

void Anim1App::mouseDown( MouseEvent event )
{
    // Unused
}

void Anim1App::update()
{
    // Unused
}

void Anim1App::draw()
{
	// Clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Update the circle's center position
    mPosition.x++;
    mPosition.y++;

    // NOTE: In production code, the position update code
    // should be put inside the update() method; but this is just
    // a first introductory demo...

    // Draw a solid yellow circle, with its center located in mPosition,
    // and with a radius of 100 pixels
    gl::color( Color( 1, 1, 0 ) );
    gl::drawSolidCircle( mPosition, 100 );
}

CINDER_APP_NATIVE( Anim1App, RendererGl )
