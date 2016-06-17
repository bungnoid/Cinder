#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/params/Params.h"

#include <vector>
#include <iterator>

#include "Sphere.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SpheresTestApp : public App {
  public:
	void prepareSettings(Settings *settings);
	void setup() override;
	void update() override;
	void draw() override;
	void mouseDown(MouseEvent event) override;
	void keyDown(KeyEvent event);

	gl::BatchRef geo;

	vector<sphere::Sphere> spheres;

	params::InterfaceGl	mParams;

	// CAMERA Controls
	CameraPersp cam;
	quat mSceneRotation;
	float mCameraDistance;
	vec3 mEye, mCenter, mUp;
};

void SpheresTestApp::prepareSettings(Settings *settings) {
	settings->setFrameRate(60);
	settings->setFullScreen(true);
}

void SpheresTestApp::setup()
{
	auto lambert = gl::ShaderDef().lambert().color();
	gl::GlslProgRef shader = gl::getStockShader(lambert);
	geo = gl::Batch::create(geom::Sphere(), shader);

	cam.lookAt(vec3(15), vec3(0));
	
	spheres.push_back(sphere::Sphere());
}

void SpheresTestApp::mouseDown( MouseEvent event )
{	
	vector<sphere::Sphere> new_spheres;
	new_spheres.resize(spheres.size());
	for (unsigned i = 0; i < spheres.size(); i++){
		new_spheres[i] = spheres[i].split();
	}
	spheres.reserve(spheres.size() + std::distance(new_spheres.begin(), new_spheres.end()));
	spheres.insert(spheres.end(), new_spheres.begin(), new_spheres.end());
}

void SpheresTestApp::keyDown(KeyEvent event)
{
	switch (event.getCode())
	{
	case KeyEvent::KEY_ESCAPE:
		quit();
		break;
	default:
		break;
	}
}

void SpheresTestApp::update()
{
}

void SpheresTestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );

	// turn on z-buffering
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::setMatrices(cam);

	for (unsigned i = 0; i < spheres.size(); i++){
		gl::pushModelMatrix();
		gl::translate(spheres[i].getPosition());
		gl::color(Color(CM_HSV, spheres[i].getColor(), 0.5, 1));
		geo->draw();
		gl::popModelMatrix();
	}

}

CINDER_APP(SpheresTestApp, RendererGl)
