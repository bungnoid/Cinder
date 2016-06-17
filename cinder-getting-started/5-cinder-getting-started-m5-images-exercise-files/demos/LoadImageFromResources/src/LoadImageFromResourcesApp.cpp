//*****************************************************************************
// Loads an image from application's resources, and displays it.
// by Giovanni Dicanio
//*****************************************************************************

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // For gl::Texture
#include "cinder/ImageIo.h"         // For loading images
#include "Resources.h"              // Application's resources


using namespace ci;
using namespace ci::app;
using namespace std;

class LoadImageFromResourcesApp : public AppNative 
{
public:
	void setup();
	void draw();

private:
    // The image to be displayed
    gl::Texture mTexture;
};

void LoadImageFromResourcesApp::setup()
{
    // Load the image from application's resources.
    // The image is identified by its 'RES_BELLEVUE' ID
    // (defined in "Resources.h").
    mTexture = loadImage(loadResource(RES_BELLEVUE));
}

void LoadImageFromResourcesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Show the loaded image
    gl::draw(mTexture, getWindowBounds());
}

CINDER_APP_NATIVE( LoadImageFromResourcesApp, RendererGl )
