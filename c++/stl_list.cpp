/*************************************************************************
	> File Name: stl_list.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <list>
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
    What is std::list ?
    std::list is sequential STL container that is internally implemented as doubly linked list.
    i.e. every element in the list is stored at a seperate memory location i.e. called node and 
    it also contains a pointer to the previous and next node.
*/

int main_list_basic()
{
    std::list<int> listOfNumbers;
 
    /* Inserting elements at end in list */
    listOfNumbers.push_back(5);
    listOfNumbers.push_back(6);
 
    /* Inserting elements at front in list */
    listOfNumbers.push_front(2);
    listOfNumbers.push_front(1);
 
    /* Iterating over list elements and display them */
    std::list<int>::iterator it = listOfNumbers.begin();
    while(it != listOfNumbers.end())
    {
        std::cout<<(*it)<<"  ";
        it++;
    }
    std::cout<<std::endl;
 
    /* Inserting elements in between the list using insert(pos,elem) member function. 
    Let's iterate to 3rd position */
    it = listOfNumbers.begin();
    it++;
    it++;
    /* Iterator 'it' is at 3rd position */
    listOfNumbers.insert(it, 4);
 
 
    /* Iterating over list elements and display them */
    it = listOfNumbers.begin();
    while(it != listOfNumbers.end())
    {
        std::cout<<(*it)<<"  ";
        it++;
    }
    std::cout<<std::endl;
 
 
    /* Erasing elements in between the list using erase(position) member function. 
       Let's iterate to 3rd position */
    it = listOfNumbers.begin();
    it++;
    it++;
    /* Iterator 'it' is at 3rd position. Now erase this element */
    listOfNumbers.erase(it);
 
 
    /* Iterating over list elements and display them */
    it = listOfNumbers.begin();
    while(it != listOfNumbers.end())
    {
        std::cout<<(*it)<<"  ";
        it++;
    }
    std::cout<<std::endl; 
    /* Lets remove all elements with value greater than 3 */ 
    listOfNumbers.remove_if([](int elem){ 
                if(elem > 3)
                    return true;
                else
                    return false;
            });
 
    it = listOfNumbers.begin();
    while(it != listOfNumbers.end())
    {
        std::cout<<(*it)<<"  ";
        it++;
    }
    std::cout<<std::endl;
 
    return 0;
}

/************************************************************************************
    Difference between Vector and List in C++
    
    Both vector and list are sequential containers of C++ Standard Template Library.
    List stores elements at non contiguous memory location i.e. it internally uses a 
    doubly linked list. Whereas, vector stores elements at contiguous memory locations 
    like an array i.e.
    
    1.) Insertion and Deletion
        Insertion and Deletion in List is very efficient as compared to vector because 
        to insert an element in list at start, end or middle, internally just a couple 
        of pointers are swapped. Whereas, in vector insertion and deletion at start or 
        middle will make all elements to shift by one. Also, if there is insufficient 
        contiguous memory in vector at the time of insertion, then a new contiguous 
        memory will be allocated and all elements will be copied there.
        >>>> So, insertion and deletion in list is much efficient than vector in c++.
        
    2.) Random Access:
        As List is internally implemented as doubly linked list, therefore no random 
        access is possible in List. It means, to access 15th element in list we need 
        to iterate through first 14 elements in list one by one. Whereas, vector stores 
        elements at contiguous memory locations like an array. Therefore, in vector 
        random access is possible i.e. we can directly access the 15th element in vector 
        using operator [] i.e.
        So, we can not use std::list with some of the STL algorithm that needs the 
        random access operators like std::sort.
        
    3.) Iterator Invalidation
        Deleting or Inserting an element in List does not invalidate any iterator 
        because during insertion and deletion no element is moved from its position 
        only a couple pointers are changed.
        Whereas, in vector insertion and deletion can invalidate the iterators.
        
    4.) Special Member functions
        As std::list do not provide random access, there many STL algorithms that 
        uses Random Access Iterators can not be used with List. Hence std::list 
        provides some extra functions for Sorting, Splicing, Removing elements and 
        identifying unique elements.
        
        Vector provides the random access and hence can be used with STL algorithms 
        that uses Random Access Iterators.
*/

/***********************************************************************************
    Different ways to Initialize a list in C++
*/

