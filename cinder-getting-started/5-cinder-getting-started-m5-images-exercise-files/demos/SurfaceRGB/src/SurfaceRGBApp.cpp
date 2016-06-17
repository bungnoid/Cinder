//*****************************************************************************
// Loads an image from application's resources, and displays it.
// Shows the single R,G,B image channels when the user presses the 'r','g','b'
// keys on the keyboard respectively.
// Pressing the 'a' (as "all") key displays the original image (with _all_
// the R,G,B color channels).
//
// by Giovanni Dicanio
//*****************************************************************************

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SurfaceRGBApp : public AppNative 
{
public:
	void setup();
    void keyDown( KeyEvent event );
	void draw();
private:
    gl::Texture mOriginal;      // Original image, loaded from resources
    gl::Texture mOnlyRed;       // Only the red channel
    gl::Texture mOnlyGreen;     // Only the green channel
    gl::Texture mOnlyBlue;      // Only the blue channel
    gl::Texture mCurrent;       // Current image to be displayed
};

void SurfaceRGBApp::setup()
{
    // Load the original image from resources
    Surface image = loadImage(loadResource(RES_IMAGE));

    //
    // Extract the red component
    //
    Surface redImage = image.clone();
    Surface::Iter redIter = redImage.getIter();
    while (redIter.line())
    {
        while (redIter.pixel())
        {
            // Leave red unchanged; zero out green and blue
            redIter.g() = 0;
            redIter.b() = 0;
        }
    }

    //
    // Extract the green component
    //
    Surface greenImage = image.clone();
    Surface::Iter greenIter = greenImage.getIter();
    while (greenIter.line())
    {
        while (greenIter.pixel())
        {
            // Leave green unchanged; zero out red and blue
            greenIter.r() = 0;
            greenIter.b() = 0;
        }
    }

    //
    // Extract the blue component
    //
    Surface blueImage = image.clone();
    Surface::Iter blueIter = blueImage.getIter();
    while (blueIter.line())
    {
        while (blueIter.pixel())
        {
            // Leave blue unchanged; zero out red and green
            blueIter.r() = 0;
            blueIter.g() = 0;
        }
    }

    //
    // Create textures corresponding to previously built images
    //
    mOriginal   = image;
    mOnlyRed    = redImage;
    mOnlyGreen  = greenImage;
    mOnlyBlue   = blueImage;
    
    // Start displaying the original image
    mCurrent = mOriginal;
}

void SurfaceRGBApp::keyDown( KeyEvent event )
{
    if (event.getChar() == 'r')
    {
        // Display only the red channel
        mCurrent = mOnlyRed;
    }
    else if (event.getChar() == 'g')
    {
        // Display only the green channel
        mCurrent = mOnlyGreen;
    }
    else if (event.getChar() == 'b')
    {
        // Display only the blue channel
        mCurrent = mOnlyBlue;
    }
    else if (event.getChar() == 'a')
    {
        // Display the original image (with _all_ R,G,B channels)
        mCurrent = mOriginal;
    }
}

void SurfaceRGBApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    // Display currently selected image
    gl::draw(mCurrent, getWindowBounds());
}

CINDER_APP_NATIVE( SurfaceRGBApp, RendererGl )
