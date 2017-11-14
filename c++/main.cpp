/*************************************************************************
	> File Name: stl_vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <iterator>
#include <list>
#include <string>
#include "debug.h"

using namespace std;

/**********************************************************************
Important Points about std::vector :

0.) std::vector allocates a memory on heap and store all its elements in contiguous memory location. When the current vector capacity is not enough to store the more elements, it will allocate a bigger chunck of memory, almost double size of the current capacity, and then copy all elements from the old memory location to a new location and then delete the old memory.

1.) Ordered Collection:
In std::vector all elements will remain in same order in which they are inserted.

2.) Provides random access:
Indexing is very fast in std::vector using opeartor [], just like arrays.

3.) Performance:
It Performs better if insertion and deletion is in end only and gives worst performance if insertion/deletion is at middle or at starting of vector.

4.) Contains Copy:
It always stores copy of the object not the same reference. So, if you are adding objects of user defined classes the you should define copy constructor and assignment opeartor in you class.

************************************************************************/

void example1() 
{
    /* Initialize vector with 5 integers, Default value of all 5 ints will be 0. */
	std::vector<int> vecOfInts(5);
 
	for (int x : vecOfInts)
		std::cout << x << std::endl;
 
}
 
void example2() 
{
    /* Initialize vector to 5 string objects with value "Hi" */
	std::vector<std::string> vecOfStr(5, "Hi");
 
	for (std::string str : vecOfStr)
		std::cout << str << std::endl;
 
}
 
void example3() 
{
    /* Create an array of string objects */
	std::string arr[] = { "first", "sec", "third", "fourth" };
 
    /* Initialize vector with a string array */
	std::vector<std::string> vecOfStr(arr, arr + sizeof(arr)/sizeof(std::string));
 
	for (std::string str : vecOfStr)
		std::cout << str << std::endl;
 
}
 
void example4() 
{
    /* Create an std::list of 5 string objects */
	std::list<std::string> listOfStr;
	listOfStr.push_back("first");
	listOfStr.push_back("sec");
	listOfStr.push_back("third");
	listOfStr.push_back("fouth");
 
    /* Initialize a vector with std::list */
	std::vector<std::string> vecOfStr(listOfStr.begin(), listOfStr.end());
 
	for (std::string str : vecOfStr)
		std::cout << str << std::endl;
 
    /* Initialize a vector with other string object */
	std::vector<std::string> vecOfStr3(vecOfStr);
 
	for (std::string str : vecOfStr3)
		std::cout << str << std::endl;
 
}
 
int main_init_vector() 
{
	example1();
	example2();
	example3();
	example4();
	return 0;
}


struct Sample
{
    Sample(){}
    Sample(const Sample & obj)
    {
        //std::cout<<"Sample copy constructor"<<std::endl;
    }
};
int main_vector_memory_allocation_policy()
{
    std::vector<Sample> vecOfInts;
 
    std::cout<<"Capacity :: "<<vecOfInts.capacity()<<std::endl;
    std::cout<<"Size :: "<<vecOfInts.size()<<std::endl;
    
    int capcity = vecOfInts.capacity();
    cout << endl;
    
    for(int i=0; i<10; i++)
    {
        for(int i = 0; i < capcity + 1; i++)
            vecOfInts.push_back(Sample());
     
        std::cout<<"Capacity :: "<<vecOfInts.capacity()<<std::endl;
        std::cout<<"Size :: "<<vecOfInts.size()<<std::endl;
        cout << endl;
    }
 
    return 0;
}

/***********************************************************************
    How to use vector efficiently in C++?
    1) Vector will be more efficient if elements are inserted or removed from 
    the back-end only, avoiding costly shifting operations.
    2) Set the storage of vector initially using reserve() member function.
    3) Instead of adding single element in multiple calls, large set of elements 
    is added in single call.
*/

struct BigTestStruct
{
    int iValue = 1;
    float fValue;
    long lValue;
    double dValue;
    char cNameArr[10];
    int iValArr[100];
};

void FillVector(vector<BigTestStruct>& testVector)
{
    for (int i = 0; i < 10000; i++)
    {
        BigTestStruct bt;
        testVector.push_back(bt);
    }
}


/*
http://www.acodersjourney.com/2016/11/6-tips-supercharge-cpp-11-vector-performance/ 
*/
int main()
{
    vector<BigTestStruct> testVector1;
    vector<BigTestStruct> testVector2;
    vector<BigTestStruct> testVector3;
    
    /*********************************************************
        #1 Avoid unnecessary reallocate and copy cycles by reserving the size of 
    vector ahead of time
    */
    RUNTIME_MEAS(FillVector, testVector1);
    
    testVector2.reserve(10000);
    RUNTIME_MEAS(FillVector, testVector2);
    
    /********************************************************
        #2 Use shrink_to_fit() to release memory consumed by the vector – clear() 
    or erase() does not release memory.
    */
    FillVector(testVector1);
    size_t capacity = testVector1.capacity();
    cout << "Capacity Before Erasing Elements:" << capacity << endl;

    testVector1.erase(testVector1.begin(), testVector1.begin() + 3); //
    capacity = testVector1.capacity();
    cout << "Capacity After Erasing 3 elements Elements:" << capacity << endl;
    
    testVector1.clear();
    capacity = testVector1.capacity();
    cout << "Capacity After clearing all emements:" << capacity << endl;
    
    testVector1.shrink_to_fit();
    capacity = testVector1.capacity();
    cout << "Capacity After shrinking the Vector:" << capacity << endl;
    
    /****************************************************************
        #3 When filling up or copying a vector into another vector, prefer 
        assignment over insert() or push_back(). If you have to copy from another
        type of container into a vector, assignment is not an option. In this case,
        you want to do iterator based insert. 
        Here's an example of the runtime tested: 
        Assignment: 589.54 us
        Insert(): 1321.27 us
        Push_back(): 5354.70 us
    */
    vector<BigTestStruct> destVec, srcVector;
    destVec = srcVector;
    destVec.insert(destVec.end(), srcVector.begin(), srcVector.end());
    for(unsigned i = 0; i < srcVector.size(); ++i)
        destVec.push_back(srcVector[i]);
    
}