int main_init_list()
{
    std::list<int> listOfInts1;
    
    /* 1. push_back */
    for (int i = 0; i < 10; i++)
		listOfInts1.push_back(i);
		
    /* 2. fill constructor */
    std::list<int> listOfInts2(5, 119);
    
    /* 3. initializer_list */
    std::list<int> listOfInts3({2,8,7,5,3,1,4});
    
    /* 4. with a std::vector or an Array */
    std::vector<int> vecOfInt( { 5, 2, 8, 7, 5, 3, 1, 4 });
    std::list<int> listOfInts4(vecOfInt.begin(), vecOfInt.end());
    
    /* print items in list */
    copy(listOfInts4.begin(), listOfInts4.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    return 0;
}

/*************************************************************************************
    How to erase elements from a list in c++ using iterators
*/
int main_erase() 
{
	/* Create a list and initialize it with 7 elements */
	std::list<int> listOfInts( { 2, 11111, 4, 6, 4, 9, 1, 2, 8, 9, 4, 6, 2, 4, 9 });
 
	/* Display The List */
	std::copy(listOfInts.begin(), listOfInts.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
 
	/* Iterator itList points to element next to begin */
	std::list<int>::iterator itList = listOfInts.begin();
 
	/* Erasing element represented by iterator itList i.e. 3 */
	itList = listOfInts.erase(++itList);
 
	/* Display The List */
	std::copy(listOfInts.begin(), listOfInts.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
 
	/* Increment iterator */
	itList++;
 
	/* Erase a range of elements i.e. 6 to end */
	listOfInts.erase(itList, listOfInts.end());
 
	/* Display The List */
	std::copy(listOfInts.begin(), listOfInts.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
 
	return 0;
}

/**************************************************************************************
    Remove elements from a List based on value or External Criterion
*/

int main_remove() 
{
	/* Create a list and initialize it with 7 elements */
	std::list<int> listOfInts( { 2, 3, 4, 6, 4, 9, 1, 2, 8, 9, 4, 6, 2 });
	
	/* print list */
	copy(listOfInts.begin(), listOfInts.end(), ostream_iterator<int>(cout, " "));
	std::cout << std::endl;
 
	/* Remove all elements with value 4 */
	listOfInts.remove(4);
 
	/* print list */
	copy(listOfInts.begin(), listOfInts.end(), ostream_iterator<int>(cout, " "));
	std::cout << std::endl;
	
	listOfInts.remove_if([](const int & val){
		if(val >= 2 && val < 5)
		return true;
		else
		return false;
	});
 
 	/* print list */
	copy(listOfInts.begin(), listOfInts.end(), ostream_iterator<int>(cout, " "));
	std::cout << std::endl;
	
    std::list<int>::iterator it = listOfInts.begin();
	while (it != listOfInts.end()) {
		if ((*it) % 3 == 0) {
			/*  
			    listOfInts.erase(it); this is wrong, because erase() will make 
			    the passed iterator invalid. But erase() returns the iterator to the 
			    next of deleted element.		   
			   */
			it = listOfInts.erase(it);  /* make sure to use the return value of erase() to continue the loop*/
		} else
			it++;
	}
 
	/* Iterate over the list using for_each & Lambda Function and display contents */
	std::for_each(listOfInts.begin(), listOfInts.end(), [](const int & val){
		std::cout<<val<<" ";
	});
	cout << endl;
	
	return 0;
}


/**********************************************************************************
    C++ List – Find | Contains : How to search an element in std::list ?
*/

/*-------------------------------------------------------------------------------
 * Generic function to find if an element of any type exists in list
 */
template <typename T>
bool contains(std::list<T> & listOfElements, const T & element)
{
	// Find the iterator if element in list
	auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
	//return if iterator points to end or not. It points to end then it means element
	// does not exists in list
	return it != listOfElements.end();
}

int main()
{
	std::list<std::string> listOfStrs = {"is", "of", "the", "Hi", "Hello", "from" };
 
	/* Create a list Iterator */
	std::list<std::string>::iterator it;
 
	/* Fetch the iterator of element with value 'Hello' */
	it = std::find(listOfStrs.begin(), listOfStrs.end(), "Hello");
 
	/* Check if iterator points to end or not */
	if(it != listOfStrs.end())
		std::cout<<"'Hello' exists in list "<<std::endl;
	else
		std::cout<<"'Hello' does not exists in list"<<std::endl;
 
    /* use generic function to search */
    bool result = contains(listOfStrs, std::string("is"));
	std::cout << result << std::endl;
}

