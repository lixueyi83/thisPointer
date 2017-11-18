/*************************************************************************
	> File Name: stl_map.cpp
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
    Benefits of using std::map :
    1. It stores only unique keys and that too in sorted order based on its assigned sorting criteria.
    2. As keys are in sorted order therefore searching element in map through key is very fast i.e. it takes logarithmic time.
    3. In std::map there will be only one value attached with the every key.
    4. std::map can be used as associative arrays.
    5. It might be implemented using balanced binary trees.

*/
int main_basics()
{
    std::map<std::string, int> mapOfWords;
    
    /* Inserting data in std::map */
    mapOfWords.insert(std::make_pair("earth", 1));
    mapOfWords.insert(std::make_pair("moon", 2));
    mapOfWords["sun"] = 3;
    
    /* Will sliently change/replace the value of already added key i.e. earth */
    mapOfWords["earth"] = 4;
    
    /*  insert will not replace already added key instead it returns the information */
    mapOfWords.insert(std::make_pair("sun", 0));
    
    /* Iterate through all elements in std::map */
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        std::cout << it->first << " :: " << it->second <<std::endl;
        it++;
    }
    
    cout << "------------------------------------------------" << endl;
    
    /* Check if insertion is successful or not */
    if(mapOfWords.insert(std::make_pair("earth", 1)).second == false)
    {
        std::cout<<"Element with key 'earth' already existed"<<std::endl;
    }
    
    /* Searching element in std::map by key. */
    if(mapOfWords.find("sun") != mapOfWords.end())
        std::cout<<"word 'sun' found"<<std::endl;
        
    if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl;
        
    /* print map */
    for(auto x : mapOfWords)
        cout << x.first << " :: " << x.second <<std::endl;
        
    cout << "------------------------------------------------" << endl;
        
    /* Erasing By iterator */
    std::map<std::string, int>::iterator ite = mapOfWords.find("moon");
    mapOfWords.erase(ite);
 
     /* print map */
    for(auto x : mapOfWords)
        cout << x.first << " :: " << x.second <<std::endl;
 
    /* Erasing By Key */
    mapOfWords.erase("earth");
    
    cout << "------------------------------------------------" << endl;
    
    /* print map */
    for(auto x : mapOfWords)
        cout << x.first << " :: " << x.second <<std::endl;
        
    return 0;
}

/***********************************************************************
    Map and External Sorting Criteria / Comparator
    
*/
struct WordGreaterComparator
{
    bool operator()(const std::string & left, const std::string & right) const
    {
        return (left > right);
    }
};
 
int main_external_sort_criteria()
{
    std::cout<<"Default sorting criteria for keys i.e. operator < for std::string: "<<std::endl;
    std::map<std::string, int > mapOfWords;
 
    mapOfWords.insert(std::make_pair("earth", 1));
    mapOfWords.insert(std::make_pair("moon", 2));
    mapOfWords.insert(std::make_pair("sun", 3));
 
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    for( ; it != mapOfWords.end(); it++)
        std::cout<< "\t" << it->first << " :: " << it->second << std::endl;
 
    std::cout<<"\nExternal sorting criteria for keys: "<<std::endl;
    std::map<std::string, int, WordGreaterComparator > mapOfWords_2;
 
    mapOfWords_2.insert(std::make_pair("earth", 1));
    mapOfWords_2.insert(std::make_pair("moon", 2));
    mapOfWords_2.insert(std::make_pair("sun", 3));
    for(std::map<std::string, int>::iterator it = mapOfWords_2.begin(); it != mapOfWords_2.end(); it++)
        std::cout<< "\t" << it->first << " :: " << it->second << std::endl;
 
    /*
         Compile Error as 2 std::map objects have different sorting criteria0
    if(mapOfWords == mapOfWords_2)
         std::cout<<"Maps are same"<<std::endl;
    */
 
    return 0;
}

/*************************************************************************
    Using User defined class objects as keys in std::map
    
    By default std::map uses “operator <” as sorting criteria for keys. For default data types 
    like int and std::string etc, operator < is available by default but for User defined classes 
    operator < is not available by default. Therefore, to use user defined class objects as keys 
    in std::map we should have either,
        1. Default sorting criteria i.e. operator < defined for our Class.
        2. std::map should be assigned with an external sorting criteria i.e. comparator that can 
           compare two objects of your user defined class.
*/

class User
{
	std::string m_id;
	std::string m_name;
public:
	User(std::string name, std::string id) :
			m_id(id), m_name(name)
	{
	}
	const std::string& getId() const
	{
		return m_id;
	}
	const std::string& getName() const
	{
		return m_name;
	}
	bool operator<(const User& userObj) const
	{
		if (this->m_id < userObj.m_id)
			return true;
	}
};
 
