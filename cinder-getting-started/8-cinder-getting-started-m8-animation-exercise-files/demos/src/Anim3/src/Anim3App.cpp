////////////////////////////////////////////////////////////////////////////////
// Animating from a start position to a target position.
//
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"            // For generating pseudo-random numbers

using namespace ci;
using namespace ci::app;
using namespace std;

class Anim3App : public AppNative 
{
public:
	void prepareSettings( Settings* settings );
    void setup();
	void update();
	void draw();

private:
    Vec2f mCurrentPos;  // Current position for the animated object (circle)
    Vec2f mTargetPos;   // Target position for the animated object (circle)

    // Generates a pseudo-random vector inside our application window boundaries
    Vec2f GenerateRandomVectorInsideWindow();
};


Vec2f Anim3App::GenerateRandomVectorInsideWindow()
{
    // Generate two pseudo-random numbers for X and Y,
    // in range 0 --> max coordinate
    // (max coordinate == window width for X,
    //  max coordinate == window height for Y)
    const float maxX = static_cast<float>(getWindowWidth());
    const float maxY = static_cast<float>(getWindowHeight());
    return Vec2f( Rand::randFloat( 0.0f, maxX ),
                  Rand::randFloat( 0.0f, maxY ) );
}

void Anim3App::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60 );
}

void Anim3App::setup()
{
    // Reset the random seed based on the clock
    Rand::randomize();

    // Start from a random position inside our window
    mCurrentPos = GenerateRandomVectorInsideWindow();

    // Go to a random position inside our window
    mTargetPos = GenerateRandomVectorInsideWindow();
}

void Anim3App::update()
{
    //
    // Calculate the new position, to progressively reach the target position.
    //

    // 1. Calculate the delta position vector
    Vec2f deltaPos = mTargetPos - mCurrentPos;

    // 2. Progressively reduce the length of the delta position vector,
    //    multiplying the delta vector by a positive scalar less than 1
    deltaPos *= 0.97f;

    // 3. Recalculate current position
    //    (this will be progressively nearer to target position)
    mCurrentPos = mTargetPos - deltaPos;


    // If we reached the target position, just continue the demo
    // reaching a new target
    if (mCurrentPos.distance(mTargetPos) < 1.0f)
    {
        // Generate a new pseudo-random vector for the new target position
        mTargetPos = GenerateRandomVectorInsideWindow();
    }
}

void Anim3App::draw()
{
	// Clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Draw a yellow solid circle at current position
    gl::color( Color( 1, 1, 0 ) );
    gl::drawSolidCircle( mCurrentPos, 50 );
}



CINDER_APP_NATIVE( Anim3App, RendererGl )
