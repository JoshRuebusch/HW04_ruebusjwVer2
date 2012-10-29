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

class node{
public:		

	node();
	node(Entry e);

	node* left_;
	node* right_;

	Entry* data;		
   }; 

class ruebusjwStarbucks : public Starbucks{
public:
	Entry* entArr;
	int arraySize;
	string fileName;
	Entry* closestStarbucks;

	Entry* theArray;

	node* newNode;

	ruebusjwStarbucks();
	void build(Entry* c, int n);
	//void createArray(string file, Entry* c, int n);
	//node* r;

	Entry* getNearest(double x, double y);
	//node* insert(Entry* e, node* r, bool isXlevel);
	//Entry* search(double keyX_, double keyY_, node* r, bool isXLevel);
};