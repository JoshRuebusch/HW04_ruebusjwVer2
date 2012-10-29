#include "ruebusjwStarbucks.h"

node::node(){
	left_ = right_ = NULL;
	data = new Entry();
}

node::node(Entry e){
	left_ = right_ = NULL;
	data = new Entry();
}

void ruebusjwStarbucks::build(Entry* c, int n){

	bool isXLevel = true;
	arraySize = n;
	fileName = "Starbucks_2006.csv";
	createArray(fileName, c, n);
}

Entry* grow(Entry* smallArray, int arrayLen){
	Entry* newArray = new Entry[arrayLen*2];
	for(int i = 0; i < arrayLen; i++)
	{
		newArray[i] = smallArray[i];
	}
	arrayLen = arrayLen*2;
	
	return newArray;
}

void ruebusjwStarbucks::createArray(string file, Entry* c, int n){
	ifstream in(file);
	int counter = 0;
	bool matchFound = false;
	while(!in.eof())
	{
		if(counter == arraySize)
		{
			entArr = grow(entArr, arraySize);
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
		
		
		entArr[counter].identifier=identifier_;
		entArr[counter].x=x_;
		entArr[counter].y=y_; 
		for(int i = 0; i < arraySize; i++)
		{
			if(abs(x_-entArr[i].x) <= 0.00001 && abs(x_-entArr[i].x!=0.00) || abs(y_-entArr[i].y) <=0.00001 && abs(y_-entArr[i].y)!=0.00){
				matchFound = true;
				break;
			}
			else
				matchFound = false;
		}
		if(!matchFound)
		counter++;
		else{}
		
	}
	cout << entArr[counter-1].identifier<<flush;
}




