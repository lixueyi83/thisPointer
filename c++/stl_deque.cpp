/*************************************************************************
	> File Name: stl_deque.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <iterator>
#include <list>
#include <string>
#include "debug.h"

using namespace std;

/*******************************************************************
Differences between vector and deque STL Containers.

    Vector provides insertion and deletion at middle and end only. Whereas, deque provides operations for insertion at front, middle and end. That is, apart from push_back() and pop_back() APIs jus like vector, deque also has push_front() and pop_front() API to add and delete elements from front.
    Vector provides good performance while insertion and deletion at end only and bad performance for insertion and deletion at middle.
    Deque provides same kind of performance as vector for insertion & deletion at end and middle. Apart from that deque provides good performance for insertion and deletion at front also.
    As Vector stores elements contiguously, where as deque internally contains a list of memory chunks which store elements contiguously. Due this basic architectural difference between vector and deque following things happen,
    Performance of addition and deletion at end for vector is better than deque.
    No Iterator invalidation happens in deque for insertion and deletion at front and end because like vectors, deque doesn’t have to shift elements from one memory to another in case current allocated memory is not sufficient to store the newly added element.

    Iterator invalidation happens in deque just like vector, if insertion or deletion takes place in the middle.
    Just like vector, deque also supports random access operations i.e. operator [] and at() function. Although performance of random access in deque will be little slower than vector.

When to choose deque over vector:
    One should choose deque over vector if he wants to either add or delete from both the ends like implementing a Queue.
When to choose vector over deque:
    One should choose vector if insertion or deletions are required mostly in end like implementing a Stack.
*/

int main()
{
    std::deque<int> dequeObj;
 
    dequeObj.push_back(5);
    dequeObj.push_back(6);
 
    for(int i = 0; i< dequeObj.size(); i++)
        std::cout<<dequeObj[i]<<" ";
    std::cout<<std::endl;
 
    dequeObj.push_front(4);
    dequeObj.push_front(3);
 
    for(int i = 0; i< dequeObj.size(); i++)
            std::cout<<dequeObj[i]<<" ";
    std::cout<<std::endl;
 
    dequeObj.pop_back();
 
    for(int i = 0; i< dequeObj.size(); i++)
            std::cout<<dequeObj[i]<<" ";
    std::cout<<std::endl;
 
    dequeObj.pop_front();
 
    for(int i = 0; i< dequeObj.size(); i++)
                std::cout<<dequeObj[i]<<" ";
    std::cout<<std::endl;
    return 0;
}







