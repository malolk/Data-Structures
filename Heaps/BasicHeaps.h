#ifndef HEAPS_BASICHEAPS_H_
#define HEAPS_BASICHEAPS_H_

#include <vector>
#include <limits>

template <class T>
class BasicHeaps
{
	public:
	BasicHeaps(int sz = 10, int flag = 0): orderFlag(flag) //default or resize
	{
		size = 0;
		capacity = sz;
		elemVec.resize(capacity + 1, T()); //the first element won't be used		
		elemVec[0] = (orderFlag == 0 ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max());
	}
	void insert(T elem);
	T delTop();
	T findTop();
	int isEmpty() 
	{
		return (size == 0);	
	}
	int isFull()
	{
		return (size == capacity);	
	}

	private:
	int	capacity;
	int	size;
	const int orderFlag;
	std::vector<T> elemVec;		
};

template <class T>
inline bool compare(T parent, T child, int flag)
{
	if(flag == 0) 
		return (parent > 	child);
	else
		return (parent <    child);
}


template <class T>
void BasicHeaps<T>::insert(T elem)
{
	int i;
	if(isFull())
	{
		elemVec.resize(2*capacity+1, T());
		capacity *= 2;	
	}
	for(i = ++size; i > 0; i /= 2)
	{
		if(compare(elemVec[i / 2], elem, orderFlag))
				elemVec[i] = elemVec[i / 2];
		else
			break;
	}
	elemVec[i] = elem;
}

template <class T>
T BasicHeaps<T>::delTop()
{
	int i, child;
	T minElem, relocator;
	if(isEmpty())
		return elemVec[0];	
	minElem = elemVec[1];
	relocator = elemVec[size--];
	
	for(i = 1; i*2 <= size; i = child)
	{
		child = i*2;
		if(child != size && compare(elemVec[child], elemVec[child+1], orderFlag))
			++child;
		if(compare(relocator, elemVec[child], orderFlag))
			elemVec[i] = elemVec[child];
		else
			break;
	}
	elemVec[i] = relocator;
	return minElem;
}

template <class T>
inline T BasicHeaps<T>::findTop()
{
	return elemVec[1];
}

#endif //HEAPS_BASICHEAPS_H_
