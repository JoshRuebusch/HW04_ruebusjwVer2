#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "cinder/Text.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/Text.h"
#include "ruebusjwStarbucks.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_ruebusjwVer2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void shapeDrawer(float x_, float y_, int red, int green, int blue, bool isLookingForClosest);
	void prepareSettings(Settings* settings);

	Entry* e;
	Census* c_;
	Census* c_2010;

	Entry* closestStar;
	int arrLen;
	int censusArrLen;
	int censusArrLen2010;
	bool growCalled;
	bool isLookingForClosest_;
	node* root;
	static const int appWidth = 800;
	static const int appHeight = 600;
	
private:
	gl::Texture myImage;
	ruebusjwStarbucks rs;
	int skippedBucks;
	int frameNumber;
	double xPos;
	double yPos;
	//void shapeDrawer(float x_, float y_, int red, int green, int blue);
	

};

void HW04_ruebusjwVer2App::prepareSettings(Settings* settings){
	settings->setWindowSize(appWidth,appHeight);
	settings->setResizable(false);
}

Entry* grow(Entry* smallArray, int arrayLen){
	Entry* newArray = new Entry[arrayLen*2];
	for(int i = 0; i < arrayLen; i++)
	{
		newArray[i] = smallArray[i];
	}
	
	return newArray;
}

Census* grow(Census* smallArray, int arrayLen){
	Census* newArray = new Census[arrayLen*2];
	for(int i = 0; i < arrayLen; i++)
	{
		newArray[i] = smallArray[i];
	}
	
	return newArray;
}

void HW04_ruebusjwVer2App::setup()
{
	myImage = gl::Texture( loadImage( loadAsset( "USA01.PNG" ) ) );
	isLookingForClosest_ = false;

	xPos = -1;
	yPos = -1;
	
	growCalled = false;

	arrLen = 3000;
	censusArrLen = 5000;
	censusArrLen2010 = 5000;

	int counter = 0;
	int censusCounter = 0;
	int censusCounter2010 = 0;

	frameNumber = 0;

	e = new Entry[arrLen];
	c_ = new Census[censusArrLen];
	c_2010 = new Census[censusArrLen2010];

	ifstream in("../resources/Starbucks_2006.csv");

	
	bool matchFound = false;
	while(!in.eof())
	{
		if(counter == arrLen)
		{
			e = grow(e, arrLen);
			growCalled = true;
		}
		string identifier_;
		double x_;
		double y_;
		string line;
		getline(in,line,',');
		identifier_=line;
		in>>x_;
		getline(in,line,',');
		in>>y_;
		getline(in,line,'\r');
		
		
		e[counter].identifier=identifier_;
		e[counter].x=x_;
		e[counter].y=y_; 
		for(int i = 0; i < arrLen; i++)
		{
			if(abs(x_-e[i].x) <= 0.00001 && abs(x_-e[i].x!=0.00) || abs(y_-e[i].y) <=0.00001 && abs(y_-e[i].y)!=0.00){
				matchFound = true;
				break;
			}
			else
				matchFound = false;
		}
		if(!matchFound){
		counter++;
		if(growCalled){
			arrLen = arrLen*2;
			growCalled = false;
		}
		}
		else{}
	}	
	arrLen = counter+1;
	in.close();

	ifstream in2("../resources/Census_2000.csv");

	while(!in2.eof())
	{
		if(censusCounter == censusArrLen)
		{
			c_ = grow(c_, censusArrLen);
			growCalled = true;
		}
		int population_;
		double x_;
		double y_;
		string line;
		getline(in2,line,',');
		in2.get();
		getline(in2,line,',');
		in2.get();
		getline(in2,line,',');
		in2.get();
		getline(in2,line,',');
		in2>>population_;
		getline(in2,line,',');
		in2>>x_;
		getline(in2,line,',');
		in2>>y_;
		getline(in2,line,'\r');
		
		c_[censusCounter].population=population_;
		c_[censusCounter].x=x_;
		c_[censusCounter].y=y_; 
		censusCounter++;
		if(growCalled){
			censusArrLen = censusArrLen*2;
			growCalled = false;
		}
		else{}
	}	
	censusArrLen = censusCounter+1;
	in2.close();


	ifstream in3("../resources/Census_2010.csv");

	while(!in3.eof())
	{
		if(censusCounter2010 == censusArrLen2010)
		{
			c_2010 = grow(c_2010, censusArrLen2010);
			growCalled = true;
		}
		int population_;
		double x_;
		double y_;
		string line;
		getline(in3,line,',');
		in3.get();
		getline(in3,line,',');
		in3.get();
		getline(in3,line,',');
		in3.get();
		getline(in3,line,',');
		in3>>population_;
		getline(in3,line,',');
		in3>>x_;
		getline(in3,line,',');
		in3>>y_;
		getline(in3,line,'\r');
		
		c_2010[censusCounter2010].population=population_;
		c_2010[censusCounter2010].x=x_;
		c_2010[censusCounter2010].y=y_; 
		censusCounter2010++;
		if(growCalled){
			censusArrLen2010 = censusArrLen2010*2;
			growCalled = false;
		}
		else{}
	}	
	censusArrLen2010 = censusCounter2010+1;
	in2.close();


	//shuffle algorithm
	int j = 0;
	for( int i = 0; i < arrLen-1; i++)
	{
		Entry temp = e[i];
		j = (rand() % (arrLen-1));
		while(i==j)
		{
			j = (rand() % (arrLen-1));
		}
		e[i] = e[j];
		e[j] = temp;
		
		//console() << e[i].identifier << std::endl;
	}
	//end shuffle

	
	rs.build(e,arrLen);
	//closestStar = rs.getNearest(.2, .6);
	//console() <<"Your closest Starbucks is at: " << closestStar->identifier << std::endl;
}

