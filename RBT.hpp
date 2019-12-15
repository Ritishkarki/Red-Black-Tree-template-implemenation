#ifndef RBT_H
#define RBT_H

#include "node.hpp"
#include <iomanip>

template<class T> class  RBTree {
	public:
		RBTree();
		~RBTree();

		void insert(T key); // Insert node, key is the key value, external interface
		void remove(T key); // Delete the node of the key
		RBTNode<T>* search(T key);
		void print();
		void preOrder(); // Pre-order traversal Print red black tree
		void inOrder();  //Intermediate traversal
		void postOrder();// Post-order traversal		
		int checkBlackNodes(); // finding the black height of the tree
		
	private:
		void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);// left-handed
		void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);// right handed
		void insert(RBTNode<T>* &root, RBTNode<T>* node);// insert node, internal interface
		void InsertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
		void destory(RBTNode<T>* &node);
		void remove(RBTNode<T>*& root, RBTNode<T>*node);// Delete the node as KEY
		void removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>*parent);
		RBTNode<T>* search(RBTNode<T>*node, T key) const;
		void print(RBTNode<T>* node)const;
		void preOrder(RBTNode<T>* tree)const;
		void inOrder(RBTNode<T>* tree)const;
		void postOrder(RBTNode<T>* tree)const;
		int checkBlackNodes(RBTNode<T>* root)const;

	private:
		RBTNode<T>*root;
};

#endif