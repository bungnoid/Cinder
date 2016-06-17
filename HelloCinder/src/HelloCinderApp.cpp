#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HelloCinderApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HelloCinderApp::setup()
{
}

void HelloCinderApp::mouseDown( MouseEvent event )
{
	gl::clear(Color(0, 1, 0));
}

void HelloCinderApp::update()
{
}

void HelloCinderApp::draw()
{
	const int w = getWindowWidth() / 2;
	const int h = getWindowHeight() / 2;
	const double t = getElapsedSeconds();

	const float hue = sin(getElapsedSeconds()) * 0.5f + 0.5f;

	// clear out the window with black
	gl::clear( Color( CM_HSV, hue, 1, 1 ) );

	gl::lineWidth(3);
	gl::color(Color(0, 0, 0));
	Vec2f p1(w, h);
	Vec2f p2(sin(t)*w*0.5 + w, cos(t)*h*0.5 + h);
	Vec2f p3(sin(t*2)*w + p1[0], cos(t*2)*h + p1[1]);
	gl::drawLine(p1, p2);
	gl::drawLine(p2, p3);

	gl::color(Color(1, 1, 1));
	gl::drawStrokedCircle(p2, 20.0f);
	gl::drawSolidCircle(p3, 20.0f);
}

CINDER_APP_NATIVE( HelloCinderApp, RendererGl )
