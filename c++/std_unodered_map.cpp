/*************************************************************************
	> File Name: stl_unordered_map.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <iterator>
#include <list>
#include <string>
#include "debug.h"

using namespace std;

/*************************************************************************
    Unordered_map provides a functionality of map i.e. it store the elements 
    in key value pair and with unique key only. Unordered_map internally uses 
    the hashing to achieve this. It internally uses a hash table to implement 
    this hashing feature. In an unordered_map elements are stored in a key 
    value pair combination. But elements are stored in arbitrary order unlike
    associative containers where elements were stored in sorted order of keys.
    
    Advantage of Unordered_map:
    The basic advantage of using unordered_map instead of associative map is 
    the searching efficiency. In an unordered_map complexity to search for 
    an element is O(1) if hash code are chosen efficiently.
    
    Different Ways to initialize an unordered_map:
    unordered_map provides different overloaded constructors. We will use some 
    of them to initialize an unordered_set in 3 different ways i.e.
        1. Initializing through an initializer_list
        2. Initializing through a iterable range
        3. Initializing through an another map
        
    Find an element in unordered_map:  
        iterator find ( const key_type& k );
      
    Insert elements in an unordered_map:
        1. Inserting multiple elements in unordered_map through an initializer_list
        2. Inserting a single element in an unordered_map and check result
*/

int main_init_insert_find()
{
	/* 1. Initialize an unordered_map through initializer_list */
	std::unordered_map<std::string, int> wordMap(
	{{ "First", 1 }, { "Second", 2 }, { "Third", 3 }});
 
	/* Iterate over an unordered_map and display elements */
	for (std::pair<std::string, int> element : wordMap)
		std::cout << element.first << " :: " << element.second << std::endl;
 
	std::cout << "*******************" << std::endl;
 
	/* 2. Initialize an unordered_map through another range of elements of 
	      type std::pair */
	std::unordered_map<std::string, int> wordMap_2(wordMap.begin(),
			wordMap.end());
 
	/* Iterate over an unordered_map and display elements */
	for (std::pair<std::string, int> element : wordMap_2)
		std::cout << element.first << " :: " << element.second << std::endl;
 
	std::cout << "*******************" << std::endl;
 
	/* 3. Initialize an unordered_map through other unordered_map */
	std::unordered_map<std::string, int> wordMap_3(wordMap);
 
	/* Iterate over an unordered_map and display elements */
	for (std::pair<std::string, int> element : wordMap_3)
		std::cout << element.first << " :: " << element.second << std::endl;
		
	std::cout << "*******************" << std::endl;
		
 	/* 3. search element: Declare an iterator to unordered_map */
	std::unordered_map<std::string, int>::iterator it;   
	it = wordMap.find("First");
	
	if(it != wordMap.end())
	{
	    std::cout << "Element Found - " << it->first << "::" << it->second << endl; 
	}
	else 
	{
	    std::cout << "Element Not Found" << endl;
	}
	
	std::cout << "*******************" << std::endl;
	
	/* 4. Insert elements through an initializer list */
	wordMap.insert({ {"*First", 1}, {"*Second", 2}, {"*Third", 3} });
	
	/* Iterate over an unordered_map and display elements */
	for (std::pair<std::string, int> element : wordMap)
		std::cout << element.first << " :: " << element.second << std::endl;
 
	return 0;
}

/********************************************************************************
* Erase element
*  1. by key;
*  2. by iterator;
*
********************************************************************************/
int main_erase()
{
    cout << "-----------------------------------------------" << endl;

    std::unordered_map<std::string, int> wordMap(
        {
            {"First", 1},
            {"second", 2},
            {"third", 3},
            {"fourth", 4},
            {"fifth", 5}
        });

    for(std::pair<std::string,int> element : wordMap)
    {
        std::cout << element.first << "::" << element.second << endl;
    }

    cout << "-----------------------------------------------" << endl;

    /* erase element by key */
    if(wordMap.erase("second") == 1)
    {
        std::cout << "\t *** erase second" << endl;
    }

    for(std::pair<std::string,int> element : wordMap)
    {
        std::cout << element.first << "::" << element.second << endl;
    }
    
    cout << "-----------------------------------------------" << endl;

    /********** by iterator ************/
    std::unordered_map<string, int>::iterator it = wordMap.find("third");
    if(it != wordMap.end())
    {
        wordMap.erase(it);
        std::cout << "\t *** erased third" << endl;
    }

    cout << "-----------------------------------------------" << endl;

    for(std::pair<std::string,int> element : wordMap)
    {
        std::cout << element.first << "::" << element.second << endl;
    }
    
    cout << "-----------------------------------------------" << endl;

    return 0;
}

int main() 
{
	/* Initialize an unordered_map through initializer_list */
	std::unordered_map<std::string, int> wordMap( 
        { 
            { "First", 1 }, 
            { "Second", 2 }, 
            { "Third", 3 }, 
            { "Fourth", 4 }, 
            { "Fifth", 5 } });
 
	for (auto element : wordMap)
		std::cout << element.first << " :: " << element.second << std::endl;
    cout << "-------------------------------------------------" << endl;

	/* Iterator pointing to first element in map */
	std::unordered_map<std::string, int>::iterator it = wordMap.begin();
 
	/* Erase all element whose key starts with letter 'F' in an iteration */
	while (it != wordMap.end()) 
    {
		/* Check if key's first character is F */
		if (it->first[0] == 'F') 
			/* erase() function returns the iterator of the next to last deleted element. */
			it = wordMap.erase(it);
		else
			it++;
	}
 
	for (auto element : wordMap)
		std::cout << element.first << " :: " << element.second << std::endl;
 
	return 1;
}

/*************************************************************************************
 * map vs unordered_map:
 *
 * http://thispointer.com/map-vs-unordered_map-when-to-choose-one-over-another/
* ***********************************************************************************/












