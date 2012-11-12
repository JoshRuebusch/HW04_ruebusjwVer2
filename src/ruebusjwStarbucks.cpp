#include "ruebusjwStarbucks.h"

ruebusjwStarbucks::ruebusjwStarbucks(){
	arraySize = 0;
	theArray = NULL;
}

void ruebusjwStarbucks::build(Entry* c, int n){
	arraySize = n;
	theArray = new Entry[n];
	
	for( int i = 0; i < n-1; i++)
	{
		theArray[i] = c[i];
	}
}

Entry* ruebusjwStarbucks::getNearest(double x_, double y_){
	Entry* curPosition = new Entry();
	curPosition->identifier = "";
	curPosition->x = x_;
	curPosition->y = y_;
	double smallestDist = 1.1;
	double curDist = 0;
	int location = 0;
	
	for(int i = 0; i < arraySize - 1; i++){
		curDist = sqrt((x_-theArray[i].x)*(x_-theArray[i].x)+(y_-theArray[i].y)*(y_-theArray[i].y));
		if(curDist < smallestDist)
		{
			smallestDist = curDist;
			location = i;
		}
	}
	curPosition = &theArray[location];

	return curPosition;
}



