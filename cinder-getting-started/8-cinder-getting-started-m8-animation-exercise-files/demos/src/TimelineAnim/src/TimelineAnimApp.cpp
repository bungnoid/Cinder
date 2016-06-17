////////////////////////////////////////////////////////////////////////////////
// Animates several properties (circle's position, radius and color)
// using the timeline.
//
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"            // For pseudo-random number generation
#include "cinder/Timeline.h"        // For animating with the timeline

using namespace ci;
using namespace ci::app;
using namespace std;

// Demo application class
class TimelineAnimApp : public AppNative 
{
public:
    void prepareSettings( Settings* settings );
    void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();


    // *** DATA MEMBERS ***
private:   

    // Animated property: Position of the circle's center
    Anim<Vec2f> mCenterPos;

    // Animated property: Radius of the circle
    Anim<float> mRadius;

    // Animated property: Circle's color
    Anim<Color> mColor;
};


// Utility functions in anonymous namespace
namespace 
{

// Generates a pseudo-random color.
inline Color randomColor()
{
    // Use the HSV (Hue-Saturation-Value) color model.
    // Just generate a pseudo-random hue for the color.
    return Color( CM_HSV, randFloat(), 1.0f, 1.0f );
}

} // anonymous


void TimelineAnimApp::prepareSettings( Settings* settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60 );
}

void TimelineAnimApp::setup()
{
    // Initialize the pseudo-random number generator
    Rand::randomize();

    // Define starting values for our animated properties
    mCenterPos = getWindowCenter();
    mRadius    = randFloat( 10.0f, 100.0f );
    mColor     = randomColor();
}

void TimelineAnimApp::mouseDown( MouseEvent event )
{
    // Set target values for the animated properties
    const Vec2f newCenterPos = event.getPos();  // click position
    const float newRadius    = randFloat( 10.0f, 100.0f );
    const Color newColor     = randomColor();

    // Start the animations of these properties using the timeline
    timeline().apply( &mCenterPos, newCenterPos, 1.0f, EaseInAtan()  );
    timeline().apply( &mRadius,    newRadius,    1.0f, EaseInCirc()  );
    timeline().apply( &mColor,     newColor,     1.0f, EaseInCubic() );
}

void TimelineAnimApp::update()
{
    // NOTHING TO DO HERE :)
}

void TimelineAnimApp::draw()
{
    // Clear the background with black
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );

    // Draw the circle using the current color, 
    // at the current position, and with the current radius value.
    gl::color( mColor.value() ); 
    gl::drawSolidCircle( mCenterPos.value(), mRadius.value() );        
}

CINDER_APP_NATIVE( TimelineAnimApp, RendererGl )

////////////////////////////////////////////////////////////////////////////////