void example_1()
{
	std::map<User, int> m_UserInfoMap;
 
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "3"), 100));
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "1"), 120));
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.Z", "2"), 300));
 
	std::map<User, int>::iterator it = m_UserInfoMap.begin();
	for (; it != m_UserInfoMap.end(); it++)
	{
		std::cout << it->first.getId() << ": " << it->first.getName() << " :: " << it->second << std::endl;
	}
}
struct UserNameComparator
{
	bool operator()(const User &left, const User &right) const
	{
		return (left.getName() > right.getName());
	}
};
 
void example_2()
{
	std::map<User, int, UserNameComparator> m_UserInfoMap;
 
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "3"), 100));
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "1"), 120));
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.Z", "2"), 300));
	m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.Y", "2"), 300));
 
	std::map<User, int, UserNameComparator>::iterator it =
			m_UserInfoMap.begin();
	for (; it != m_UserInfoMap.end(); it++)
	{
		std::cout << it->first.getName() << " :: " << it->second << std::endl;
	}
}
int main_use_defined_class()
{
	std::cout << "EXAMPLE 1 :: Comparing by ID" << std::endl;
	example_1();
	std::cout << "EXAMPLE 1 :: Comparing by NAME" << std::endl;
	example_2();
	return 0;
}

/*******************************************************************************
    Set vs Map : How to choose a right associative container ?
    
    Set:
        1. Set is an associative container which we need to store unique elements.
        2. It always keeps the elements in sorted order.
        3. Internally it maintains a balanced binary search tree of elements. Therefore when we search 
           an element inside the set then it takes only log(n) complexity to search it.
        4. Each element added inside the set is const i.e. you cannot modify that element, because if 
           you could, then it would hamper set’s internal data structure i.e. it will lose its internal 
           balanced binary search tree property and results in undefined behavior.
           
    Map:
        1. Map is a associative container that is used to store key-value pair of elements with unique keys.
        2. It always keeps the inserted pairs in sorted order based on the key.
        3. Internally it maintains a balanced binary search tree to store keys. (log(n) for searching)
        4. We cannot modify the key of any inserted pair in map.
        5. We can modify the value associated with a key in any inserted pair in map.
*/

void example1()
{
	std::set<std::string> setOfDepartments;
 
	setOfDepartments.insert("First");
	setOfDepartments.insert("Second");
	setOfDepartments.insert("Third");
	
	std::for_each(setOfDepartments.begin(), 
	              setOfDepartments.end(), 
	              [](std::string elem){ std::cout << (elem) << " , "; });
 
	/* Now Try to change the element */
	 std::set<std::string>::iterator it = setOfDepartments.find("Second");
	 if(it != setOfDepartments.end())
	 {
		 std::cout << std::endl<< *it;
		 //*it = "Fourth"; // NOT ALLOWED
	 }
	 cout << endl;
 
}
int main_set()
{
	example1();
	return 0;
}

void example2()
{
	/* Map of Department and Employee count in that Department */
	std::map<std::string, int > mapOfDepEmpCount;
 
	mapOfDepEmpCount.insert(std::make_pair("First", 0));
	mapOfDepEmpCount.insert(std::make_pair("Second", 0));
	mapOfDepEmpCount.insert(std::make_pair("Third", 0));
 
	std::map<std::string, int >::iterator it = mapOfDepEmpCount.find("Second");
	 if(it != mapOfDepEmpCount.end())
	 {
		 std::cout << "Department = "<< it->first << " :: No. Of Employees = " << it->second << std::endl;
		 it->second = 10;  /* You can change the value associated with the key */
		 /* it->first = "sss"; You cannot chage the key */
	 }
 
	 it = mapOfDepEmpCount.find("Second");
	 if(it != mapOfDepEmpCount.end())
	 {
		 std::cout << "Department = "<< it->first << " :: No. Of Employees = " << it->second << std::endl;
	 }
}
 
int main_map()
{
	example2();
	return 0;
}

/*****************************************************************************************
    How to Insert elements in a map
    
    Map internally store elements in a pair of key value i.e.
        	
        pair<iterator,bool> insert (const value_type& element);
        
    It accepts an object of key value pair and returns an pair of map iterator and bool.
*/
void testResult(std::pair<std::map<std::string, int>::iterator, bool> & result) 
{
	/* Check if Insertion was successful */
	if(result.second == false) 
	{
		/* Insertion Failed */
		std::cout << "Failed to add . duplicate key: " << result.first->first << std::endl;
	} 
	else 
	{
		/* Insertion was successful */
		std::cout << "Successful in Adding key: " << result.first->first << std::endl;
	}
}
 
