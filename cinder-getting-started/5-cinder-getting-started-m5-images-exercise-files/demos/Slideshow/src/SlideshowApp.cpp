//*****************************************************************************
// Implements a slideshow application, displaying some images loaded from
// resources.
// The user can press the left and right arrow keys on the keyboard to
// select the slides in the slideshow.
//
// by Giovanni Dicanio
//*****************************************************************************

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"          // For gl::Texture
#include "cinder/ImageIo.h"             // For image loading
#include "Resources.h"                  // Resources containing images
#include <vector>                       // For std::vector container

using namespace ci;
using namespace ci::app;
using namespace std;

class SlideshowApp : public AppNative 
{
public:
	void setup();
	void keyDown(KeyEvent event);
	void draw();
private:
    // Images loaded from resources are stored in a STL vector container
    vector<gl::Texture> mSlides;
    
    // Index of current image (slide)
    int mCurrent;
};

void SlideshowApp::setup()
{
    //
    // Load the images from the resources.
    // Images are stored as gl::Texture's in the std::vector container.
    // The std::vector::push_back() method dynamically and automatically
    // grows the vector.
    //
    mSlides.push_back( loadImage(loadResource(RES_SLIDE1)) );
    mSlides.push_back( loadImage(loadResource(RES_SLIDE2)) );
    mSlides.push_back( loadImage(loadResource(RES_SLIDE3)) );
    mSlides.push_back( loadImage(loadResource(RES_SLIDE4)) );
    mSlides.push_back( loadImage(loadResource(RES_SLIDE5)) );
    
    // Start with first image (index 0).
    // Note that valid indexes in the vector go from 0 to (size-1).
    mCurrent = 0;
}

void SlideshowApp::keyDown( KeyEvent event )
{
    if (event.getCode() == KeyEvent::KEY_RIGHT)
    {
        // Move to next image
        mCurrent++;

        // Check index bounds in the vector of images
        if (mCurrent >= static_cast<int>(mSlides.size()))
        {
            // If the last image was reached, then continue from the
            // first image
            mCurrent = 0;
        }
    }
    else if (event.getCode() == KeyEvent::KEY_LEFT)
    {
        // Move to previous image
        mCurrent--;
        
        // Check index bounds in the vector of images
        if (mCurrent < 0)
        {
            // If the first image was reached, then continue from the
            // last image
            mCurrent = static_cast<int>(mSlides.size() - 1);
        }
    }
}

void SlideshowApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Draw current slide
    gl::draw( mSlides[mCurrent], getWindowBounds() );
}

CINDER_APP_NATIVE( SlideshowApp, RendererGl )
