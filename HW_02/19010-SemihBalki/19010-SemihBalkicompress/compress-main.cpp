#include <iostream>
#include <string>
#include <fstream>
#include "bst.h"
#include <vector>
using namespace std;
//Compression algorithm

bool alphabet_check(int x)
{
    if(x > 4096)
        return false;

    return true;
}

int main()
{
    ifstream input;
    input.open("compin");
    ofstream output;
    output.open("compout");

    BST<string, int> dictionary(-1);//Create the BST, and note that (return -1, if not found)

    int alphabet = 256, print, check, ctr = 0;
    string old_prefix, prefix = "";
    char c;
    bool Entered = false;//If the given file is empty

    if(alphabet_check(alphabet))
    {
        while (input.get(c))
        {
            if(c == ' ')
                continue;

            Entered = true;
            prefix += c;
            check = dictionary.find(prefix);
            if(prefix.length() > 1 && check == -1)// p is not in dict and length of the prefix is greater than 1
            {
                dictionary.insert(prefix, alphabet++);// add p into dict and increase the number of character number

                if (old_prefix.length() == 1)// determine the code of oldp (p - ch)
                    print = old_prefix.at(0);
                else{//If prefix is greater than 1, check that in the BST to have the number
                    print = dictionary.find(old_prefix);
                }
                output << print << " ";
                prefix = c;
            }
            old_prefix = prefix;
        }
        if (Entered)//For the remaining string issue
        {
            if (old_prefix.length() == 1)
                print = old_prefix.at(0);
            else{
                print = dictionary.find(old_prefix);
            }
            output << print;
        }
    }

    input.close();
    output.close();
    return 0;
}