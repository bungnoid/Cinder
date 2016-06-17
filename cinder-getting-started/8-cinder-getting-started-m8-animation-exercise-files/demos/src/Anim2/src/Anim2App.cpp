////////////////////////////////////////////////////////////////////////////////
// Animating a circle along a sinusoidal path.
//
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Anim2App : public AppNative 
{
public:
    void prepareSettings( Settings* settings );
    void setup();
	void update();
	void draw();

private:
    // Position of the circle's center
    Vec2f mPosition;
};

void Anim2App::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60 );
}

void Anim2App::setup()
{
    // Start the animation from the left side of the window,
    // and at half the height
    mPosition = Vec2f( 0.0f, getWindowHeight() / 2.0f );
}

void Anim2App::update()
{
    //
    // Update circle's position, following a sinusoidal path.
    //

    // Move horizontally one pixel on the right
    mPosition.x++;

    // Calculate y = f(x) using a sinusoidal function
    const float Y0 = getWindowHeight() / 2.0f;
    const float A = getWindowHeight() / 3.0f;
    const float Pi = 3.14159265f;
    const float omega = 2.0f * Pi / getWindowWidth(); 
    mPosition.y = Y0 - A * sin( omega * (mPosition.x) );
}

void Anim2App::draw()
{
	// Clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Draw a yellow solid circle
    gl::color( Color( 1, 1, 0 ) );
    gl::drawSolidCircle( mPosition, 50 );
}

CINDER_APP_NATIVE( Anim2App, RendererGl )


////////////////////////////////////////////////////////////////////////////////
