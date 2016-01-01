#ifndef HASHSEP_H
#define HASHSEP_H

#include <string>
#include <iostream>
#include <stdexcept>

class ListNode
{
public:
	std::string key;
	ListNode *next;	
};

using Position = ListNode *;
using List = ListNode *;

class HashSepTable
{

friend void printHashTable(const HashSepTable &hashTble);
public:
	HashSepTable() = default;
	HashSepTable(int size);
	HashSepTable(const HashSepTable &);
	HashSepTable& operator=(const HashSepTable &);
	void destroyTable();
	Position find(const std::string &key);
	void insert(const std::string &key);
	void delNode(const std::string &key);
	std::string retrive(Position p);
	unsigned hashFunc(const std::string &str);
	~HashSepTable()
	{
		destroyTable();	
	}

private:
	bool isPrime(int number);
	int tableSize = 10;
	List *sepList = nullptr;	
};

void printHashTable(const HashSepTable &hashTble)
{
	if(hashTble.sepList == nullptr || hashTble.tableSize == 0)
	{
		std::cerr << "empty table\n";
		return;	
	}		
	for(int index = 0; index < hashTble.tableSize; ++index)
	{
		auto lst = *(hashTble.sepList + index);
		std::cout << index << ": ";
		while(lst != nullptr)
		{
			std::cout << lst->key;
			lst = lst->next;
			std::cout << " ";	
		}	
		std::cout << "\n";
	}	
}

inline 
unsigned HashSepTable::hashFunc(const std::string &str)
{
	unsigned int hashVal = 0;
	for(const auto &chr: str)	
		hashVal = (hashVal << 5) + chr;
	return hashVal % tableSize;
}

inline
bool HashSepTable::isPrime(int number)
{
	if(number <= 1)
		return false;
	for(int num = 2; num*num <= number; ++num)
	{
		if(number % num == 0)
			return false;	
	}
	return true;				
}

HashSepTable::HashSepTable(int size)
{
	if(size <= 1)
	{
		std::cerr << "invalid size\n";
		std::runtime_error("invalid size");
	}	
	while(1)
	{
		if(isPrime(size))
			break;
		++size;	
	}
	tableSize = size;
	sepList = new List[tableSize];
	if(sepList == nullptr)
		std::runtime_error("out of space!!!");
	for(int i = 0; i < tableSize; ++i)
		sepList[i] = nullptr;
}

HashSepTable::HashSepTable(const HashSepTable &rhs)
{
	tableSize = rhs.tableSize;
	sepList = new List[tableSize];
	if(sepList == nullptr)
		std::runtime_error("out of space!!!");
	for(int i = 0; i < tableSize; ++i)
		sepList[i] = nullptr;
	for(int index = 0; index < tableSize; ++index)
	{
		auto leftPtr = *(sepList + index);	
		auto rightPtr = *(rhs.sepList + index);
		while(rightPtr != nullptr)
		{
			auto node = new ListNode();
			if(node == nullptr)
				std::runtime_error("out of space");
			if(leftPtr == nullptr)
				leftPtr = *(sepList + index) = node;
			else
				leftPtr->next = node;

			node->key = rightPtr->key;
			node->next = nullptr;
			rightPtr = rightPtr->next;
		}	
	}
}

HashSepTable& HashSepTable::operator=(const HashSepTable &rhs)
{
	if(sepList != rhs.sepList)
	{
		destroyTable();
		tableSize = rhs.tableSize;
		sepList = new List[tableSize];
		if(sepList == nullptr)
			std::runtime_error("out of space!!!");
		for(int i = 0; i < tableSize; ++i)
			sepList[i] = nullptr;
		for(int index = 0; index < tableSize; ++index)
		{
			auto leftPtr = *(sepList + index);	
			auto rightPtr = *(rhs.sepList + index);
			while(rightPtr != nullptr)
			{
				auto node = new ListNode();
				if(node == nullptr)
					std::runtime_error("out of space");
				if(leftPtr == nullptr)
					leftPtr = *(sepList + index) = node;
				else
					leftPtr->next = node;
				node->key = rightPtr->key;
				node->next = nullptr;
				rightPtr = rightPtr->next;
			}	
		}			
	}	

	return *this;
}

void HashSepTable::insert(const std::string &elem)
{
	unsigned index = hashFunc(elem);
	auto node = new ListNode();
	if(node == nullptr)
		std::runtime_error("out of space");
	node->key = elem;
	node->next = sepList[index];
	sepList[index] = node;
}

Position HashSepTable::find(const std::string &elem)
{
	unsigned index = hashFunc(elem);
	auto lst = sepList[index];
	while(lst != nullptr && lst->key != elem)
		lst = lst->next;
	return lst;
}

void HashSepTable::delNode(const std::string &elem)
{
	unsigned index = hashFunc(elem);
	auto prevElem = sepList[index];
	if(prevElem == nullptr)
		return;
	if(prevElem->key == elem)
	{
		sepList[index] = prevElem->next;
		delete prevElem;
		return;	
	}
	while(prevElem->next && prevElem->next->key != elem)
		prevElem = prevElem->next;
	if(prevElem->next)
	{
		auto tmp = prevElem->next;
		prevElem->next = tmp->next;
		delete tmp;		
	}
}

void HashSepTable::destroyTable()
{
	List curLst = nullptr;
	List tmpLst = nullptr;
	for(int index = 0; index < tableSize; ++index)
	{
		curLst = sepList[index];
		while(curLst != nullptr)
		{
			tmpLst = curLst;
			curLst = curLst->next;
			delete tmpLst;			
		}	
		sepList[index] = nullptr;
	}	
	delete [] sepList;
}

std::string HashSepTable::retrive(Position p)
{
	if(p == nullptr)
		std::runtime_error("invalide position");	
	return p->key;
}



#endif

