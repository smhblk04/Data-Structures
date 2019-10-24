//
// Created by Semih Balki on 10/21/18.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include "strutils.h"
#include <vector>
using namespace std;

template<class T>
struct filenode
{
    T number;
    filenode<T> *next;

    filenode()
    {}

    filenode(T numb, filenode<T> *pt = nullptr):
            number(numb), next(pt)
    {}
};

template<class T>
struct node
{
    T word;
    filenode<T> *down;
    node<T> *next;

    node()
    {}

    node(T name, filenode<T> *dw = nullptr, node<T> *ptr = nullptr):
            word(name), down(dw), next(ptr)
    {}
};

template<class T>
class linkedlist
{
private:
    node<T> *head;
public:
    linkedlist();
    void sort(T newword, T number);
    void print();
    ~linkedlist();
    void intersect(vector<T> vec);
};

template<class T>
linkedlist<T>::linkedlist()
{
    head = NULL;
}

template<class T>
void linkedlist<T>::sort(T newword, T number){
    node<T> *ptr = head;
    filenode<T> *ptr_ver;
    bool k = true;

    if(head == NULL)
    {
        filenode<T> *temp = new filenode<T>(number, NULL);
        head = new node<T>(newword, NULL, NULL);
        head->down = temp;
        head->down->next = NULL;
        ptr_ver = temp;
    }
    else {
        while (ptr != NULL) {
            ptr_ver = ptr->down;
            if(newword == ptr->word)//(Ayni kelime
            {
                /* if (ptr_ver->next == NULL) {
                     ptr_ver->next = new filenode<T>(number, NULL);
                     ptr_ver = ptr_ver->next;
                 }*/

                while (ptr_ver != NULL) {
                    if (atoi(ptr_ver->number) > atoi(number)) {
                        filenode<T> *temp = new filenode<T>(number, NULL);
                        temp->next = ptr->down;
                        ptr->down = temp;
                        break;
                    }
                    else if(atoi(number) > atoi(ptr_ver->number) && (ptr_ver->next == NULL)) {
                        filenode<T> *temp = new filenode<T>(number, NULL);
                        ptr_ver->next = temp;
                        break;
                    }
                    else if (atoi(ptr_ver->number) < atoi(number) && atoi(number) < atoi(ptr_ver->next->number)) {
                        filenode<T> *temp = new filenode<T>(number, ptr_ver->next);
                        ptr_ver->next = temp;
                        break;
                    }
                    else if(atoi(ptr_ver->number) == atoi(number))
                    {
                        break;
                    }
                    ptr_ver = ptr_ver->next;
                }

            }
			else if(ptr->next != NULL){//Eklendi
				if(((ptr->word < newword) && (newword < ptr->next->word))) {//Yeni kelime
					filenode<T> *temp_1 = new filenode<T>(number, NULL);
					node<T> *temp = new node<T>(newword, temp_1, ptr->next);
					ptr->next = temp;
				}
			}
			else if(newword < head->word){//Yeni kelime
                filenode<T> *temp_1 = new filenode<T>(number, NULL);
				node<T> *temp = new node<T>(newword, temp_1, head);
				head = temp;
            }
			else if(newword > ptr->word && ptr->next == NULL){//Eklendi 
                filenode<T> *temp_1 = new filenode<T>(number, NULL);
				node<T> *temp = new node<T>(newword, temp_1, NULL);
				ptr->next = temp;
            }
            ptr = ptr->next;
        }
    }
	/*else if(ptr->next == NULL){
				if(ptr->word < newword) {//Yeni kelime
					filenode<T> *temp_1 = new filenode<T>(number, NULL);
					node<T> *temp = new node<T>(newword, temp_1, NULL);
					ptr->next = temp;
				}
			}*/
			/*else if(ptr != head){
				if(ptr->word < newword) {//Yeni kelime
					filenode<T> *temp_1 = new filenode<T>(number, NULL);
					node<T> *temp = new node<T>(newword, temp_1, ptr);
					prev->next = temp;
				}
			}*/
}

template<class T>
void linkedlist<T>::intersect(vector<T> vec)
{
    vector<T> cumulative_words;//Kullanicidan sorgulanan kelimelerin bulundugu dosyalari tutan vektor
    vector<T> intersected_words;//Kullanicidan sorgulanan kelimelerin kesistigi dosya numaralarini tutan vektor
    vector<T> final_intersected_words;//Kullanicidan sorgulanan kelimelerin kesistigi dosya numaralarini tutan vektor'un son hali
    node<T> *ptr;
    for(int i = 0; i < vec.size(); i++)
    {
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->word == vec[i])
            {
                filenode<T> *ptr_ver = ptr->down;
                while(ptr_ver != NULL)
                {
                    cumulative_words.push_back(ptr_ver->number);
                    ptr_ver = ptr_ver->next;
                }
            }
            ptr = ptr->next;
        }
    }
    int count;
    for(int i = 0; i < cumulative_words.size(); i++)
    {
        count = 1;
        for(int j = 0; j < cumulative_words.size(); j++)
        {
            if(i != j)
            {
                if(atoi(cumulative_words[i]) == atoi(cumulative_words[j]))
                {
                    count++;
                    if(count == vec.size())
                    {
                        intersected_words.push_back(cumulative_words[i]);
                    }
                }
            }
        }
    }
    unsigned long i = 0;
    unsigned long size = vec.size();
    while(i < intersected_words.size())
    {
        final_intersected_words.push_back(intersected_words[i]);
        i = i + size;
    }
    for(int k = 0; k < vec.size(); k++)
    {
        cout << vec[k] << " ";
    }
    cout << final_intersected_words.size() << " ";
    for(int i = 0; i < final_intersected_words.size(); i++)
    {
        cout << final_intersected_words[i] << " ";
    }
    cout << endl;
}

template <class T>
void linkedlist<T>::print()
{
    node<T> *ptr=head;

    if(head == nullptr)
    {
        cout << "List is empty." << endl;
    }
    else {
        while (ptr != nullptr) {
            cout << ptr->word << ": ";
            filenode<T> *ptr_1 = ptr->down;
            while(ptr_1 != NULL)
            {
                cout << ptr_1->number;
                ptr_1 = ptr_1 -> next;
                cout << " ";
            }
            ptr = ptr->next;
            cout << endl;
        }
    }
}

template<class T>
linkedlist<T>::~linkedlist()
{//Linear
    node<T> *ptr=head;
    if(head == nullptr)
    {
        cout << "Nothing to delete." << endl;
    }
    else
    {
        while(ptr != nullptr)
        {
            filenode<T> *ptr_1 = ptr->down;
            filenode<T> *head_info = ptr_1;
            while(ptr_1 != NULL)
            {
                ptr_1 = ptr_1->next;
                delete head_info;
                head_info = ptr_1;
            }
            ptr = ptr->next;
            delete head;
            head = ptr;
        }
    }
}

#endif //CS300_HW1_LINKEDLIST_H