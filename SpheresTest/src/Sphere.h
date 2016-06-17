#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include <vector>
#include <stdlib.h>

using namespace ci;
using namespace ci::app;
using namespace std;

#include <time.h>

namespace sphere{

	class Sphere
	{
	public:
		Sphere(vec3 p = vec3(), float r = 1.0f, int segs = 12){
			_p = p;
			_r = r;
			_seg = segs;
			_c = ((float)rand()) / (float)RAND_MAX;
		};

		void draw(){
			gl::drawSphere(_p, _r, _seg);
		};

		void setPosition(vec3 p){
			_p = p;
		};

		vec3 getPosition(){
			return _p;
		};

		float getColor(){
			return _c;
		};

		Sphere split(){

			//srand(time(NULL));

			//console() << time(NULL) << endl;

			const float x = ((float)rand()) / (float)RAND_MAX;
			const float y = ((float)rand()) / (float)RAND_MAX;
			const float z = ((float)rand()) / (float)RAND_MAX;
			const float d = 2;
			vec3 offset((x - 0.5f)*d, (y - 0.5f)*d, (z - 0.5f)*d);
			glm::normalize(offset);
			Sphere new_sphere(offset + _p);

			return new_sphere;
		};

	protected:
		vec3 _p;	// position
		float _r;	// radius
		int _seg;	// segments
		float _c;	// colour hue value
	};

}