void HW04_ruebusjwVer2App::shapeDrawer(float x_, float y_, int red, int green, int blue, bool isLookingForClosest)
{
	if(isLookingForClosest)
	{
		gl::color(Color8u(0,0,0));
		gl::drawSolidCircle( Vec2f( 800*x_, 600*(1-y_) ), 4.0f );
		gl::color(Color8u(0, 255, 255));
		gl::drawSolidCircle( Vec2f( 800*x_, 600*(1-y_) ), 3.0f );
		gl::color(1,1,1,-1);
		isLookingForClosest_ = false;
	}
	else
	{
		gl::color(Color8u(0,0,0));
		gl::drawSolidCircle( Vec2f( 800*x_, 600*(1-y_) ), 3.0f );
		gl::color(Color8u(red, green, blue));
		gl::drawSolidCircle( Vec2f( 800*x_, 600*(1-y_) ), 2.0f );
		gl::color(1,1,1,-1);
	}
}

void HW04_ruebusjwVer2App::mouseDown( MouseEvent event )
{
	skippedBucks = -1;
	xPos = event.getPos().x;
	yPos = event.getPos().y;
	Entry* nearestStarbucks = rs.getNearest(xPos/appWidth,1-(yPos/appHeight));
	for(int i = 0; i < arrLen;i++)
	{
		if(e[i].identifier==nearestStarbucks->identifier)
			skippedBucks = i;
	}
}

void HW04_ruebusjwVer2App::update()
{
	

}

void HW04_ruebusjwVer2App::draw()
{
	if(frameNumber == 0)
	{
		gl::draw( myImage, getWindowBounds() );
	}
	for(int i = 0; i<arrLen; i++)
	{
		if(i==skippedBucks)
		{
			isLookingForClosest_ = true;
		}

		shapeDrawer(e[i].x,e[i].y,255,0,0,isLookingForClosest_);
	}
}

CINDER_APP_BASIC( HW04_ruebusjwVer2App, RendererGl )
