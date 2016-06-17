///////////////////////////////////////////////////////////////////////////////
// PaintCirclesApp.cpp -- Cinder Demo Application serving as an example
//                        showing how to process user input.
//                        
// by Giovanni Dicanio
//
// Usage:
//
// - When user clicks the LEFT mouse button, a new circle is painted
//   having its center at the current mouse cursor position, 
//   with random color and random radius.
//
// - When user clicks the RIGHT mouse button, the more recent circle
//   is deleted.
//
// - When user presses the 'C' key on the keyboard, all circles are
//   deleted ('C' == "clear").
//
///////////////////////////////////////////////////////////////////////////////


#include "cinder/app/AppNative.h"       // Cinder's application base classes
#include "cinder/gl/gl.h"               // Basic drawing
#include "cinder/Rand.h"                // Cinder's pseudo-random numbers 
#include <vector>                       // std::vector to contain circles

using namespace ci;
using namespace ci::app;
using namespace std;


// Demo Application C++ class
class PaintCirclesApp : public AppNative 
{
public:

    //
    // Event Handlers
    //
    void setup(); 
    void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
    void update();
	void draw();


    //
    // Implementation
    //
private:
    
    // This class represents a circle.
    // It can draw itself on the screen, using the draw() method.
    class Circle
    {
    public:
        // Creates a circle with given parameters.
        Circle(Vec2f center, float radius, Color fillColor)
               : m_center(center)
               , m_radius(radius)
               , m_fillColor(fillColor)

        {
            // Nothing to do here
        }
       

        //
        // Accessors for circle's attributes/properties.
        //
        Vec2f center()    const { return m_center;    }
        float radius()    const { return m_radius;    }
        Color fillColor() const { return m_fillColor; }


        // Draws the circle.
        void draw()
        {
            // Set current drawing color
            gl::color(m_fillColor);

            // Draw a solid (i.e. "filled") circle
            gl::drawSolidCircle(m_center, m_radius);
        }

        //
        // Circle's Implementation
        //
    private:
        Vec2f m_center;
        float m_radius;
        Color m_fillColor;
    };


    // Container of circles to be drawn on screen.
    std::vector<Circle> m_circles;

    // Generates a circle at the specified center coordinate,
    // with random radius and color.
    Circle generateRandomCircleAt(Vec2f center)
    {
        // Generate a random value for radius in range [10, 50]
        float radius = Rand::randFloat(10.0f, 50.0f);

        // Generate a random color (with random hue)
        Color color(CM_HSV,                      // HSV color model
                    Rand::randFloat(0.0f, 1.0f), // random hue    
                    1.0f, 1.0f);                 // saturation and value = 1

        // Build and return a circle with these attributes
        return Circle(center, radius, color);
    }
};



void PaintCirclesApp::setup()
{
    // Initialize random seed generator
    Rand::randomize();
}


void PaintCirclesApp::mouseDown( MouseEvent event )
{
    //
    // Handle mouse click event.
    //
    // Left mouse button click: 
    //   - add a new circle at current mouse cursor coordinate.
    //
    // Right mouse button click: 
    //   - remove more recently inserted circle.
    //

    if (event.isLeft())
    {
        // Add new circle at current mouse cursor position
        m_circles.push_back( generateRandomCircleAt( event.getPos() ) );
    }
    else if (event.isRight())
    {
        // Remove more recent circle (if any)
        if (! m_circles.empty())
        {
            m_circles.pop_back();
        }
    }
}

void PaintCirclesApp::keyDown( KeyEvent event )
{
    // 
    // Handle key pressed on the keyboard
    //

    if ((event.getChar() == 'c') || (event.getChar() == 'C'))
    {
        // Remove all circles
        m_circles.clear();
    }
}

void PaintCirclesApp::update()
{
    // NOTHING TO DO
}

void PaintCirclesApp::draw()
{
	// Clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );

    // Draw all circles
    for (auto& circle : m_circles)    // for each circle
    {
        circle.draw();                // draw it
    }
}

CINDER_APP_NATIVE( PaintCirclesApp, RendererGl )


///////////////////////////////////////////////////////////////////////////////
