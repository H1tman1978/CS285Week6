#pragma once

#include <vector>		// Used for creating vectors
#include <string>

using namespace std;

template <class T>
class myVector : public vector<T> {
	bool isSorted = false;
public:	
	static size_t seqSearch(myVector<T> *searchVector, T searchItem);
	static int binarySearch(const myVector<T> *searchVector, T searchItem);
	static void bubbleSort(myVector<T> *aVector);
	static void insertionSort(myVector<T> *aVector);
	bool getSortStatus();
	void setSortStatus(bool status);
};

template <class T>
size_t myVector<T>::seqSearch(myVector<T> *searchVector, T searchItem)
{
	//implement sequential search
	size_t loc = 0;
	bool found = false;

	while (loc < *searchVector.size() && !found)
	{
		if (*searchVector.at(loc) == searchItem)
			found = true;
		else
			loc++;
	}
	if (found)
		return loc;
	return -1;
}

template <class T>
inline void myVector<T>::bubbleSort(myVector<T> *aVector)
{
	//implement bubble sort	
	for (size_t i = 1; i < *aVector.size() - 1; i++) // Loop for iterations
	{
		bool swapped = false;
		for (size_t j = 0; j < *aVector.size() - i - 1; j++) // Loop to compare values
		{
			if (*aVector.at(j) > *aVector.at(j + 1))
			{
				T temp = *aVector.at(j);
				*aVector.at(j) = aVector.at(j + 1);
				*aVector.at(j + 1) = temp;
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop the list is sorted
		if (swapped == false)
			break;
	}
	*aVector.setSortStatus(true);
}

template <class T>
inline void myVector<T>::insertionSort(myVector<T> *aVector)
{
	//implement insertion sort	
	for (size_t i = 1; i < *aVector.size(); i++)
	{
		if (*aVector.at(i) < *aVector.at(i - 1))
		{
			T temp = *aVector.at(i);
			size_t location = i;

			do 
			{
				*aVector.at(location) = *aVector.at(location - 1);
				location--;
			} while (location > 0 && *aVector.at(location - 1) > temp);
			*aVector.at(location) = temp;
		}
	}
	*aVector.setSortStatus(true);
}

template<class T>
inline bool myVector<T>::getSortStatus()
{
	return isSorted;
}

template<class T>
inline void myVector<T>::setSortStatus(bool status)
{
	isSorted = status;
}

template <class T>
int myVector<T>::binarySearch(const myVector<T> *searchVector, T searchItem)
{
	//implement binary search...searchVector must be sorted prior to use
	int first = 0;
	int last = *searchVector.size() - 1;
	int mid;
	bool found = false;
	
	while (first <= last && !found)
	{
		mid = (first + last) / 2;
		if (*searchVector.at(mid) == searchItem)
			found = true;
		else if (*searchVector.at(mid) > searchItem)
			last = mid - 1;
		else
			first = mid + 1;
	}

	if (found)
		return mid;
	else
		return -1;
}	// End of myVector class
