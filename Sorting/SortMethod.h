#ifndef SORTING_SORTINGMETHOD_H_
#define SORTING_SORTINGMETHOD_H_

#include <vector>
#include <cstdlib>
#include <iostream>

namespace
{

	using namespace std;

	template<class T>
		class SortingMethod
		{
			public:
				void insertionSort(vector<T> &input, size_t num);	
				void bubbleSort(vector<T> &input, size_t num);	
				void shellSort(vector<T> &input, size_t num);	
				void heapSort(vector<T> &input, size_t num);	
				void mergeSort(vector<T> &input, size_t num);
				void quickSort(vector<T> &input, size_t num);
				void quickSelect(vector<T> &input, size_t num, size_t k);
		};


	template<class T>
		void SortingMethod<T>::insertionSort(vector<T> &input, size_t num)
		{
			size_t i, j;
			T tmp;
			for(i = 1; i < num; ++i)
			{
				tmp = input[i];
				for(j = i; j > 0; --j)
				{
					if(input[j-1] > tmp)	
						input[j] = input[j-1];
					else
						break;
				}
				input[j] = tmp;
			}		
		}
	template<class T>
		void SortingMethod<T>::bubbleSort(vector<T> &input, size_t num)
		{
			size_t i, j, k;
			T tmp;
			for(i = 0; i < num - 1; ++i)
			{
				k = i;
				for(j = i+1; j < num; ++j)
				{
					if(input[j] < input[k])
						k = j;
				}	
				tmp = input[i];
				input[i] = input[k];
				input[k] = tmp;
			}
		}
	template<class T>
		void SortingMethod<T>::shellSort(vector<T> &input, size_t num)
		{
			int i, j, incre;
			T tmp;
			
			for(incre = num / 2; incre > 0; incre /= 2)
			{
				for(i = incre; i < num; ++i)
				{
					tmp = input[i];
					for(j = i; j > incre; j -= incre)	
						if(input[j - incre] > tmp)
							input[j] = input[j - incre];
						else
							break;
					input[j] = tmp;
				}	
			}
		}
	template<class T>
		void percoDown(vector<T> &input, size_t i, size_t num)
		{
			size_t child, j;
			T tmp = input[i-1];
			for(j = i; j * 2  <= num; j = child)
			{
				child = 2 * j;
				if(child != num && input[child-1] < input[child])
					child++;
				if(tmp < input[child-1])
					input[j-1] = input[child-1];
				else
					break;
			}	
			input[j - 1] = tmp;
		}
	
	//position zero is not a sentinel 
	template<class T>
		void SortingMethod<T>::heapSort(vector<T> &input, size_t num)
		{
			size_t i;
			T tmp;
			for(i = num / 2; i > 0; --i)
				percoDown(input, i, num);
			for(i = 0; i < num - 1; ++i)
			{
				tmp = input[0];
				input[0] = input[num - i - 1];
				input[num - i - 1] = tmp;
				percoDown(input, 1, num - i - 1);	
			}
		}
	
	template<class T>
	void mergeInput(vector<T> &input, vector<T> &tempInput, size_t left, size_t center, size_t right)
	{
		size_t leftPos = left, rightPos = center + 1;
		size_t tempPos = left;

		while( leftPos <= center && rightPos <= right)
			if(input[leftPos] < input[rightPos])
				tempInput[tempPos++] = input[leftPos++];
			else
				tempInput[tempPos++] = input[rightPos++];
		
		while(leftPos <= center)
			tempInput[tempPos++] = input[leftPos++];

		while(rightPos <= right)
			tempInput[tempPos++] = input[rightPos++];

		while(left <= right)
		{
			input[left] = tempInput[left];
			++left;
		}
			
	}
	template<class T>
	void divideInput(vector<T> &input, vector<T> &tempInput, size_t left, size_t right)
	{
			if(left < right)
			{
				size_t center = (left + right)/2;
				divideInput(input, tempInput, left, center);	
				divideInput(input, tempInput, center+1, right);
				mergeInput<T>(input, tempInput, left, center, right);	
			}
	}
	template<class T>
		void SortingMethod<T>::mergeSort(vector<T> &input, size_t num)
		{
			vector<T> tempInput(num, T());
			divideInput<T>(input, tempInput, 0, num - 1);
		}
	template<class T>
		inline void swapVec(vector<T> &input, size_t lhs, size_t rhs)
		{
			T tmp = input[lhs];
			input[lhs] = input[rhs];
			input[rhs] = tmp;
		}
	template<class T>
		T median3(vector<T> &input, size_t left, size_t right)
		{
			size_t center = (left + right)/2;
			if(input[left] > input[center])
				swapVec<T>(input, left, center);
			if(input[left] > input[right])
				swapVec<T>(input, left, right);
			if(input[center] > input[right])
				swapVec<T>(input, center, right);

			swapVec(input, center, right - 1);
			return input[right-1];
		}
	template<class T>
		void divideOfQsort(vector<T> &input, size_t left, size_t right)
		{
			if(left + 3 < right)
			{
				size_t i, j;
				T pivot = median3(input, left, right);
				i = left;
				j = right - 1;
				for( ; ; )
				{
					while(input[++i] < pivot);
					while(input[--j] > pivot);
					if(i < j)
						swapVec<T>(input, i, j);
					else
						break;	
				}	
				swapVec<T>(input, i, right - 1);
				divideOfQsort<T>(input, left, i - 1);
				divideOfQsort<T>(input, i + 1, right);
			}	
			else
			{
				int i, j;
				T tmp;
				for(i = 1; i <= right; ++i)
				{
					tmp = input[i];
					for(j = i; j > left; --j)
						if(input[j - 1] > tmp)
							input[j] = input[j - 1];
						else
							break;
					input[j] =  tmp;
				}	
			
			}
		}
	template<class T>
		void quickSelectDriver(vector<T> &input, size_t left, size_t right, size_t k)
		{
			if(left + 5 <= right)
			{
				size_t i = left, j = right - 1;	
				T pivot = median3<T>(input, left, right);
				for( ; ; )
				{
					while(input[++i] < pivot);
					while(input[--j] > pivot);	
					if(i < j)
						swapVec<T>(input, i, j);
					else
						break;
				}
				swapVec<T>(input, i, right - 1);
				if(k < i)
					quickSelectDriver(input, left, i-1, k);
				else if(k > i)
					quickSelectDriver(input, i+1, right, k);
			}	
			else
			{
				int i, j;
				T tmp;
				for(i = 1; i <= right; ++i)
				{
					tmp = input[i];
					for(j = i; j > left; --j)
						if(input[j - 1] > tmp)
							input[j] = input[j - 1];
						else
							break;
					input[j] =  tmp;
				}	
			}
		}
	template<class T>
		void SortingMethod<T>::quickSort(vector<T> &input, size_t num)
		{
			divideOfQsort<T>(input, 0, num - 1);
		}
	template<class T>
		void SortingMethod<T>::quickSelect(vector<T> &input, size_t num, size_t k)
		{
			quickSelectDriver<T>(input, 0, num - 1, k-1);	
		}
}
#endif   // SORTING_SORTINGMETHOD_H_

