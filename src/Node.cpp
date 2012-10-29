#include "Node.h"

Node::Node(){
	left_ = right_ = NULL;
	data = new Entry();
}

Node::Node(Entry e){
	left_ = right_ = NULL;
	data = new Entry();
}