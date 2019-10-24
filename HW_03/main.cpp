#include <iostream>
#include "randgen.h"
#include <random>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <cassert>
#include <ostream>
using namespace std;

bool check(int case1_0, int case1_1, int case2_0, int case2_1, int case3_0, int case3_1);
int nextprime(const int & x);//Taken from Lecture notes
bool isprime(const int & x);//Taken from lecture notes	
void output(vector<vector<double>> result1_0, vector<vector<double>> result1_1, vector<vector<double>> result2_0, vector<vector<double>> result2_1, vector<vector<double>> result3_0, vector<vector<double>> result3_1);
int number_of_columns(vector<double> vec);

class HashTable
{
public:
	explicit HashTable(int size);	
	void makeEmpty();//Taken from CS300 textbook
	int contains(const int & x) const;	
	int insert(const int & x);		
	int remove(const int & x);		

	enum EntryType { ACTIVE, EMPTY, DELETED };

	int getcurrentSize() const;	
	int gettotalsize() const;	

private:
	struct HashEntry
	{
		int element;
		EntryType info;

		HashEntry(const int & e = int(), EntryType i = EMPTY)
			: element(e), info(i) {}
	};

	vector<HashEntry> array;
	int currentSize;
	int totalSize;

	bool isActive(int currentPos) const;//Taken from CS300 textbook
	int findPos(const int & x, int &i) const;

	int myhash(const int & x) const;		
};

int HashTable::getcurrentSize() const
{
	return currentSize;
}

int HashTable::gettotalsize() const
{
	return totalSize;
}

int HashTable::myhash(const int & x) const
{
	return x % totalSize;
}

HashTable::HashTable(int size) :
	array(nextprime(size)), totalSize(nextprime(size))
{
	makeEmpty();
}

void HashTable::makeEmpty()
{
	currentSize = 0;
	for (auto & entry : array)
		entry.info = EMPTY;
}

int HashTable::findPos(const int & x, int &i) const
{
	int currentPos = myhash(x);
	while (array[currentPos].info == ACTIVE && array[currentPos].element != x)
	{
		currentPos++;
		i++;

		currentPos %= array.size();
	}

	return currentPos;
}

bool HashTable::isActive(int currentPos) const
{
	return array[currentPos].info == ACTIVE;
}

int HashTable::contains(const int & x) const
{
	int probe = 1;
	int found = findPos(x, probe);

	if (isActive(found) == true)
		return probe;
	else
		return -1 * probe;
}

int HashTable::insert(const int & x)
{
	int probe = 1;
	int currentPos = findPos(x, probe);
	if (isActive(currentPos))//The element is already in the Table
		return -1 * probe;
	//Else
	array[currentPos].element = x;
	array[currentPos].info = ACTIVE;
	currentSize++;

	return probe;
}

int HashTable::remove(const int & x)
{//Taken from CS300 textbook, added new lines
	int probe = 1;
	int currentPos = findPos(x, probe);
	if (!isActive(currentPos))//Adjusted
		return -1 * probe;

	array[currentPos].info = DELETED;
	currentSize--;//Added

	return probe;
}

bool check(int case1_0, int case1_1, int case2_0, int case2_1, int case3_0, int case3_1)
{
	return ((case1_0 + case1_1 == 1000000) || (case2_0 + case2_1 == 1000000) || (case3_0 + case3_1 == 1000000));
}

int nextprime(const int & x)
{
	int xx = x;

	while (!isprime(xx))
		xx++;

	return xx;
}

bool isprime(const int & x)
{
	int i;

	for (i = 2; i < x; i++)
		if (!(x % i))
			return false;

	return true;
}

int number_of_columns(vector<double> vec)
{//Returns the number of columns at specified row
	int count = 0;
	if(!vec.empty())
	{
		for(vector<double>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			count++;
		}
	}
	return count;
}