int main_insert_element_into_map() 
{
	/* Map of string and int */
	std::map<std::string, int> mapOfWordCount;
 
	/* Pair of Map Iterator and bool */
	std::pair<std::map<std::string, int>::iterator, bool> result;
 
	/* Insert Element in map */
	result = mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
	
	testResult(result);
 
	/* Insert Element in map */
	result = mapOfWordCount.insert(std::pair<std::string, int>("second", 2));

	testResult(result);
 
	/* Insert Element in map */
	result = mapOfWordCount.insert(std::pair<std::string, int>("third", 3));

	testResult(result);
 
	/* Try to add duplicate element */
	result = mapOfWordCount.insert(std::pair<std::string, int>("third", 4));

	testResult(result);
 
	/* Create a map iterator and point to beginning of map */
	std::map<std::string, int>::iterator it = mapOfWordCount.begin();
 
	std::cout << "*****************************" << std::endl;
	
	/* Iterate over a map using std::for_each and Lambda function */
	std::for_each(mapOfWordCount.begin(), mapOfWordCount.end(),
			[](std::pair<std::string, int> element) 
			{
				/* Accessing KEY::VALUE from element */
				std::string word = element.first;
				int count = element.second;
				std::cout<< word << " :: " << count << std::endl;
			});
 
	return 0;
}

/*****************************************************************************************
    How to Iterate over a map in C++
    
    1. Iterate over a map using STL Iterator
    2. Iterating over the map using C++11 range based for loop
    3. Iterating over the map using std::for_each and lambda function
    
    Reverse Iterate: 
    To Iterate a map in reverse order we will use reverse_iterator of map i.e.
    Reverse Iterator of map moves in backward direction on increment. So, we will point the 
    reverse_iterator to the last element of map and then keep on incrementing it until it 
    reaches the first element. To do this we will use 2 member functions of std::map i.e.
    
    std::map::rbegin() returns the reverse_iterator pointing to last element of map.
    std::map::rend() returns the reverse_iterator pointing to first element of map.
*/

int main_interate_1() 
{ 
	std::map<std::string, int> mapOfWordCount;
	/* Insert Element in map, if already exist then insert fails */
	mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
	mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 5));
 
	/* Create a map iterator and point to beginning of map */
	std::map<std::string, int>::iterator it = mapOfWordCount.begin();
 
	/* Iterate over the map using Iterator till end. */
	while (it != mapOfWordCount.end())
	{
		/* Accessing KEY::VALUE from element pointed by it. */
		std::string word = it->first;
		int count = it->second;
		std::cout << word << " :: " << count << std::endl;
 
		/* Increment the Iterator to point to next entry */
		it++;
	}
	return 0;
}

int main_interate_2() 
{
	std::map<std::string, int> mapOfWordCount;
	/* Insert Element in map */
	mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
	mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 5));
 
	/* Create a map iterator and point to beginning of map */
	std::map<std::string, int>::iterator it = mapOfWordCount.begin();
 
	// Iterate over the map using c++11 range based for loop
	for (std::pair<std::string, int> element : mapOfWordCount) 
	{
		// Accessing KEY::VALUE from element
		std::string word = element.first;
		int count = element.second;
		std::cout << word << " :: " << count << std::endl;
	}
 
	return 0;
}

int main_interate_3() 
{ 
	std::map<std::string, int> mapOfWordCount;
	/* Insert Element in map */
	mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
	mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
	mapOfWordCount.insert(std::pair<std::string, int>("third", 5));
 
	/* Create a map iterator and point to beginning of map */
	std::map<std::string, int>::iterator it = mapOfWordCount.begin();
 
	/* Iterate over a map using std::for_each and Lambda function */
		std::for_each(mapOfWordCount.begin(), mapOfWordCount.end(),
				[](std::pair<std::string, int> element){
					// Accessing KEY::VALUE from element
					std::string word = element.first;
					int count = element.second;
					std::cout<<word<<" :: "<<count<<std::endl;
		});
 
	return 0;
}

int main_reverse_iterate() 
{
	/* Creating & Initializing a map of String & Ints */
	std::map<std::string, int> mapOfWordCount = 
	{
			{ "aaa", 10 },
			{ "ddd", 11 },
			{ "bbb", 12 },
			{ "ccc", 13 }
	};
 
	/* Create a map iterator and point to the end of map */
	std::map<std::string, int>::reverse_iterator it = mapOfWordCount.rbegin();
 
	/* Iterate over the map using Iterator till beginning. */
	while (it != mapOfWordCount.rend()) 
	{
		/* Accessing KEY::VALUE from element pointed by it. */
		std::string word = it->first;
		int count = it->second;
		std::cout << word << " :: " << count << std::endl;
 
		/* Increment the Iterator to point to next entry */
		it++;
	}
 
	return 0;
}






