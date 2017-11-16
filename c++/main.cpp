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
*/
























