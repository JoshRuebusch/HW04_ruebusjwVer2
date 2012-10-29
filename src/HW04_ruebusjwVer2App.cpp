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
	Entry* e;
	Entry* closestStar;
	int arrLen;
	bool growCalled;
	node* root;

};

Entry* grow(Entry* smallArray, int arrayLen){
	Entry* newArray = new Entry[arrayLen*2];
	for(int i = 0; i < arrayLen; i++)
	{
		newArray[i] = smallArray[i];
	}
	
	return newArray;
}

void HW04_ruebusjwVer2App::setup()
{
	growCalled = false;
	arrLen = 3000;
	int counter = 0;
	e = new Entry[arrLen];
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

	ruebusjwStarbucks rs;
	rs.build(e,arrLen);
	closestStar = rs.getNearest(.2, .6);
	console() <<"Your closest Starbucks is at: " << closestStar->identifier << std::endl;
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
	gl::clear( Color( 1, 1, 1 ) ); 
}

CINDER_APP_BASIC( HW04_ruebusjwVer2App, RendererGl )