void output(vector<vector<double>> result1_0, vector<vector<double>> result1_1, vector<vector<double>> result2_0, vector<vector<double>> result2_1, vector<vector<double>> result3_0, vector<vector<double>> result3_1)
{
	//First row of the each matrix is for 6 1 1 combination
	//Second row of the each matrix is for 4 2 2 combination
	//Third row of the each matrix is for 2 1 5 combination
	ofstream file1_0, file1_1, file2_0, file2_1, file3_0, file3_1;
	file1_0.open("unsuccessful_insert.csv");
	file1_1.open("successful_insert.csv");
	file2_0.open("unsuccessful_delete.csv");
	file2_1.open("successful_delete.csv");
	file3_0.open("unsuccessful_find.csv");
	file3_1.open("successful_find.csv");

	int j = 0;
	int k = 0;
	int i = 0;
	int number = number_of_columns(result1_0[1]);
	int number_2 = number_of_columns(result1_0[2]);
	while ((j < result1_0[0].size()) && (k < number) && (i < number_2))
	{
		file1_0 << result1_0[0][j] << ";" << result1_0[1][k] << ";" << result1_0[2][i] << endl;
		j++;
		k++;
		i++;
	}

	file1_0.close();

	j = 0;
	k = 0;
	i = 0;
	number = number_of_columns(result1_1[1]);
	number_2 = number_of_columns(result1_1[2]);
	while ((j < result1_1[0].size()) && (k < number) && (i < number_2))
	{
		file1_1 << result1_1[0][j] << ";" << result1_1[1][j] << ";" << result1_1[2][j] << endl;
		j++;
		k++;
		i++;
	}
	file1_1.close();

	j = 0;
	k = 0;
	i = 0;
	number = number_of_columns(result2_0[1]);
	number_2 = number_of_columns(result2_0[2]);
	while ((j < result2_0[0].size()) && (k < number) && (i < number_2))
	{
		file2_0 << result2_0[0][j] << ";" << result2_0[1][j] << ";" << result2_0[2][j] << endl;
		j++;
		k++;
		i++;
	}
	file2_0.close();

	j = 0;
	k = 0;
	i = 0;
	number = number_of_columns(result2_1[1]);
	number_2 = number_of_columns(result2_1[2]);
	while ((j < result2_1[0].size()) && (k < number) && (i < number_2))
	{
		file2_1 << result2_1[0][j] << ";" << result2_1[1][j] << ";" << result2_1[2][j] << endl;
		j++;
		k++;
		i++;
	}
	file2_1.close();

	j = 0;
	k = 0;
	i = 0;
	number = number_of_columns(result3_0[1]);
	number_2 = number_of_columns(result3_0[2]);
	while ((j < result3_0[0].size()) && (k < number) && (i < number_2))
	{
		file3_0 << result3_0[0][j] << ";" << result3_0[1][j] << ";" << result3_0[2][j] << endl;
		j++;
		k++;
		i++;
	}
	file3_0.close();

	j = 0;
	k = 0;
	i = 0;
	number = number_of_columns(result3_1[1]);
	number_2 = number_of_columns(result3_1[2]);
	while ((j < result3_1[0].size()) && (k < number) && (i < number_2))
	{
		file3_1 << result3_1[0][j] << ";" << result3_1[1][j] << ";" << result3_1[2][j] << endl;
		j++;
		k++;
		i++;
	}
	file3_1.close();
}

