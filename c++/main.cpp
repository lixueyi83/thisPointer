/*************************************************************************
	> File Name: stl_set.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <iterator>
#include <list>
#include <string>
#include "debug.h"

using namespace std;

/***********************************************************************
    Benefits and Features of std::set:
    1. It’s doesn’t allow duplicate elements i.e. it only contains unique elements.
    2. std::set can contain element of any specified type in template argument i.e.
    3. std::set internally store elements in balanced binary tree.
    4. By default std::set uses the operator < for comparator 
    5. std::set will keep the inserted elements in sorted order based on the comparator
    
Notice:
    But you cannot modify the elements using iterators because if you modify the element 
    value then internal data structure of std::set will get corrupt and it will not remain 
    balanced binary search tree. Hence further additions and find operations will not work properly.
    
    It internally maintains a binary balanced tree and during insertion it compares the new 
    element with already present nodes and finds the right position of new element in tree. 
    If that element is already present then it doesn’t insert the new element.
*/

int main_insert_find()
{
	std::set<std::string> setOfNumbers;
 
	/* Lets insert four elements */
	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");
	setOfNumbers.insert("first");
	setOfNumbers.insert("aaaaa");
	setOfNumbers.insert("ddddd");
	setOfNumbers.insert("ccccc");
 
	/* Only 3 elements will be inserted */
	std::cout<<"Set Size = "<<setOfNumbers.size()<<std::endl;
 
	/* Iterate through all the elements in a set and display the value. */
	for (std::set<std::string>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
	    std::cout << *it << endl;
	    
	/* To search an element, use std::set::find member method and check iterator. 
	Why std::set::find member method instead of std::find standard generic algorithm?
	Because find member function knows its internal data structure is balance binary search 
	tree and hence designed to operate on that only therefore it will take much lesser time 
	then standard algorithm std::find.*/
    std::set<std::string>::iterator it = setOfNumbers.find("second");
	if(it != setOfNumbers.end())
		std::cout<<"'second'  found"<<std::endl;
	else
		std::cout<<"'second' not found"<<std::endl;
		
	return 0;
}

std::set<int> setOfNumbers;
void checkAndInsert(int num)
{
  if(setOfNumbers.insert(num).second)
     std::cout<<"Number "<<num<<" inserted sucessfuly\n";
 else
     std::cout<<"Number "<<num<<" was already present in set\n";
 
}
int main_verify_insertion()
{
    checkAndInsert(2);
    checkAndInsert(3);
    checkAndInsert(2);
    checkAndInsert(1);
 
   /* Check the size of set */
   std::cout<< "set size: " << setOfNumbers.size()<<std::endl;
 
   /* Iterate through all the elements in a set and display the value. */
   for (std::set<int>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
      std::cout << *it << endl;
   std::cout<<"\n";
 return 0;
}


int main()
{
 
	std::set<std::string> setOfNumbers;
 
	/* Lets insert four elements */
	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");
	setOfNumbers.insert("first");
 
	/* Iterate through all the elements in a set and display the value. */
	for (std::set<std::string>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<std::endl;
 
	setOfNumbers.erase("third");
 
	/* Iterate through all the elements in a set and display the value. */
	for (std::set<std::string>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
		    std::cout << ' ' << *it;
 
	std::cout<<std::endl;
	return 0;
}

