// CS285RolfeAnthonyWeek6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "myVector.h"
#include <iostream>		// Used for console operations
#include <string>		// Used for creating strings
#include <algorithm>	// Used for lambda function
#include <random>		// Used for random number generation
#include <chrono>		// Used for testing

using namespace std;


// Functions to load lists
// Function to generate a random string
string genRandomString(int len) {
	auto randchar = []() -> char {
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	string str(len, 0);
	std::generate_n(str.begin(), len, randchar);
	return str;
}

// Function to Generate a random String vector
myVector<string> randomStringVectorGenerator(int numberOfItems) {
	myVector<string> tempVector;
	for (int i = 0; i < numberOfItems; ++i)
	{
		tempVector.push_back(genRandomString(15));
	}
	return tempVector;
}

// Function to create a random double vector between 0.0 and 1,000,000.0
myVector<double> randomDoubleVectorGenerator(int numberOfItems) {
	myVector<double> tempVector;
	random_device rd;  // Used for seed generation
	mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(0.0, 1.0);
	for (int n = 0; n < numberOfItems; ++n)
	{
		tempVector.push_back(dis(gen) * 1000000);
	}
	return tempVector;
}

// Function to create a random int vector of +/-1,000,000
myVector<int> randomIntVectorGenerator(int numberOfItems) {
	myVector<int> tempVector;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(-1.0, 1.0);
	for (int n = 0; n < numberOfItems; ++n)
	{
		tempVector.push_back(int(dis(gen) * 1000000));
	}
	return tempVector;
}

// Function to create a random int given min and max numbers (used to select a random index as the target for searches)
int randomInt(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(min, max);
	return int(dis(gen));
}

// Testing Functions
// Functions that tests sorting methods
// Bubble Sort Testing
template< typename T>
void testBubbleSorting(myVector<T> testVector) {
	cout << "Testing a Bubble Sort on your vector...\n";
	auto t1 = chrono::high_resolution_clock::now();
	myVector<T>::bubbleSort(testVector);
	auto t2 = chrono::high_resolution_clock::now();
	double time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
	cout << "Bubble Sort took " << time	<< " milliseconds.\n\n";	
}

// Insertion Sort Testing
template< typename T>
void testInsertionSorting(myVector<T> testVector) {
	cout << "Testing an Insertion Sort on your vector...\n";
	auto t1 = chrono::high_resolution_clock::now();
	myVector<T>::insertionSort(testVector);
	auto t2 = chrono::high_resolution_clock::now();
	double time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
	cout << "Insertion Sort took " << time << " milliseconds.\n\n";	
}

// Binary Search Testing
template< typename T>
void binarySearchTime(myVector<T> testVector) {
	int randomIndex = randomInt(0, testVector.size());
	T searchItem = testVector[randomIndex];
	if (testVector.getSortStatus() == false)
	{
		cout << "Test vector is not sorted...using insertion sort";
	} 
	else
	{
		cout << "Testing an Binary Search on your vector...\n";
		cout << "Looking for " << searchItem << " in your vector...\n";
		auto t1 = chrono::high_resolution_clock::now();
		int resultLocation = myVector<T>::binarySearch(testVector, testVector[501]);
		auto t2 = chrono::high_resolution_clock::now();
		cout << searchItem << " was found at index " << resultLocation << "\n";
		double time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
		cout << "Binary Search took " << time << " milliseconds.\n\n";
	}	
}

// Sequential Search Testing
template< typename T>
void sequentialSearchTime(myVector<T> testVector) {
	int randomIndex = randomInt(0, testVector.size());
	T searchItem = testVector[randomIndex];
	cout << "Testing an Sequential Search on your vector...\n";
	cout << "Looking for " << searchItem << " in your vector...\n";
	auto t1 = chrono::high_resolution_clock::now();
	int resultLocation = myVector<T>::seqSearch(testVector, testVector[randomIndex]);
	auto t2 = chrono::high_resolution_clock::now();
	cout << searchItem << " was found at index " << resultLocation << "\n";
	double time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
	cout << "Sequential Search took " << time << " milliseconds.\n\n";
}

// Function to test all sorting functions
template<class T>
void testAllSortingFunctions(myVector<T> testVector) {
	testBubbleSorting(testVector);
	testInsertionSorting(testVector);	
}

// Function to test all search functions
template<class T>
void testAllSearchFunctions(myVector<T> testVector) {
	sequentialSearchTime(testVector);
	binarySearchTime(testVector);
}

// Function to print a vector
template<class T>
void printVector(myVector<T> anyVector) {
	cout << "Vector contents:  ";
	for (int i = 0; i < anyVector.size(); i++)	
	{
		cout << anyVector.at(i) << ", ";
	}
}

int main()
{
	//define test vector(s)
	myVector<string> nameList;
	myVector<int> intList;
	myVector<double> doubleList;

	//add values to the vector(s)
	nameList = randomStringVectorGenerator(10);
	intList = randomIntVectorGenerator(10);
	doubleList = randomDoubleVectorGenerator(10);	

	//test sort methods
	cout << "All vectors have 1000 items.\n\n";
	cout << "Testing sort functions on String Vector.\n\n";
	testAllSortingFunctions(nameList);
	cout << "Testing sort functions on int Vector.\n\n";
	testAllSortingFunctions(intList);
	cout << "Testing sort functions on double Vector.\n\n";
	testAllSortingFunctions(doubleList);

	//test search methods
	cout << "Testing search functions on String Vector. \n\n";
	testAllSearchFunctions(nameList);
	cout << "Testing Search functions on int Vector. \n\n";
	testAllSearchFunctions(intList);
	cout << "Testing search functions on double Vector. \n\n";
	testAllSearchFunctions(doubleList);

	//print sorted vector using range based for loop
	printVector(nameList);
	printVector(intList);
	printVector(doubleList);

		//define new test vector(s)


		//define an iterator to each of the above vector containers

		//add values to the vector(s)

		//test the STL sort method

		 //test the STL binary_search algorithm

		//print the resulting vector(s) using an iterator

	return 0;
}