int main()
{
	struct Entry
	{
		int transaction;
		double probe;
	};

	int number;
	int hold;
	int size;
	int total_num_of_transaction;

	int M = 0;//Size of the hash table
	M = rand() % 10000 + 10000;

	M = nextprime(M);

	vector<Entry> arr1_0(M + 1);//Unsuccessfull insert
	vector<Entry> arr1_1(M + 1);//Successfull insert
	vector<Entry> arr2_0(M + 1);//Unsuccessfull delete
	vector<Entry> arr2_1(M + 1);//Successfull delete
	vector<Entry> arr3_0(M + 1);//Unsuccessfull find
	vector<Entry> arr3_1(M + 1);//Successfull find

	//Hold the statistical value
	vector<double> hold1_0(M + 1);
	vector<double> hold1_1(M + 1);
	vector<double> hold2_0(M + 1);
	vector<double> hold2_1(M + 1);
	vector<double> hold3_0(M + 1);
	vector<double> hold3_1(M + 1);

	//To collect the results
	vector<vector<double>> result1_0;
	vector<vector<double>> result1_1;
	vector<vector<double>> result2_0;
	vector<vector<double>> result2_1;
	vector<vector<double>> result3_0;
	vector<vector<double>> result3_1;

	HashTable Table(M);

	for (int i = 1; i <= 3; i++)
	{
		Table.makeEmpty();

		total_num_of_transaction = 0;
		do
		{
			int t = rand();
			int m = t % 8;

			number = rand() % 10000000;

			size = Table.getcurrentSize();

			if (i == 1) {//First combination out of 3 combination
				if (0 <= m && m <= 5)//Insert
				{
					hold = Table.insert(number);
					if (hold > 0)//Successfull
					{
						arr1_1[size].probe += hold;
						arr1_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr1_0[size].probe -= hold;
						arr1_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
				else if (m == 6)//Delete
				{
					hold = Table.remove(number);
					if (hold > 0)//Successfull
					{
						arr2_1[size].probe += hold;
						arr2_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr2_0[size].probe -= hold;
						arr2_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
				else//Find
				{
					hold = Table.contains(number);
					if (hold > 0)//Successfull
					{
						arr3_1[size].probe += hold;
						arr3_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr3_0[size].probe -= hold;
						arr3_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
			}
			if (i == 2) {//Second combination out of 3 combination
				if (0 <= m && m <= 3)//Insert
				{
					hold = Table.insert(number);
					if (hold > 0)//Successfull
					{
						arr1_1[size].probe += hold;
						arr1_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr1_0[size].probe -= hold;
						arr1_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
				else if (4 <= m && m <= 5)//Delete
				{
					hold = Table.remove(number);
					if (hold > 0)//Successfull
					{
						arr2_1[size].probe += hold;
						arr2_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr2_0[size].probe -= hold;
						arr2_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
				else//Find
				{
					hold = Table.contains(number);
					if (hold > 0)//Successfull
					{
						arr3_1[size].probe += hold;
						arr3_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr3_0[size].probe -= hold;
						arr3_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
			}
			if(i == 3){//Third combination
				if (0 <= m && m <= 1)//Insert
				{
					hold = Table.insert(number);
					if (hold > 0)//Successfull
					{
						arr1_1[size].probe += hold;
						arr1_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr1_0[size].probe -= hold;
						arr1_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
				else if (m == 2)//Delete
				{
					hold = Table.remove(number);
					if (hold > 0)//Successfull
					{
						arr2_1[size].probe += hold;
						arr2_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr2_0[size].probe -= hold;
						arr2_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
				else//Find
				{
					hold = Table.contains(number);
					if (hold > 0)//Successfull
					{
						arr3_1[size].probe += hold;
						arr3_1[size].transaction += 1;
						total_num_of_transaction++;
					}
					else
					{
						arr3_0[size].probe -= hold;
						arr3_0[size].transaction += 1;
						total_num_of_transaction++;
					}
				}
			}
		} while ((Table.getcurrentSize() < M) && (total_num_of_transaction < 10000000));

		//Table.getcurrentSize() + 1
		for (int j = 0; j < M + 1; j++)
		{
			if (arr1_0[j].transaction != 0.0)
				hold1_0.push_back(arr1_0[j].probe / arr1_0[j].transaction);
			if (arr1_1[j].transaction != 0.0)
				hold1_1.push_back(arr1_1[j].probe / arr1_1[j].transaction);
			if (arr2_0[j].transaction != 0.0)
				hold2_0.push_back(arr2_0[j].probe / arr2_0[j].transaction);
			if (arr2_1[j].transaction != 0.0)
				hold2_1.push_back(arr2_1[j].probe / arr2_1[j].transaction);
			if (arr3_0[j].transaction != 0.0)
				hold3_0.push_back(arr3_0[j].probe / arr3_0[j].transaction);
			if (arr3_1[j].transaction != 0.0)
				hold3_1.push_back(arr3_1[j].probe / arr3_1[j].transaction);
		}

        arr1_0.clear();
        arr1_1.clear();
        arr2_0.clear();
        arr2_1.clear();
        arr3_0.clear();
        arr3_1.clear();

		arr1_0.resize(M + 1);
		arr1_1.resize(M + 1);
		arr2_0.resize(M + 1);
		arr2_1.resize(M + 1);
		arr3_0.resize(M + 1);
		arr3_1.resize(M + 1);

		result1_0.push_back(hold1_0);
		result1_1.push_back(hold1_1);
		result2_0.push_back(hold2_0);
		result2_1.push_back(hold2_1);
		result3_0.push_back(hold3_0);
		result3_1.push_back(hold3_1);

		hold1_0.clear();
        hold1_1.clear();
        hold2_0.clear();
        hold2_1.clear();
        hold3_0.clear();
        hold3_1.clear();
	}

	output(result1_0, result1_1, result2_0, result2_1, result3_0, result3_1);

	return 0;
}