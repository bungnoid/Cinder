//******************************************************************************
// Cinder application that loads an image from assets, and allows adjusting 
// the brightness and contrast of that image, using a GUI built with 
// the InterfaceGl class.
//
// Users can switch between the modified image and the original image 
// pressing the SPACEBAR.
//
// by Giovanni Dicanio <giovanni.dicanio@gmail.com>
//
//******************************************************************************


//------------------------------------------------------------------------------
//                              Includes
//------------------------------------------------------------------------------

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"   // For InterfaceGl
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"

// Import some namespaces for convenience
using namespace ci;
using namespace ci::app;
using namespace std;


//------------------------------------------------------------------------------
// Cinder Application C++ class
//------------------------------------------------------------------------------
class BrightnessContrastApp : public AppNative 
{
public:
	
    //
    // *** Event Handlers ***
    //
    void setup();
    void keyDown(KeyEvent event);
    void update();
    void draw();


    //
    // *** Data Members ***
    //
private:
    // The input original image
    Surface32f mImageInput;

    // The output modified image, with different brightness and contrast
    Surface32f mImageOutput;

    // Flag to indicate if we should display the original image ('true'),
    // or the modified image ('false')
    bool mShowOriginal;

    // Current brightness value
    float mBrightness;

    // Previous brightness value
    float mBrightnessPrev;
    
    // Current contrast value
    float mContrast;

    // Previous contrast value
    float mContrastPrev;
    
    // InterfaceGl instance, used to build a GUI to modify the
    // brightness and contrast parameters
    params::InterfaceGl mParams;

    // Helper method, to compare floating-point numbers
    // with some tolerance 
    // (Note that direct == comparison between floating-point numbers
    // is generally wrong.)
    static bool equal(float x, float y, float tolerance = 0.001f);

    // Apply the brightness-contrast adjustment combined equation,
    // returning the new pixel value, based on the input pixel value,
    // and considering the mBrightness and mContrast (data members) parameters.
    float adjustBrightnessContrast(float value);
};



//==============================================================================
//                          Method Implementations
//==============================================================================


//------------------------------------------------------------------------------
// Application Setup
//------------------------------------------------------------------------------
void BrightnessContrastApp::setup()
{
    //
    // Load an image from assets, used as input image.
    // We use the classical "Lenna" here as test image.
    //
    // More info on Lenna can be found here:
    //
    //   http://en.wikipedia.org/wiki/Lenna
    //
    mImageInput = loadImage(loadAsset("lenna.png"));
    

    //
    // Build a surface with the same width and height of the input image,
    // and no alpha channel.
    // This surface will be filled with the output processed image,
    // built pixel-by-pixel.
    //
    mImageOutput = Surface32f(
        mImageInput.getWidth(),         // width, in pixels
        mImageInput.getHeight(),        // height, in pixels
        false                           // no alpha channel
    );


    //
    // Initialize brightness/contrast data members
    //
    mBrightness      = 0.0f;  // start with no brightness adjustment
    mBrightnessPrev  = -0.5f; // assume previous brightness was lowest possible
    mContrast        = 1.0f;  // start with no contrast adjustment
    mContrastPrev    = 0.0f;  // assume previous contrast was lowest possible

    // NOTE:
    // Having set the initial "previous" brightness and contrast values
    // different from the "current" values will trigger the calculation of
    // mImageOutput in the update() method when the application starts.

    // Start in "show modified image" mode
    mShowOriginal = false;

    // Set the application window size according to the loaded image size
    setWindowSize(mImageInput.getWidth(), mImageInput.getHeight());


    //
    // Use InterfaceGl to build a GUI to modify the brightness 
    // and contrast parameters
    //

    // Set GUI title and size
    mParams = params::InterfaceGl("Adjustment Params", Vec2i(200, 80));
    
    // Add control for brightness
    mParams.addParam(
        "Brightness",                                    // caption
        &mBrightness,                                    // data member binding
        "min=-0.5 max=0.5 step=0.01 keyIncr=b keyDecr=v" // properties
    );

    // Add control for contrast
    mParams.addParam(
        "Contrast",                                      // caption
        &mContrast,                                      // data member binding
        "min=0.0  max=2.0 step=0.01 keyIncr=c keyDecr=x" // properties
    );

}


