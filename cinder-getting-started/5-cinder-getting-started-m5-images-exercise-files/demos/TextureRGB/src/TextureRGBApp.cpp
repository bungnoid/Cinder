//*****************************************************************************
// Loads an image from application's resources, and displays it.
// Shows the single R,G,B image channels when the user presses the 'r','g','b'
// keys on the keyboard respectively.
// Pressing the 'a' (as "all") key displays the original image (with _all_
// the R,G,B color channels).
// In this demo, color channels are selected using the GPU and the
// gl::color() function.
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

class TextureRGBApp : public AppNative 
{
public:
	void setup();
	void keyDown( KeyEvent event );	
	void draw();

private:

    // Show mode: all the RGB channels, or just one of them.
    enum class ShowMode 
    {
        Complete,
        Red,
        Green,
        Blue
    };

    // Currently selected show mode
    ShowMode mShowMode;

    // Image loaded from resources
    gl::Texture mTexture;
};

void TextureRGBApp::setup()
{
    // Load image from resources
    mTexture = loadImage(loadResource(RES_IMAGE));
    
    // Start displaying the original image, with all color components
    mShowMode = ShowMode::Complete;
}

void TextureRGBApp::keyDown( KeyEvent event )
{
    const char ch = event.getChar();
    switch (ch) 
    {
    case 'r':
        // Show only the red channel
        mShowMode = ShowMode::Red;
        break;
    case 'g':
        // Show only the green channel
        mShowMode = ShowMode::Green;
        break;
    case 'b':
        // Show only the blue channel
        mShowMode = ShowMode::Blue;
        break;
    case 'a':
        // Show the complete image, with all RGB components
        mShowMode = ShowMode::Complete;
        break;
    default:
        break;
    }
}

void TextureRGBApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

    // Use the gl::color() function to select the particular
    // color channel for displaying the image stored in the texture.
    // (gl::color(1,1,1) activates all the R,G,B channels.)
    switch (mShowMode)
    {
    case ShowMode::Complete:
        gl::color(1, 1, 1);     // All the R,G,B components
        break;
    case ShowMode::Red:
        gl::color(1, 0, 0);     // Only the red component
        break;
    case ShowMode::Green:
        gl::color(0, 1, 0);     // Only the green component
        break;
    case ShowMode::Blue:
        gl::color(0, 0, 1);     // Only the blue component
        break;
    }

    // Display the texture containing the image loaded from resources
    gl::draw(mTexture, getWindowBounds());
}

CINDER_APP_NATIVE( TextureRGBApp, RendererGl )
