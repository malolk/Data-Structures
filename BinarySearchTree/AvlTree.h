#ifndef AVLTREE_H
#define AVLTREE_H

#include "BinarySearchTree.h"
#include <stdexcept>

template <typename T>
class AvlTree: public BinarySearchTree<T>
{
public:
	AvlTree() = default;
	AvlTree(std::initializer_list<T> l)
	{
		for(const auto &key : l)
			insertNode(key);	
	}
	void insertNode(T x) override;
	void delNode(T x) override;
private:
	Tree<T> insertNodeDriver(T x, Tree<T> tree);
	Tree<T> delNodeDriver(T x, Tree<T> tree);
	int getHight(Tree<T> node);	
	Tree<T> singleRotateWithLeft(Tree<T> tree);
	Tree<T> singleRotateWithRight(Tree<T> tree);
	Tree<T> doubleRotateRightLeft(Tree<T> tree);
	Tree<T> doubleRotateLeftRight(Tree<T> tree);
};

template <typename T>
int AvlTree<T>::getHight(Tree<T> node)
{
	if(!node)
		return -1;
	return node->hight;	
}

template <typename T>
int max(T left, T right)
{
	return left > right ? left : right;
}

template <typename T>
Tree<T> AvlTree<T>::singleRotateWithLeft(Tree<T> tree)
{
	auto leftT = tree->leftTree;
	auto rightTreeOfChild = leftT->rightTree;
	leftT->rightTree = tree;
	tree->leftTree = rightTreeOfChild;
	tree->hight = max(getHight(tree->leftTree), getHight(tree->rightTree)) + 1;
	leftT->hight = max(getHight(leftT->leftTree), getHight(leftT->rightTree)) + 1;
	
	return leftT;
}

template <typename T>
Tree<T> AvlTree<T>::singleRotateWithRight(Tree<T> tree)
{
	auto rightT = tree->rightTree;
	auto leftTreeOfChild = rightT->leftTree;
	rightT->leftTree = tree;
	tree->rightTree = leftTreeOfChild;
	tree->hight = max(getHight(tree->leftTree), getHight(tree->rightTree)) + 1;
	rightT->hight = max(getHight(rightT->leftTree), getHight(rightT->rightTree)) + 1;
	return rightT;
}

template <typename T>
Tree<T> AvlTree<T>::doubleRotateLeftRight(Tree<T> tree)
{
	tree->leftTree = singleRotateWithRight(tree->leftTree);
	return singleRotateWithLeft(tree);
}

template <typename T>
Tree<T> AvlTree<T>::doubleRotateRightLeft(Tree<T> tree)
{
	tree->rightTree = singleRotateWithLeft(tree->rightTree);
	return singleRotateWithRight(tree);
}

template <typename T>
Tree<T> AvlTree<T>::insertNodeDriver(T x, Tree<T> tree)
{
	if(!tree)
	{
		tree = new TreeNode<T>();
		if(!tree)
		{
			std::runtime_error("out of space!!!");				
		}	
		else
		{
			tree->key = x;
			tree->hight = 0;
			tree->leftTree = tree->rightTree = nullptr;	
		}
	}	
	else if(x < tree->key)
	{
		tree->leftTree = insertNodeDriver(x, tree->leftTree);
		if(getHight(tree->leftTree) - getHight(tree->rightTree) == 2)
			if(x < tree->leftTree->key)
				tree = singleRotateWithLeft(tree);
			else
				tree = doubleRotateLeftRight(tree);					
	}	
	else if(x > tree->key)
	{
		tree->rightTree = insertNodeDriver(x, tree->rightTree);
		if(getHight(tree->rightTree) - getHight(tree->leftTree) == 2)
			if(x > tree->rightTree->key)
				tree = singleRotateWithRight(tree);
			else
				tree = doubleRotateRightLeft(tree);					
	}	

	auto leftH = getHight(tree->leftTree);
	auto rightH = getHight(tree->rightTree);
	tree->hight = (leftH > rightH ? leftH + 1 : rightH + 1);
	return tree;
}

template <typename T>
void AvlTree<T>::insertNode(T x)
{
	this->root = insertNodeDriver(x, this->root);	
}

template <typename T>
Tree<T> AvlTree<T>::delNodeDriver(T x, Tree<T> tree)
{
	if(!tree)
		return tree;	
	else if(x < tree->key)
		tree->leftTree = delNodeDriver(x, tree->leftTree);	
	else if(x > tree->key)
		tree->rightTree = delNodeDriver(x, tree->rightTree);	 else
	{
		if(tree->leftTree && tree->rightTree)
		{
			auto minRightNode = findMinDriver(tree->rightTree);
			tree->key = minRightNode->key;
			tree->rightTree = delNodeDriver(tree->key, tree->rightTree);	
		}	
		else
		{
			auto tmpNode = tree;
			if(!tree->leftTree)
				tree = tree->rightTree;
			else 
				tree = tree->leftTree;
			delete tmpNode;

		}
	}
	//one node case
	if(!tree)
		return nullptr;
	tree->hight = max(getHight(tree->leftTree), getHight(tree->rightTree)) + 1;
	int diffHight = getHight(tree->leftTree) - getHight(tree->rightTree);
	
	if(diffHight > 1)
	{
		if(getHight(tree->leftTree->leftTree) > getHight(tree->leftTree->rightTree))
			tree = singleRotateWithLeft(tree);
		else
			tree = doubleRotateLeftRight(tree);				
	}	
	else if(diffHight < -1)
	{
		if(getHight(tree->rightTree->rightTree) > getHight(tree->rightTree->leftTree))
			tree = singleRotateWithRight(tree);
		else
			tree = doubleRotateRightLeft(tree);				
	}

	return tree;
}

template <typename T>
void AvlTree<T>::delNode(T x)
{
	this->root = delNodeDriver(x, this->root);	
}

#endif

