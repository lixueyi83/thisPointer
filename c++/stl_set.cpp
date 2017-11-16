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
 
	/* Iterate through all the elements in a set and display the value in sorted order. 
	   It will display: aaaaa ccccc ddddd first second third 
	*/
	for (std::set<std::string>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
	    std::cout << *it << " ";
	cout << endl;
	    
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


int main_set_iteration()
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

/***********************************************************************************************
C++ std::set example and tutorial with user defined classe
    If you want to use std::set with user defined classes and use default sorting criteria 
    then overload operator < in the class.
*/
class Message1
{
public:
	std::string m_MsgContent;
	std::string m_sentBy;
	std::string m_recivedBy;
 
	Message1(std::string sentBy, std::string recBy, std::string msg) :
		m_MsgContent(msg), m_sentBy(sentBy), m_recivedBy(recBy)
	{}
 
	bool operator< (const Message1 & msgObj) const
	{
		std::string rightStr = 	msgObj.m_MsgContent + msgObj.m_sentBy + msgObj.m_recivedBy;
		std::string leftStr = 	this->m_MsgContent + this->m_sentBy + this->m_recivedBy;
		return (leftStr < rightStr);
	}
	friend std::ostream& operator<<(std::ostream& os, const Message1& obj);
 
};

std::ostream& operator<<(std::ostream& os, const Message1& obj)
{
	os<<obj.m_sentBy<<" :: "<<obj.m_MsgContent<<" :: "<<obj.m_recivedBy<<std::endl;
	return os;
}

int main_overload_default_comparator()
{
	std::set<Message1> setOfMsgs;
 
	Message1 msg1("user_1", "Hello", "user_2");
	Message1 msg2("user_1", "Hello", "user_3");
	Message1 msg3("user_3", "Hello", "user_1");
	/* A Duplicate Message1 which will not be inserted */
	Message1 msg4("user_1", "Hello", "user_3");
 
	setOfMsgs.insert(msg1);
	setOfMsgs.insert(msg2);
	setOfMsgs.insert(msg3);
	setOfMsgs.insert(msg4);

	for (std::set<Message1>::iterator it=setOfMsgs.begin(); it!=setOfMsgs.end(); ++it)
	    std::cout << *it ;
 
	return 0;
}

/********************************************************************************************
    c++ std::set example and tutorial with external Sorting criteria | Comparator
    
    Requirement:
    we want to keep only single message sent by each user i.e. only one sent message 
    is allowed per user and we can’t modify operator <.
*/
class Message2
{
public:
	std::string m_MsgContent;
	std::string m_sentBy;
	std::string m_recivedBy;
 
	Message2(std::string sentBy, std::string recBy, std::string msg) :
		m_MsgContent(msg), m_sentBy(sentBy), m_recivedBy(recBy)
	{}
	friend std::ostream& operator<<(std::ostream& os, const Message2& obj);
 
};
std::ostream& operator<<(std::ostream& os, const Message2& obj)
{
	os<<obj.m_sentBy<<" :: "<<obj.m_MsgContent<<" :: "<<obj.m_recivedBy<<std::endl;
	return os;
}

class MessageUserComparator
{
	std::string m_userName;
public:
	MessageUserComparator(std::string userName) :
		m_userName(userName)
	{}
	bool operator() (const Message2& msg1, const Message2& msg2) const
	{
		if(msg1.m_sentBy < msg2.m_sentBy )
			return true;
		else
			return false;
	}
};

int main_external_comparator()
{
 
	Message2 msg1("user_1", "Hello", "user_2");
	Message2 msg2("user_1", "Hello", "user_3");
	Message2 msg3("user_3", "Hello", "user_1");
	Message2 msg4("user_1", "Hello", "user_3");
 
	/* std::set that contains the messages sent by user - "user_1" */
	std::cout<<"set that contains the messages sent by user - user_1"<<std::endl;
	std::set<Message2, MessageUserComparator> setOfMsgs_1(MessageUserComparator("user_1"));
 
	setOfMsgs_1.insert(msg1);
	setOfMsgs_1.insert(msg2);
	setOfMsgs_1.insert(msg3);
	setOfMsgs_1.insert(msg4);
	
	/*  msg1, msg2 and msg4 are duplicates according to MessageUserComparator implementation
	    hence only 2 element are actually inserted in std::set
	    Iterate through all the elements in a set and display the value.
	*/
		for (std::set<Message2>::iterator it=setOfMsgs_1.begin(); it!=setOfMsgs_1.end(); ++it)
		    std::cout << *it ;
 
	return 0;
}

/******************************************************************8
    How to Access Element by index in a Set | C++
    
    std::set is an associative container, which internally store elements in a balanced 
    binary search tree and it doesn’t provide random access operator [].
    
    Therefore accessing a random element from set by index is little tricky.
    
    Suppose we have below set:
    std::set<std::string> setOfStr = { "bb", "ee", "dd", "aa", "ll" }; and inside the set 
    elements will be stored in sorted order: aa bb dd ee ll.
    
    To access an element at nth index we need to create an iterator pointing to starting 
    position and keep on  increment the iterator till nth element is reached. 
    STL provides two algorithms which serves the same purpose: std::advance & std::next.
    
    std::advance accepts an iterator and a value by which it advances the given iterator.

        std::set<std::string>::iterator iter = setOfStr.begin();
        std::advance(iter, 3);
        std::cout<<"3rd Element in set = "<<*iter<<std::endl;
        
    std::next
        // std::next internally iterate through n elements to reach nth
        // element and returns the iterator of 3rd element in the set
        std::set<std::string>::iterator it = std::next(setOfStr.begin(), 3);
        std::cout<<"3rd Element in set = "<<*it<<std::endl;
*/

/*
 * Access nth element from a set.
 * It returns a pair of Element and bool.
 * bool represents if nth element exists in set or not.
 * if bool is true them First element of pair T contains the element value
 */
template <typename T>
std::pair<T, bool> getNthElement(std::set<T> & searchSet, int n)
{
	std::pair<T, bool> result;
	if(searchSet.size() > n )
	{
		result.first = *(std::next(searchSet.begin(), n));
		result.second = true;
	}
	else
		result.second = false;
 
	return result;
}
 
int main_access_element_by_index()
{
	std::set<std::string> setOfStr =
				{ "bb", "ee", "dd", "aa", "ll" };
 
	std::cout<<"***** Set Contents *****"<<std::endl;
	for(std::string elem : setOfStr)
		std::cout << elem << " ";
    cout << endl;
 
	std::cout<<"***** Accessing Elements by Index ***"<<std::endl;
 
	// Access 3rd element
	std::pair<std::string, bool> result = getNthElement(setOfStr, 3);
 
	if(result.second)
		std::cout<<"3rd Element in set = "<<result.first<<std::endl;
	else
		std::cout<<"3rd Element in set not found"<<std::endl;
 
 
	// Access 7th element
	result = getNthElement(setOfStr, 7);
 
	if(result.second)
		std::cout<<"7th Element in set = "<<result.first<<std::endl;
	else
		std::cout<<"7th Element in set not found"<<std::endl;
}

/*****************************************************************
    C++ : Different ways to insert elements in Set
    
    Set provides 3 different overloaded version of insert() function to add element in set.
        1. Inserting a Single element in Set and checking the result
        2. Inserting an Iterator Range into a Set
        3. Inserting a Initializer List in Set
    
    Set is an associative container and contains only unique elements, therefore an insertion 
    in set can fail if a similar element is already present in set. Keeping that in mind set 
    provides a version of member function insert() i.e.
*/

void insertInSet(std::set<std::string> & setOfStrs, std::string str)
{
	// A pair of set iterator and bool
	std::pair<std::set<std::string>::iterator, bool> result;
 
	// Insert Returns a pair of iterator and bool
	result = setOfStrs.insert(str);
 
	// Check if element added sucessfuly
	if(result.second)
		std::cout<<str<<" - Inserted sucessfuly"<<std::endl;
	else
		std::cout<<str<<" - Not Inserted sucessfuly"<<std::endl;
 
}
 
int main_insert_one_element_into_set()
{
	std::set<std::string> setOfStrs;
 
 
	insertInSet(setOfStrs, "Hi");
	// Try to insert the duplicate element.
	insertInSet(setOfStrs, "Hi");
 
	insertInSet(setOfStrs, "the");
	insertInSet(setOfStrs, "is");
	insertInSet(setOfStrs, "Hello");
 
	std::cout<<"**Map Contents***"<<std::endl;
 
	for(auto elem : setOfStrs)
		std::cout<<elem<<std::endl;
 
	return 0;
}

int main_insert_range_into_set()
{
	std::vector<std::string> vecOfStrs = {"Hi", "Hello", "is", "the", "at", "Hi", "is"};
 
	std::set<std::string> setOfStrs;
 
	// Insert a Range in set
	// Range here is start and end iterators of a vector
	setOfStrs.insert(vecOfStrs.begin(), vecOfStrs.end());
 
	// It will insert all the elements in vector to set, but as
	// set contains only unique elements, so duplicate elements will
	// be automatically rejected.
 
	// But there is no way to find out how many actually inserted
	// because it doesn't return any value.
 
	std::cout<<"**Map Contents***"<<std::endl;
 
	for(auto elem : setOfStrs)
		std::cout<<elem<<std::endl;
 
	return 0;
}

int main_insert_initializer_list_in_set()
{
	std::set<std::string> setOfStrs;
 
	/* Insert a Initializer list in the set */
	setOfStrs.insert({"Hi", "Hello", "is", "the", "at", "Hi", "is"});
 
	/* It will insert all the elements in initializer_list to set, but as
	   set contains only unique elements, so duplicate elements will
	   be automatically rejected.
	*/
 
	/* But there is no way to find out how many actually inserted
	   because it doesn't return any value.
    */ 
 
	std::cout<<"**Map Contents***"<<std::endl;
 
	for(auto elem : setOfStrs)
		std::cout<<elem<<std::endl;
 
	return 0;
}

/****************************************************************************
    Different ways to iterate over a set in C++
*/
int main_iterate_set()
{
    /* Set of strings */
	std::set<std::string> setOfStr =
	{ "jjj", "khj", "bca", "aaa", "ddd" };
 
    /* 1. Creating a iterator pointing to start of set */
    std::cout << "*** Iterating Set in Forward Direction using Iterators"<< std::endl;
	std::set<std::string>::iterator it = setOfStr.begin();
 
    /* Iterate till the end of set */
	while (it != setOfStr.end())
	{
		std::cout << (*it) << " ";
		it++;
	}
	std::cout << std::endl << endl;
 
    /* 2. Creating a reverse iterator pointing to end of set i.e. rbegin */
    std::cout << "*** Iterating Set in Reverse Direction using Iterators"<< std::endl;
	std::set<std::string>::reverse_iterator revIt = setOfStr.rbegin();
 
    /* Iterate till the start of set i.e. rend */
	while (revIt != setOfStr.rend())
	{
		std::cout << (*revIt) << " ";
		revIt++;
	}
	std::cout << std::endl << endl;
 
    /* 3. Iterate over all elements of set using range based for loop */
    std::cout << "*** Iterating Set using range based for loop" << std::endl;
	for (auto elem : setOfStr)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl << endl;
 
    /* 4. Iterate over all elements using for_each and lambda function */
    std::cout << "*** Iterating Set using for_each algo & Lambda function" << std::endl;
	std::for_each(setOfStr.begin(), setOfStr.end(), [](const std::string & str)
	{
		std::cout<<str<<" ";
	});
	std::cout << std::endl << endl;
}

/****************************************************************************
    Different ways to Erase / Delete an element from a Set in C++
*/

int main_erase_element_from_set()
{
	/* Set Of Strings */
	//std::set<std::string> setOfStrs = {"Hi", "Hello", "is", "the", "at", "Hi", "is", "from", "that"};
	
	std::set<std::string> setOfStrs;
	setOfStrs.insert("Hi");
	setOfStrs.insert("Hello");
	setOfStrs.insert("is");
	setOfStrs.insert("the");
	setOfStrs.insert("at");
	setOfStrs.insert("is");
	setOfStrs.insert("from");
	setOfStrs.insert("that");
 
	/* Printing Contents of Set */
	std::copy (setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	/* Search for element "is" */
	std::set<std::string>::iterator it = setOfStrs.find("is");
 
	/* Check if Iterator is valid */
	if(it != setOfStrs.end())
	{
		/* Deletes the element pointing by iterator it */
		setOfStrs.erase(it);
	}
 
	/* Printing Contents of Set */
	std::copy (setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	/* Iterator pointing to "Hi" in Set */
	std::set<std::string>::iterator start = setOfStrs.find("Hi");
	/* Iterator pointing to "from" in Set */
	std::set<std::string>::iterator last = setOfStrs.find("from");
 
	/* Check if both start and last iterators are valid */
	if(start != setOfStrs.end() && last != setOfStrs.end())
	{
		/* Erase all elements from "Hi" to "from" */
		setOfStrs.erase(start, last);
	}
 
	/* Printing Contents of Set */
	std::copy (setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	/* Erase element "that" from set */
	setOfStrs.erase("that");
 
	/* Printing Contents of Set */
	std::copy (setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	return 0;
}


int main_erase_with_conditions()
{
    std::set<std::string> setOfStrs = {"Hi", "Hello", "is", "the", "at", "Hi", "is", "from", "that"};
 
	/* Printing Contents of Set */
	std::copy (setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	std::set<std::string>::iterator it = setOfStrs.begin();
 
	while(it != setOfStrs.end())
	{
		if(it->size() > 3)
		{
			/* Remove string from set if length is greater than 3 */
			it = setOfStrs.erase(it);
		}
		else
			it++;
	}
	/* Printing Contents of Set */
	std::copy (setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	return 0;
}

/*
 * Creating a generic function that will erase elements from container
 * while iterating if any given condition matches.
 *
 * It accepts following arguments
 *
 * 1.) Container i.e. set, list or vector
 * 2.) Iterator pointing to start of range
 * 3.) Iterator pointing to end of range
 * 4.) Callback to check if it needs to delete the current element
 *
 * It Iterates over the range and check if element needs to be deleted using passed checker callback.
 * If Yes then it deletes the element
 */
template <typename S, typename T>
void erase_if(S & container, T first, T last, std::function<bool (T)> checker)
{
	while(first != last)
	{
		if(checker(first))
		{
			first = container.erase(first);
		}
		else
			first++;
	}
 
}
int main()
{
 
	typedef std::set<std::string>::iterator SetIter ;
 
	std::set<std::string> setOfStrs = {"Hi", "Hello", "is", "the", "at", "Hi", "is", "from", "that"};
 
	std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	/* Callback to check if size of string is greater than 2 */
	std::function<bool (SetIter)> lambda = [](SetIter it) -> bool {
											return it->size() > 2;
										};
	/* Remove all strings from set whose length is greater than 3 */
	erase_if<>(setOfStrs, setOfStrs.begin(), setOfStrs.end(), lambda);
 
	std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout<<std::endl;
 
	return 0;
}











