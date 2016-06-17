////////////////////////////////////////////////////////////////////////////////
// Initial Drawing Experiments with Cinder
// by Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DrawingApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void DrawingApp::setup()
{
    // NOTHING TO DO HERE
}

void DrawingApp::mouseDown( MouseEvent event )
{
    // NOTHING TO DO HERE
}

void DrawingApp::update()
{
    // NOTHING TO DO HERE
}

//
// *** DRAWING CODE ***
//
void DrawingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 


    // Get app window's extension, to correctly draw 
    // also in case of window resizing
    const int w = getWindowWidth();
    const int h = getWindowHeight();


    // Set drawing color to yellow
    gl::color( Color( 1, 1, 0 ) );
    
    // Draw a slightly thicker line
    gl::lineWidth( 5 );

    // Draw diagonal line, from left-top, to right-bottom corner
    gl::drawLine(Vec2f(0, 0), Vec2f(w, h));


    // Set drawing color to blue
    gl::color( Color( 0, 0, 1 ) );

    // Draw opposite diagonal line
    //   (w, 0) --> right-top corner
    //   (0, h) --> left-bottom corner
    gl::drawLine( Vec2f(w, 0), Vec2f(0, h) );
}

CINDER_APP_NATIVE( DrawingApp, RendererGl )

////////////////////////////////////////////////////////////////////////////////
