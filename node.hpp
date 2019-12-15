//Node header file
#ifndef NODE_H
#define NODE_H
#include "enums.hpp"

template<class T> struct  RBTNode {
	T key;
	Color color;
	RBTNode<T> * left;
	RBTNode<T> * right;
	RBTNode<T> * parent;
	RBTNode(T k, Color c, RBTNode* p, RBTNode*l, RBTNode*r) :
		key(k), color(c), parent(p), left(l), right(r) { };
};

#endif