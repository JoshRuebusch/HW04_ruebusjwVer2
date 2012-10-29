#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "ruebusjwStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_ruebusjwVer2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	//ruebusjwStarbucks rs;

};

void HW04_ruebusjwVer2App::setup()
{
	
}

void HW04_ruebusjwVer2App::mouseDown( MouseEvent event )
{
}

void HW04_ruebusjwVer2App::update()
{
}

void HW04_ruebusjwVer2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_ruebusjwVer2App, RendererGl )
