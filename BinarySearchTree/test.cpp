#include <iostream>
#include "BinarySearchTree.h"
#include "AvlTree.h"

/*
void printTree(Tree<int> tree)
{
	if(!tree)
	{
		return;
	}
		
	printTree(tree->leftTree);
	std::cout << tree->key << " ";	
	printTree(tree->rightTree);
}
*/
int main()
{
	BinarySearchTree<int> tree({2, 9, 8, 5, 3, 4, 10, 6, 7});
	tree.printTree();
	std::cout << std::endl;
	AvlTree<int> avlTree({3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9});
	avlTree.printTree();
	std::cout << std::endl;
	avlTree.delNode(9);
	avlTree.printTree();
	std::cout << std::endl;
	avlTree.delNode(8);
	avlTree.printTree();
	std::cout << std::endl;
	avlTree.delNode(10);
	avlTree.printTree();
	std::cout << std::endl;
	avlTree.delNode(11);
	avlTree.printTree();
	std::cout << std::endl;
	/*std::cout << std::endl;
	std::cout << "Min :" << tree.findMin()->key << std::endl;
	std::cout << "Max :" << tree.findMax()->key << std::endl;
	tree.insertNode(2);
	printTree(tree);
	std::cout << std::endl;
	tree.delNode(5);
	printTree(tree);
	std::cout << std::endl;
*/
	return 0;	
}
