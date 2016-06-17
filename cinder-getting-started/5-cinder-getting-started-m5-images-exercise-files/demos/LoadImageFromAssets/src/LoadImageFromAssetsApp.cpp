//*****************************************************************************
// Loads an image from assets, and displays it.
// by Giovanni Dicanio
//*****************************************************************************

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // For gl::Texture
#include "cinder/ImageIo.h"         // For image loading

using namespace ci;
using namespace ci::app;
using namespace std;

class LoadImageFromAssetsApp : public AppNative 
{
public:
	void setup();
	void draw();
private:
    // This texture will contain the image loaded from assets
    gl::Texture mTexture;
};

void LoadImageFromAssetsApp::setup()
{
    // Load the test image from assets
    mTexture = loadImage(loadAsset("image.jpg"));
}

void LoadImageFromAssetsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Display the image
    gl::draw(mTexture, getWindowBounds());
}

CINDER_APP_NATIVE( LoadImageFromAssetsApp, RendererGl )
