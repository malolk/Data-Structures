#ifndef HEAPS_LEFTISTHEAPS_H_
#define HEAPS_LEFTISTHEAPS_H_

#include <cstdlib>

template <class T>
class Node
{
public:
	T elem;
	Node *left;
	Node *right;
	int nullLength; 	
};

template <class T>
class LeftistHeaps
{
public:
	LeftistHeaps(): root(nullptr) {} 
	LeftistHeaps(T elem)
	{
		root = (Node<T>* )std::malloc(sizeof(Node<T>));
		root->elem = elem;
		root->left = root->right = nullptr;
		root->nullLength = 0;	
	}
	int isEmpty() { return root == nullptr; }
	void merge(LeftistHeaps &h); 
	void insert(T elem);
	T delTop();
	T findTop();

	~LeftistHeaps();
private:
	Node<T>* mergeDriver(Node<T>* tree1, Node<T>* tree2);
	Node<T>* mergeRecursive(Node<T>* tree1, Node<T>* tree2);
	Node<T>* insertDriver(Node<T>* tree1, Node<T>* tree2);
	void destroyDriver(Node<T>*);
	Node<T> *root;		
};

template<class T>
Node<T>* LeftistHeaps<T>::mergeRecursive(Node<T>* tree1, Node<T>* tree2)
{
	if(tree1 == nullptr)
		return tree2;
	if(tree2 == nullptr)
		return tree1;
	if(tree1->elem < tree2->elem)
		return mergeDriver(tree1, tree2);
	else
		return mergeDriver(tree2, tree1);	
}
template<class T>
Node<T>* LeftistHeaps<T>::mergeDriver(Node<T>* tree1, Node<T>* tree2)
{
	Node<T> *tmpPtr = nullptr;
	if(tree1->left == nullptr)
		tree1->left = tree2;
	else
	{
		tree1->right = mergeRecursive(tree1->right, tree2);
		if(tree1->left->nullLength < tree1->right->nullLength)
		{
			tmpPtr = tree1->right;
			tree1->right = tree1->left;
			tree1->left = tmpPtr;	
		}
		tree1->nullLength = tree1->right->nullLength + 1;
	}

	return tree1;
}

template<class T>	
void LeftistHeaps<T>::merge(LeftistHeaps<T> &h)
{
	this->root = mergeRecursive(this->root, h.root);	
	h.root = nullptr;
} 

template<class T>
void LeftistHeaps<T>::insert(T elem)
{
	LeftistHeaps<T> newTree(elem);
	merge(newTree);
}

template<class T>
T  LeftistHeaps<T>::delTop()
{
	T retElem;
	Node<T> *tmp = root;
	retElem = root->elem;
	root = mergeRecursive(root->left, root->right);
	free(tmp);
	return retElem;
}

template<class T>
T  LeftistHeaps<T>::findTop()
{
	return root->elem;	
}

template<class T>
void LeftistHeaps<T>::destroyDriver(Node<T>* tree)
{
	if(tree != nullptr)
	{
		destroyDriver(tree->left);	
		destroyDriver(tree->right);
		free(tree);	
	}	
}

template<class T>
LeftistHeaps<T>::~LeftistHeaps()
{
	destroyDriver(root);
	root = nullptr;
}
#endif    //HEAPS_LEFTISTHEAPS_H_
