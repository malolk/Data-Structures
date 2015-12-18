#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <initializer_list>

template <typename T> 
class TreeNode
{
public:
	T key;
	TreeNode *leftTree;
	TreeNode *rightTree;
	int hight = -1;	
};

template <typename T> using Tree = TreeNode<T> *;	
template <typename T> using Position = TreeNode<T> *;	
template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() = default;
	BinarySearchTree(std::initializer_list<T> l)
	{
		for(const auto &key : l)
			insertNode(key);				
	}
//operations below
	Tree<T> makeEmpty();	
	Position<T> find(T x);
	Position<T> findMin();
	Position<T> findMax();
	virtual void insertNode(T x);
	virtual void delNode(T x);
	T retrieve(Position<T> p);
	int getDepth(Tree<T> tree);
	Tree<T> rootOfTree() 
	{
		return root;	
	}
	void printTree();
protected:
	Tree<T> root = nullptr;
};

template <typename T>
int BinarySearchTree<T>::getDepth(Tree<T> tree)
{
	//!!!depth begins at zero
	int leftDepth = -1, rightDepth = -1;
	int maxDepth = -1;
	if(!tree)
		return -1;
	leftDepth = getDepth(tree->leftTree);
	rightDepth = getDepth(tree->rightTree);
	maxDepth = leftDepth > rightDepth ? leftDepth : rightDepth;				
	return maxDepth + 1;
}

template <typename T>
Tree<T> empty(Tree<T> tree)
{
	if(tree != nullptr)	

	{
		empty(tree->leftTree);		
		empty(tree->rightTree);
		delete tree;
		tree = nullptr;		
	}
	return nullptr;
}
template <typename T>
Tree<T> BinarySearchTree<T>::makeEmpty()
{
	return empty(root);
}

template <typename T>
Position<T> findItem(T elem, Tree<T> tree)
{
	if(!tree)
		return nullptr;
	if(elem < tree->key)
		return findItem(elem, tree->leftTree);
	else if(elem > tree->key)
		return findItem(elem, tree->rightTree);
	else
		return tree;			
}

template <typename T>
Position<T> BinarySearchTree<T>::find(T elem)
{
	return findItem<T>(elem, root);	
}

template <typename T>
Tree<T> findMinDriver(Tree<T> tree)
{
	if(tree && tree->leftTree)
		return findMinDriver(tree->leftTree);
	else
		return tree;
}

template <typename T>
Position<T> BinarySearchTree<T>::findMin()
{
	return findMinDriver(root);
}

template <typename T>
Position<T> BinarySearchTree<T>::findMax()
{
	Tree<T> t = root;
	while(t)
	{
		if(t->rightTree)
			t = t->rightTree;	
		else
			break;	
	}
	return t;	
}


template <typename T>
Tree<T> insertDriver(T elem, Tree<T> tree)
{
	if(!tree)
	{
		tree = new TreeNode<T>();
		if(!tree)
			std::cerr << "insertDriver: out of space!\n";
		else
		{
			tree->key = elem;
			tree->leftTree = tree->rightTree = nullptr;
		}
	}	
	else if(elem < tree->key)
		tree->leftTree = insertDriver(elem, tree->leftTree);
	else if(elem > tree->key)
		tree->rightTree = insertDriver(elem, tree->rightTree);
	
	return tree;
}

template <typename T>
void BinarySearchTree<T>::insertNode( T elem)
{
	root = insertDriver(elem, root);	
}

template <typename T>
Tree<T> delNodeDriver(T elem, Tree<T> tree)
{
	if(!tree)
		return tree;
	else if(elem < tree->key)
		tree->leftTree = delNodeDriver(elem, tree->leftTree);
	else if(elem > tree->key)	
		tree->rightTree = delNodeDriver(elem, tree->rightTree);
	else
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
	return tree;
}

template <typename T>
void BinarySearchTree<T>::delNode( T elem)
{
	root = delNodeDriver(elem, root);		
}

//assumed that p has been checked
template <typename T>
T BinarySearchTree<T>::retrieve(Position<T> p)
{
	return p->key;	
}

template <typename T>
void printTreeOneLevel(Tree<T> tree, int level)
{
	if(!tree)
		return;
	if(level == 0)
		std::cout << " " << tree->key << " ";
	printTreeOneLevel(tree->leftTree, level-1); 			
	printTreeOneLevel(tree->rightTree, level-1); 	
}

//here the depth begins at zero
template <typename T>
void BinarySearchTree<T>::printTree()
{
	int hight = getDepth(root);
	for(int level = 0; level < hight+1; ++level)
	{
		printTreeOneLevel(root, level);
		std::cout << std::endl;	
	}			
}
#endif

