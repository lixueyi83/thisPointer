/*************************************************************************
	> File Name: stl_unordered_set.cpp
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
#include <unordered_set>
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
 * how to initialize an unordered_set in c++11 
 *
 * 1. initialize an unordered_set from an array
 * 2. initialize an unordered_set by an initializer list 
 * 3. initialize an unordered_set with a vector 
*/

int main_init() 
{
    /* 1. array */
	int arr[] = { 2, 4, 6, 1, 3, 6, 8, 3, 2 };
	std::unordered_set<int> setOfNum(arr, arr + sizeof(arr) / sizeof(int));
	for (int val : setOfNum)
		std::cout << val << "  ";
	std::cout << std::endl;
 
	/* 2. initializer_list */
	std::unordered_set<int> setOfNum2( { 1, 2, 3, 1, 3, 4, 2 });
	for (int val : setOfNum2)
		std::cout << val << "  ";
	std::cout << std::endl;
 
    /* 3. vector */
	std::vector<int> vec( { 14, 5, 6, 7 });
	std::unordered_set<int> setOfNum3(vec.begin(), vec.end());
	for (int val : setOfNum3)
		std::cout << val << "  ";
	std::cout << std::endl;
}


/*************************************************************************
 * How to insert elements in an unordered_set 
 * std::pair<iterator, bool> insert(const TYPE& val);
 *
 * If an element equivalent to passed element is already present in set, then new 
 * element will not be inserted in set and ti will return the pair with following 
 * values, 
 *       - iterator wil point to the position of first matched equivalent element 
 *       - bool flag will be false: ret.second == false 
 *
 * */
 
 int main_insert() 
 {
	std::unordered_set<int> setOfNum;
 
	/* 1. Inserting few elements in set */
	setOfNum.insert(2);
	setOfNum.insert(6);
	setOfNum.insert(1);
 
	/* Declare a pair of iterator and bool flag */
	std::pair<std::unordered_set<int>::iterator, bool> result;
 
	/* Try to insert a Duplicate Element, it will return a pair of iterator and bool */
	result = setOfNum.insert(6);
	if (result.second == false)
		std::cout << "Failed to Insert 6" << std::endl;
 
	/* Try to insert a another Element, it will return a pair of iterator and bool */
	result = setOfNum.insert(7);
	if (result.second)
		std::cout << "Successfully Inserted 7" << std::endl;
 
	for (int val : setOfNum)
		std::cout << val << " ";
	std::cout << std::endl;
 
    /* 2. insert another container: 
     * Create an another vector of ints */
	std::vector<int> vec( { 3, 4, 1, 2, 9, 1, 3, 4, 5, 6 });
	setOfNum.insert(vec.begin(), vec.end());
	for (int val : setOfNum)
		std::cout << val << " ";
	std::cout << std::endl;
 
	/* 3. Insert an initializer_list in existing  unordered set */
	setOfNum.insert( { 2, 3, 6, 2, 15, 17, 11 });
	for (int val : setOfNum)
		std::cout << val << " ";
	std::cout << std::endl;
}
 
/**********************************************************************************
 * How to search an element in unordered_set
 * std::unordered_set provides a member function find () that accepts an element 
 * of same type as set and search for that element in set.
 * */ 
 
 int main() 
 {
	std::unordered_set<int> setOfNum( { 1, 2, 3, 1, 3, 4, 2 });
	std::unordered_set<int>::const_iterator it = setOfNum.find(4);
 
	if (it != setOfNum.end()) 
    {
		std::cout << "4 exist in the set" << std::endl;
	}
 
	it = setOfNum.find(9);
 
	if (it == setOfNum.end()) 
    {
		std::cout << "9 dont exist in the set" << std::endl;
	}
 
}
