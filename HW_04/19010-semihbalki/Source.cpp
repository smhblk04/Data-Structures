#include <vector>
#include "MPQ.h"

extern vector<int> heights;

class coord
{
public:
	int id, side, x_cor;

	bool operator<(coord rhs) //coord rhs
	{
		return 	(x_cor < rhs.x_cor) || (x_cor == rhs.x_cor && side < rhs.side) || (x_cor == rhs.x_cor && side == rhs.side && side == -1 && heights[id] > heights[rhs.id]) || (x_cor == rhs.x_cor && side == rhs.side && side == 1 && heights[id] < heights[rhs.id]); 
	}

	coord operator=(coord rhs)
	{
		x_cor = rhs.x_cor;
		side = rhs.side;
		id = rhs.id;
		return *this;
	}
};

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//Prototype's
void heapsort(vector<coord> & a);
void percDown(vector<coord> & a, int i, int n);

int main ()
{
	ifstream input;
	string filename;
	input.open("input.txt");

	int num, left, right, count = 0;
	input >> num;

	// no building
	if (num == 0)
	{
		input.close();
		
		cout << 0 << " " << 0 << endl;
	
		return 0;
	}

	heights.resize(num+1);// reserve for the heights
	heights.push_back(0);
	vector<coord> spans(2*num);//vector<coord>

	//left represented as -1
	//right represented as 1
	for (int i = 1; i <= num; i++)
	{
		input >> left >> heights[i] >> right;	
	
		// left x-coord
		spans[count].id = i;
		spans[count].side = -1;
		spans[count].x_cor = left;
		count++;

		// right x-coord
		spans[count].id = i;
		spans[count].side = 1;
		spans[count].x_cor = right;
		count++;
	}
	
	// sort the coordinate array
	heapsort(spans);

	// heap
	MPQ<int> myheap(num);
	
	int currentMax = INT_MIN;

	if (spans[0].x_cor != 0)//No building case
		cout << 0 << " " << 0 << endl;

	for (int i = 0; i < 2*num; i++)//Each coordinate
	{
		if (spans[i].side == -1)//Left coordinate case: insert to heap
			myheap.insert(heights[spans[i].id], spans[i].id);

		else//Right coordinate: remove from heap
			myheap.remove(spans[i].id);

		if (myheap.getMax() != currentMax)//If change occurred, print max element
		{	
			currentMax = myheap.getMax();
			cout << spans[i].x_cor << " " << currentMax << endl;
		}
	}

	input.close();

	return 0;
}

void percDown(vector<coord> & a, int i, int n)
{
	int child;
	coord temp;

	for (temp = a[i]; 2*i+1 < n; i = child)
	{
		child = 2*i+1;
		if (child != n-1 && a[child] < a[child+1])// compare left and right
			child++;

		if (temp < a[child])// if necessary, percolate
			a[i] = a[child];
		else
			break;
	}
	
	a[i] = temp;
}

void heapsort(vector<coord> & a)
{	
	if(!a.size())	
		return;

	for (int i = a.size()/2; i >= 0; i--)//build heap
		percDown(a, i, a.size());

	for (int j = a.size() - 1; j > 0; j--)
	{
		coord tmp = a[0];		//swap the max element
		a[0] = a[j];
		a[j] = tmp; 
		percDown(a, 0, j);
	}
}
