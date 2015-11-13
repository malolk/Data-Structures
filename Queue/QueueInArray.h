#ifndef QUEUEINARRAY_H
#define QUEUEINARRAY_H


#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <vector>

template <typename> class QueueInArray;
template <typename T>
std::ostream& operator<<(std::ostream& out, QueueInArray<T> &q);
template <typename T>
class QueueInArray
{
friend std::ostream& operator<<<T>(std::ostream &out, QueueInArray &q);
public:
	QueueInArray(std::size_t sz = 10);
	QueueInArray(std::initializer_list<T> l);

	bool isEmpty();
	bool isFull();
	void Enqueue(T elem);
	void Dequeue();
	std::size_t curRear() { return rear; }
	std::size_t curFront() { return front; }
	T frontElem();
	void makeEmpty();
private:
	std::vector<T> array;
	std::size_t cap;
	std::size_t size;
	std::size_t front;
	std::size_t rear;	
};

template <typename T>
std::ostream& operator<<(std::ostream& out, QueueInArray<T> &q)
{
	for(std::size_t index = 0; index < q.size; ++index)
		out << q.array[(q.front + index)%q.cap] << (index + 1 != q.size ? "->" : "\n");
	return out;
}
template <typename T>
QueueInArray<T>::QueueInArray(std::size_t sz)
{
	cap = sz;
	array = std::vector<T>(sz);
	size = 0;
	front = 1;
	rear = 0; 	
}

template <typename T>
bool QueueInArray<T>::isEmpty()
{
	return size == 0;	
}

template <typename T>
bool QueueInArray<T>::isFull()
{
	return size == cap;	
}

template <typename T>
void QueueInArray<T>::Enqueue(T elem)
{
	if(isFull())
		return;
	++rear;
	++size;
	rear = rear%cap;
	array[rear]	= elem;
}

template <typename T>
void QueueInArray<T>::Dequeue()
{
	if(isEmpty())
		return;
	++front;
	--size;
	front %= cap;		
}

template <typename T>
T QueueInArray<T>::frontElem()
{
	if(isEmpty())
	{
		std::cerr << "Empty Queue\n";
		return T();	
	}	
	return array[front];
}
template <typename T>
QueueInArray<T>::QueueInArray(std::initializer_list<T> l)
{
	cap = l.size();
	array = std::vector<T>(cap);
	size = 0;
	front = 1;
	rear = 0;
	for(auto it : l)
		Enqueue(it);		
}

template <typename T>
void QueueInArray<T>::makeEmpty()
{
	while(!isEmpty())
		Dequeue();			
}



#endif

