#include "ruebusjwStarbucks.h"

node::node(){
	left_ = right_ = NULL;
	data = NULL;
}

node::node(Entry e){
	left_ = right_ = NULL;
	*data = e;
	data = new Entry();
}

ruebusjwStarbucks::ruebusjwStarbucks(){}

node* insert(Entry e, node* r, bool isXlevel){
	//case 1: no node found
	if(r->data==NULL)
		return new node(e);
	//case 2: same node...this one shouldn't happen, I don't think
	/*if(r->data->x == e.x && r->data->y == e.y)
		return r;*/
	//case 3 on x level, key's x < node's x
	if(e.x < r->data->x && isXlevel)
		r->left_=insert(e,r->left_,!isXlevel);
	//case 4 on x level, key's x > node's x
	else
		r->right_=insert(e,r->right_,!isXlevel);
	//case 5 not on x level, key's y < node's y
	if(e.y < r->data->y && !isXlevel)
		r->left_=insert(e,r->left_,!isXlevel);
	//case 6 not on x level, key's y > node's y
	else
		r->right_=insert(e,r->right_,!isXlevel);

}

void ruebusjwStarbucks::build(Entry* c, int n){
	bool isXLevel = true;
	arraySize = n;
	theArray = new Entry[n];
	
	for( int i = 0; i < n-1; i++)
	{
		theArray[i] = c[i];
	}
}

Entry* ruebusjwStarbucks::getNearest(double x_, double y_){
	Entry* curPosition = new Entry();
	curPosition->identifier = "Your position";
	curPosition->x = x_;
	curPosition->y = y_;
	double smallestDist = 1.1;
	double curDist = 0;
	for(int i = 0; i < arraySize - 1; i++){
		curDist = sqrt((x_-theArray[i].x)*(x_-theArray[i].x)+(y_-theArray[i].y)*(y_-theArray[i].y));
		if(curDist < smallestDist)
			smallestDist = curDist;
	}
	for(int i = 0; i < arraySize - 1; i++){
		curDist = sqrt((x_-theArray[i].x)*(x_-theArray[i].x)+(y_-theArray[i].y)*(y_-theArray[i].y));
		if(curDist == smallestDist)
			curPosition = &theArray[i];
	}

	
	return curPosition;
}

Entry* search(double keyX_, double keyY_, node* r, bool isXLevel){
	if(r==NULL) return NULL;
	if(keyX_ == r->data->x && keyY_ == r->data->y)
		return r->data;
	if(keyX_ < r->data->x && isXLevel)
		Entry* best_fit = search(keyX_, keyY_, r->left_,!isXLevel);
	else
		Entry* best_fit = search(keyX_, keyY_, r->right_,!isXLevel);

	if(keyY_ < r->data->y && !isXLevel)
		Entry* best_fit = search(keyX_, keyY_, r->left_,!isXLevel);
	else
		Entry* best_fit = search(keyX_, keyY_, r->right_,!isXLevel);
}



