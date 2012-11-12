#include "Starbucks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;
std::stringstream;


class Census{
public:
	int population;
	double x;
	double y;
};


class ruebusjwStarbucks : public Starbucks{
public:
	Entry* entArr;
	int arraySize;
	string fileName;
	Entry* closestStarbucks;

	Entry* theArray;

	ruebusjwStarbucks();
	void build(Entry* c, int n);

	Entry* getNearest(double x, double y);
};