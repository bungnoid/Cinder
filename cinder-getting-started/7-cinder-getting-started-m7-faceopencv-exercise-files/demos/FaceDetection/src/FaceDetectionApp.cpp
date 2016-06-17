//*****************************************************************************
// Cinder application to detect faces in an image.
// Uses the OpenCV CinderBlock for the face detection job.
// by Giovanni Dicanio <giovanni.dicanio@gmail.com>
//*****************************************************************************

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "CinderOpenCV.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;


// ------------------------------------------------
// Cinder application to detect faces in an image.
// ------------------------------------------------
class FaceDetectionApp : public AppNative 
{
public:
	void setup();
	void draw();
	
private:
    
    // Cascade classifier, used to detect faces
    cv::CascadeClassifier mFaceClassifier;
    
    // Test image, in which we'll try detecting faces
    Surface mImage;
    
    // All the faces detected in the image.
    // Each face is localized by a single rectangle (bounding box).
    std::vector<Rectf> mFaces;
};


namespace // anonymous
{

// Converts from vector of OpenCV rectangles, to vector of Cinder rectangles. 
std::vector<ci::Rectf> fromOcv(const std::vector<cv::Rect>& cvRects)
{
    // Resulting vector of Cinder's rectangles (starts empty)
    std::vector<ci::Rectf> rects;

    // For each OpenCV rectangle in the input vector
    for (const auto& cvRect : cvRects)
    {
        // Convert from OpenCV rectangle to Cinder rectangle
        ci::Rectf rect( ci::fromOcv(cvRect) );

        // Add the Cinder rectangle to the output vector
        rects.push_back(rect);
    }

    // Return the vector containing Cinder rectangles
    return rects;
}

} // anonymous namespace




void FaceDetectionApp::setup()
{
    // Load the test image from assets
    mImage = loadImage(loadAsset("image.png"));

    // Make the application window the same size of the loaded image
    setWindowSize(mImage.getWidth(), mImage.getHeight());

    // Name of the XML file with data for the face cascade classifier
    static const char * kClassifierFilename = "haarcascade_frontalface_alt.xml"; 
    
    // Load the XML classifier file for detecting faces
    mFaceClassifier.load( getAssetPath(kClassifierFilename).string() );

    // Convert the image from Cinder's format (Surface) 
    // to OpenCV's format (cv::Mat).
    // 
    // Matrix data types use this format:
    //
    //    CV_<bit depth>(S|U|F)C<number of channels>
    //
    //    S = Signed integer
    //    U = Unsigned integer
    //    F = Float
    //
    // So, CV_8UC1 means:
    //    8U --> 8-bit unsigned integer
    //    C1 --> single-channel matrix
    //
    cv::Mat cvImage( toOcv(mImage, CV_8UC1) );
    
    // Detect faces using the cascade classifier object
    std::vector<cv::Rect> cvFaces;
    mFaceClassifier.detectMultiScale( cvImage, cvFaces );
    
    // Convert face bounding rectangles from OpenCV's format 
    // (using cv::Rect) to Cinder's format (using Rectf)
    mFaces = fromOcv(cvFaces);
}

void FaceDetectionApp::draw()
{
    // Draw the test image first
    gl::color(1.0, 1.0, 1.0);
    gl::draw(mImage);

    // Then draw faces bounding boxes, using some transparency
    // for the bounding rectangles.
    gl::color( ColorA(1.0f, 1.0f, 0.0, 0.4f) );
    for (const auto& face : mFaces)
    {
        gl::drawStrokedRect(face);
    }
}

CINDER_APP_NATIVE( FaceDetectionApp, RendererGl )

//*****************************************************************************
