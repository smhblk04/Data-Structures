#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	struct dictionary
	{
		string s;
	};
	ifstream input;
	input.open("compout");

	ofstream output;
	output.open("decompout");
	
	vector<dictionary> vec(4096);//Initializing the dictionary with 4096 empty spaces since we could take at most 4096
	for(int i = 0; i < 256; i++)
	{
		vec[i].s = i;
	}

	int nextcode = 256;
	int prevcode, code;

	input >> code;
	output << vec[code].s;

	prevcode = code;
	while (input >> code)
	{
		if(code < nextcode)	// the code is in dictionary if the taken code below 255
		{
			output << vec[code].s;

			vec[nextcode].s = vec[prevcode].s + vec[code].s.at(0);
			nextcode++;
		}

		else//Add new letters to the dictionary
		{
			vec[nextcode].s = vec[prevcode].s + vec[prevcode].s.at(0);
			nextcode++;
			output << vec[prevcode].s + vec[prevcode].s.at(0);
		}

		prevcode = code;
	}

	input.close();
	output.close();
	return 0;
}