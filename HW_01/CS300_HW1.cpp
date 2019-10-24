#include <iostream>
#include <string>
#include "linkedlist.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include "strutils.h"
#include <vector>
using namespace std;

int main() {
    ifstream input;
    linkedlist<string> list;

    input.open("docdb2.txt");

    string line, unique_word, name, filenumber;

    while(!input.eof())//!input.eof()
    {
        getline(input, line);
        istringstream ss(line);

        if(line != ""){
            ss >> unique_word >> filenumber;
            if(atoi(filenumber) > 0) {
                list.sort(unique_word, filenumber);
            }
        }
        ss.clear();
    }

    list.print();

    //Query asking part
    int positive_number;
    string query;
    cout << "Please enter a query " << endl;
    cin >> positive_number;
    getline(cin, query);
    query = query.substr(1, query.find("\n"));

    string word;
    vector<string> words;
    while(positive_number != 0)
    {
        istringstream ss_new(query);
        while (getline(ss_new, word, ' ')) {
            words.push_back(word);//Kullanicidan alinan kelimeleri bir vektorde depola
        }
        list.intersect(words);
        words.clear();
        cout << "Please enter a query: " << endl;
        cin >> positive_number;
		getline(cin, query);//Eklendi
		query = query.substr(1, query.find("\n"));//Eklendi
    }
    system("PAUSE");
    return 0;
}