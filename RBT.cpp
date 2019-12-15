#include "RBT.hpp"
#include <iostream>
using namespace std;

template<class T>		//Constructor
RBTree<T>::RBTree() :root(NULL) {
	root = nullptr;
}

template<class T>		//Destructor
RBTree<T>::~RBTree() {
	destory(root);
}

template<class T>		//Left
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x) {
	RBTNode<T>*y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};

template<class T>		//right spin
void RBTree<T>::rightRotate(RBTNode<T>*&root, RBTNode<T>*y) {
	RBTNode<T>*x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class T>		//insert
void RBTree<T>::insert(T key)
{
	RBTNode<T>*z = new RBTNode<T>(key, RED, NULL, NULL, NULL);
	insert(root, z);
};

template<class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *x = root;
	RBTNode<T> *y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->key >= x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if(y!=NULL)
	{
		if (node->key >= y->key)
			y->right = node;
		else
			y->left = node;
	}
	else 
		root = node;
	node->color = RED;
	InsertFixUp(root, node);
};

template<class T>
void RBTree<T>::InsertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>*parent;
	parent = node->parent;
	while (node != RBTree::root  && parent->color == RED)
	{
		RBTNode<T>*gparent = parent->parent;
		if (gparent->left == parent)
		{
			RBTNode<T>*uncle = gparent->right;
			if (uncle != NULL && uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = RED;
				parent->color = BLACK;
				break;
			}
		}
		else
		{
			RBTNode<T>*uncle = gparent->left;
			if (uncle != NULL && uncle->color == RED)
			{
				gparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = BLACK;
				gparent->color = RED;
				break;
			}
		}
	}
	root->color = BLACK;
}

template<class T>
//Destroy the red black tree
void RBTree<T>::destory(RBTNode<T>* &node) 
{
	if (node == NULL)
		return;
	destory(node->left);
	destory(node->right);
	delete node;
	node = nullptr;
}

template<class T>
void RBTree<T>::remove(T key) 
{
	RBTNode<T>*deletenode = search(root,key);
	if (deletenode != NULL){
		remove(root, deletenode);
	}
}

template<class T>
void RBTree<T>::remove(RBTNode<T>*&root, RBTNode<T>*node)
{
	RBTNode<T> *child, *parent;
	Color color;
	T key = node -> key;
	//The node left and right of the deleted node is not empty (not the leaf node)
	if (node->left != NULL && node->right != NULL)     
	{
		RBTNode<T> *replace = node;
		// Find the successor node (the lowest node of the right subtree of the current node)
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		//The deleted node is not the root node.
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		//root node situation
		else
			root = replace;
		//child is the right node of the replacement node, which is the node that needs subsequent adjustment.
		//Because replace is a successor node, it is impossible for him to have a left child.
		//The same reason that the precursor node cannot have the right child node
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		
		// The node is replaced by the parent node of the repalce
		if (parent == node)
			parent = replace;
		else
		{
			//Children's node exists
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		cout << key << " deleted from Red Black Tree." << endl;
		return;
	}
	// When the deleted node has only the left (right) node is empty, find the child node of the deleted node
	if (node->left != NULL)    
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child) 
	{
		child->parent = parent;
	}
	//The deleted node is not the root node
	if (parent)     
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	//The deleted node is the root node
	else
		RBTree::root = child;		

	if (color == BLACK)
	{
		removeFixUp(root, child, parent);
	}
	delete node;
	cout << key << " deleted from Red Black Tree." << endl;
}

template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node,RBTNode<T>*parent)
{
	RBTNode<T>*othernode;
	while ((!node) || node->color == BLACK && node != RBTree::root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == RED)
			{
				othernode->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == BLACK)
				{
					othernode->left->color=BLACK;
					othernode->color = RED;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = BLACK;
				othernode->right->color = BLACK;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == RED)
			{
				othernode->color = BLACK;
				parent->color = RED;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == BLACK) && (!othernode->right || othernode->right->color == BLACK))
			{
				othernode->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == BLACK)
				{
					othernode->right->color = BLACK;
					othernode->color = RED;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = BLACK;
				othernode->left->color = BLACK;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = BLACK;
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key) 
{
	return search(root, key);
}

template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>*node, T key) const
{
	try {
      	if (node == NULL || node->key == key){
			  if (node == NULL) std::cout << std::endl << "Node not found" << std::endl << std::endl ;
			return node;
		}
		else
			if (key >= node->key)
				return search(node->right, key);
			else
				return search(node->left, key);
	} catch (int n) {
		throw "Element not found";
	}
}

template<class T>		// Output binary tree details
void RBTree<T>::print() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		print(root);
}

template<class T>
void RBTree<T>::print(RBTNode<T>* node)const {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		cout << node->key << "(" << node->color << ") is root" << endl;
	else if(node->parent->left==node)
	{
		cout << node->key << "(" << node->color << ") is "<<node->parent->key<<"'s "<<"left child" << endl;
	}
	else
	{
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "right child" << endl;
	}
	print(node->left);
	print(node->right);
}

template<class T>		// Pre-order traversal RB tree
void RBTree<T>::preOrder() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		preOrder(root);
};

template<class T>		 
void RBTree<T>::preOrder(RBTNode<T>* tree)const {
		if (tree != NULL) {
			cout << tree->key << " ";
			preOrder(tree->left);
			preOrder(tree->right);
		}
	}


template<class T>		// Traverse RB tree
void RBTree<T>::inOrder() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		inOrder(root);
};

template<class T>		 
void RBTree<T>::inOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}

template<class T>      // Traverse RB tree
void RBTree<T>::postOrder() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		postOrder(root);
};

template<class T>		
void RBTree<T>::postOrder(RBTNode<T>* tree)const {
	if (tree != NULL) {
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}

template<class T>      // Traverse RB tree and find the black height
int RBTree<T>::checkBlackNodes() {
	return checkBlackNodes(root);
};

template<class T>	// recursive function to check the height of RB tree
int RBTree<T>::checkBlackNodes(RBTNode<T>* root)const {
	if (root == NULL)   
		return 1;    
	int leftBlackHeight = checkBlackNodes(root->left);
	if (leftBlackHeight == 0)
		return leftBlackHeight;
	int rightBlackHeight = checkBlackNodes(root->right);
	if (rightBlackHeight == 0)
		return rightBlackHeight;
	if (leftBlackHeight != rightBlackHeight){
		return 0;
	} else{
		return leftBlackHeight + (root -> color == BLACK ? 1 : 0);
	}
}