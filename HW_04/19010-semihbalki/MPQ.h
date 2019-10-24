#ifndef MPQ_H
#define MPQ_H
#include <vector>
#include <iostream>
using namespace std;

vector<int> heights;

template<class comparable>
struct element		// element of the heap
{
	comparable value;
	comparable label;
};

template<class comparable>
class MPQ		// modified priority queue
{
public:
	MPQ(comparable size = 0) :
		heap_array(size+1), locations(size+1)
	{ 
		currentSize = 0;	
	} 
	~MPQ() {}
	void insert (comparable value, comparable label);
	comparable remove (comparable label);			
	comparable getMax() const;			
	bool isEmpty() const;		
	void print() const;			

private:
	comparable currentSize;			
	vector<element<comparable>> heap_array;			
	vector<comparable> locations;			
	void percolateDown (comparable hole);		
};

template<class comparable>
void MPQ<comparable>::insert (comparable value, comparable label)
{
	// create a hole and poercolate it up
	comparable hole = ++currentSize;
	for (; hole > 1 && value > heap_array[hole/2].value; hole /= 2)
	{
		heap_array[hole].value = heap_array[hole/2].value;
		heap_array[hole].label = heap_array[hole/2].label;

		// update location in each time
		locations[heap_array[hole].label] = hole;
	}
	heap_array[hole].value = value;
	heap_array[hole].label = label;
	locations[heap_array[hole].label] = hole;
}

template<class comparable>
comparable MPQ<comparable>::remove(comparable label)
{
	// return 0 if the heap is empty or there doesn't exist the labeled item
	if (isEmpty() || !locations[label])
		return 0;

	//swap 

	comparable value = heap_array[locations[label]].value;

	heap_array[locations[label]].value = heap_array[currentSize].value;
	heap_array[locations[label]].label = heap_array[currentSize].label;
	currentSize--;

	// percolate 
	percolateDown(locations[label]);
	locations[label] = 0;

	return value;	
}

template<class comparable>
comparable MPQ<comparable>::getMax() const
{
	if (isEmpty())	
		return 0;
	
	return heap_array[1].value;
}

template<class comparable>
bool MPQ<comparable>::isEmpty() const
{

	if (currentSize)	
		return false;

	return true;
}

template<class comparable>
void MPQ<comparable>::percolateDown(comparable hole)
{
	comparable child;
	
	comparable value = heap_array[hole].value;
	comparable label = heap_array[hole].label;


	//percolate the removed place
	for(; hole * 2 <= currentSize; hole = child)
	{
		child = hole*2;

		// compare left and right child
		if (child != currentSize && heap_array[child + 1].value > heap_array[child].value)
			child++;

		// if necessary percolate 
		if (heap_array[child].value > value)
		{
			heap_array[hole].value = heap_array[child].value;
			heap_array[hole].label = heap_array[child].label;

			locations[heap_array[hole].label] = hole;
		}
		else	
			break;
	}

	heap_array[hole].value = value;
	heap_array[hole].label = label;

	locations[heap_array[hole].label] = hole;
}

template<class comparable>
void MPQ<comparable>::print() const
{
	// for heap
	cout << endl << "array:" << endl;
	for (comparable i = 1; i <= currentSize; i++)	
		cout << i << ":" << heap_array[i].value << " ";

	cout << endl;	
}
#endif