//------------------------------------------------------------------------------
// Key-Press Event Handler
//------------------------------------------------------------------------------
void BrightnessContrastApp::keyDown(KeyEvent event)
{
    // Space switches between original (input) image 
    // and processed (output) image
    if (event.getChar() == ' ')
    {
        mShowOriginal = !mShowOriginal;
    }
}


//------------------------------------------------------------------------------
// Comparison with tolerance between floating-point numbers
//------------------------------------------------------------------------------
bool BrightnessContrastApp::equal(float x, float y, float tolerance)
{
    if (fabs(x - y) < tolerance) 
        return true;
    else
        return false;
}


//------------------------------------------------------------------------------
// Implementation of the brightness-contrast combined equation
//------------------------------------------------------------------------------
float BrightnessContrastApp::adjustBrightnessContrast(float value)
{
    return (value - 0.5f) * mContrast + 0.5f + mBrightness;
}


//------------------------------------------------------------------------------
// Update Event Handler
//------------------------------------------------------------------------------
void BrightnessContrastApp::update()
{
    // Recalculate the output image only if brightness or contrast changed
    if (equal(mBrightness, mBrightnessPrev) && equal(mContrast, mContrastPrev))
    {
        // Same brightness and contrast from last call, 
        // so there's no need to recalculate the output image
        return;
    }

    
    //
    // *** Image Processing Code ***
    //

    // Get an iterator to access pixels in the input image (read-only)
    Surface32f::ConstIter pixelInIter = mImageInput.getIter(); 
    
    // Get an iterator to access pixels in the output image (read-write) 
    Surface32f::Iter pixelOutIter = mImageOutput.getIter();

    
    // NOTE:
    // In the following nested loops, the input and output iterators
    // are advanced in a *synchronized* way.

    // For each line in the input and output images...
    while (pixelInIter.line())
    {
        pixelOutIter.line();

        // For each pixel in current line in input and output images...
        while (pixelInIter.pixel()) 
        {
            pixelOutIter.pixel();
        
            
            //
            // *** Pixel Transform ***
            //
            // Just apply the brightness and contrast equation to each
            // color component (red, green and blue) of current input pixel.
            // As a result of that, we'll get the color components 
            // of the _corresponding_ output pixel.
            //
            pixelOutIter.r() = adjustBrightnessContrast(pixelInIter.r());
            pixelOutIter.g() = adjustBrightnessContrast(pixelInIter.g());
            pixelOutIter.b() = adjustBrightnessContrast(pixelInIter.b());
        }
    }


    // Save the current values of brightness and contrast
    // (so in this update() method it'll be possible to check if these
    // values changed from call to call)
    mBrightnessPrev = mBrightness;
    mContrastPrev = mContrast;
}


//------------------------------------------------------------------------------
// Draw Event Handler
//------------------------------------------------------------------------------
void BrightnessContrastApp::draw()
{
    //
    // We have to possible drawing modes:
    //
    // - Just showing the original (input, unprocessed) image
    //
    // - Showing the modified (output) image, with the InterfaceGl GUI overlapped
    //
    if (mShowOriginal) 
    {
        // Show the original (input) image
        gl::draw(mImageInput, getWindowBounds());
    }
    else
    {
        // Show the modified (output) image
        gl::draw(mImageOutput, getWindowBounds());
        
        // Show the InterfaceGl GUI on top of that
        mParams.draw();
    }

    //
    // Note that in the previous calls to gl::draw(),
    // a texture object is *implicitly* created from
    // the Surface32f object, using this gl::Texture
    // constructor overload:
    //
    // Texture::Texture( const Surface32f &surface, Format format )
    //
    // This gl::Texture object is then passed to gl::draw().
    //
}



CINDER_APP_NATIVE( BrightnessContrastApp, RendererGl )
