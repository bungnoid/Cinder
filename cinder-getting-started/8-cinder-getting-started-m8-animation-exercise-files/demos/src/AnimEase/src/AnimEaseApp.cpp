////////////////////////////////////////////////////////////////////////////////
// Animating from a start position to a target position, 
// using easing functions.
//
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Easing.h"          // For easing functions
#include "cinder/Rand.h"            // For generating pseudo-random numbers

using namespace ci;
using namespace ci::app;
using namespace std;


// Helper functions
namespace 
{

// Generates a pseudo-random vector inside our application window boundaries
Vec2f generateRandomVectorInsideWindow()
{
    // Generate two pseudo-random numbers for X and Y,
    // in range 0 --> max coordinate
    // (max coordinate == window width for X,
    //  max coordinate == window height for Y)
    const float maxX = static_cast<float>(app::getWindowWidth());
    const float maxY = static_cast<float>(app::getWindowHeight());
    return Vec2f( Rand::randFloat( 0.0f, maxX ),
                  Rand::randFloat( 0.0f, maxY ) );
}

} // anonymous namespace


//------------------------------------------------------------------------------
// Single particle to animate
//------------------------------------------------------------------------------
class Particle
{
public:

    //
    // Properties
    //

    Vec2f StartPos;
    Vec2f TargetPos;
    Vec2f CurrentPos;
    float Radius;
    float TimeBase;

    // NOTE: In production quality code, consider using private data members
    // with public getter/setter methods.


    // Initializes the particle with null values
    Particle()
        : StartPos(0.0f, 0.0f)
        , TargetPos(0.0f, 0.0f)
        , Radius(0.0f)
        , CurrentPos(0.0f, 0.0f)
        , TimeBase(0.0f)
    { }


    // Initializes the particle with client specified values
    Particle(Vec2f start, Vec2f target, float radius)
        : StartPos(start)
        , TargetPos(target)
        , Radius(radius)
        , CurrentPos(0.0f, 0.0f)
        , TimeBase(0.0f)
    { }


    // Updates the particle's position
    void update()
    {
        //
        // Calculate the new position, to progressively reach the target position,
        // using an easing function.
        //

        // Calculate the delta position vector, from the start position
        const Vec2f deltaPos = TargetPos - StartPos;


        // Time elapsed from the beginning of the animation
        const float deltaTime = static_cast<float>(app::getElapsedSeconds()) 
                                - TimeBase;

        // Parameter to control the speed of the animation.
        // (1 : fast; < 1 to slow down)
        static const float kAnimSpeed = 0.4f;

        // Calculate current position, using an easing function
        CurrentPos = easeOutCubic(kAnimSpeed * deltaTime) * deltaPos 
                     + StartPos;

        // If the particle reached the target position, 
        // just continue with a new animation, reaching a new target
        if ( CurrentPos.distance( TargetPos ) < 1.0f )
        {
            // Start next animation from here
            StartPos = CurrentPos;

            // Define a new (random) target
            TargetPos = generateRandomVectorInsideWindow();

            // Reset the timebase, to calculate delta time for next animation 
            // starting from now
            TimeBase = static_cast<float>(app::getElapsedSeconds());
        }
    }

    // Draws the particle on screen
    void draw()
    {
        // Draw using a solid circle
        gl::drawSolidCircle( CurrentPos, Radius );
    }
};


//------------------------------------------------------------------------------
// Demo application class
//------------------------------------------------------------------------------
class AnimEaseApp : public AppNative 
{
public:
    void prepareSettings( Settings* settings );
    void setup();
	void update();
	void draw();

private:
    // Particle (circle) to animate
    Particle mParticle;
};


void AnimEaseApp::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60 );
}


void AnimEaseApp::setup()
{
    // Initialize the pseudo-random number generator
    Rand::randomize();

    // Initialize the particle to animate
    mParticle = Particle(
        generateRandomVectorInsideWindow(), // random start pos
        generateRandomVectorInsideWindow(), // random target pos
        50.0f                               // radius
    );
}


void AnimEaseApp::update()
{
    // Calculate new position of the animated particle (circle)
    mParticle.update();
}


void AnimEaseApp::draw()
{
    // Clear out the rendering window with black
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) ); 

    // Draw a yellow particle at current position
    gl::color( Color( 1.0f, 1.0f, 0.0f ) );
    mParticle.draw();
}


CINDER_APP_NATIVE( AnimEaseApp, RendererGl )


////////////////////////////////////////////////////////////////////////////////
