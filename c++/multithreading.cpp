/*************************************************************************
	> File Name: multithreading.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <unistd.h>

using namespace std;

/* Three different ways of create Threeads: we can attach a callback with thread object. 
*   
*   std::thread thObj(<CALLBACKs>);
*
*   These CALLBACKs can be: 
*       1) function pointer; 
*       2) function objects; 
*       3) lambda functions; 
* */


/*---------------------------------------------------------------------
*  Creating a thread using Function Pointer 
*/
void thread_function()
{
    for(int i = 0; i < 10000; i++);
        std::cout<<"thread function Executing"<<std::endl;
}

int main_1()  
{
    
    std::thread threadObj(thread_function);
    
    usleep(1000); /* allow thread_function running first*/
    
    std::cout<<"display From MainThread"<<std::endl;
        
    threadObj.join();    
    
    std::cout<<"Exit of Main function"<<std::endl;
    
    return 0;
}

/*---------------------------------------------------------------------
*  Creating a thread using Function Object 
*/
class DisplayThread
{
public:
    void operator()()     
    {
        for(int i = 0; i < 10; i++)
            std::cout<<"****** Thread Executing"<<std::endl;
    }
};
 
int main_2()  
{
    DisplayThread functor();
    //functor();
    //std::thread threadObj((functor()));
    std::thread threadObj( (DisplayThread()) );
    for(int i = 0; i < 10; i++)
        std::cout<<"------ From Main Thread "<<std::endl;
    std::cout<<"Waiting For Thread to complete"<<std::endl;
    threadObj.join();
    std::cout<<"Exiting from Main Thread"<<std::endl;
    return 0;
}

/*---------------------------------------------------------------------
*  Creating a thread using Function Lambda function 
*/
int main_3()  
{
    int x = 9;
    std::thread threadObj([]()
        {
            for(int i = 0; i < 10; i++)
                std::cout<<"****** Thread Executing"<<std::endl;
        });
            
    for(int i = 0; i < 10; i++)
        std::cout<<"------ From Main Thread"<<std::endl;
        
    threadObj.join();
    std::cout<<"Exiting from Main Thread"<<std::endl;
    return 0;
}


class myFunctorClass
{
    public:
        myFunctorClass (int x) : _x( x ) {}
        int operator() (int y) 
        { 
            return _x + y; 
            cout << "***********" << endl;
        }
        
    private:
        int _x;
};
 
int main_4()
{
    myFunctorClass addFive( 5 );
    std::cout << addFive( 6 ) << endl;
 
    return 0;
}


/*
*   Join and Detach a thread 
*   Before calling join() or detach() we should check if thread is join-able every time.
*   if(threadObj.joinable()) { "join or detach the thread" }
*   Note: join or detach twice the same thread object will terminate the program. 
*   
*   1. Never call join() or detach() on std::thread object with no associated executing thread.
*   2. Never forget to call either join or detach on a std::thread object with associated executing thread.
*/

class WorkerThread
{
public:
    void operator()()     
    {
        std::cout<<"Worker Thread "<<std::this_thread::get_id()<<" is Executing"<<std::endl;
    }
};
int main_5()  
{
    std::vector<std::thread> threadList;
    for(int i = 0; i < 10; i++)
    {
        threadList.push_back( std::thread( WorkerThread() ) );
    }
    // Now wait for all the worker thread to finish i.e.
    // Call join() function on each of the std::thread object
    std::cout<<"wait for all the worker thread to finish"<<std::endl;
    std::for_each(threadList.begin(),threadList.end(), std::mem_fn(&std::thread::join));
    std::cout<<"Exiting from Main Thread"<<std::endl;
    return 0;
}

/*
*   RAII
*   we should not forget call either join() or detach() in case of exceptions. 
*   To prevents with we should use RESOURCE ACQUISITION IS INITIALIZATION (RAII) i.e.
*/
class ThreadRAII
{
    std::thread & m_thread;
    public:
        ThreadRAII(std::thread  & threadObj) : m_thread(threadObj)
        {
            cout << "ThreadRAII constructor " << endl;
        }
        ~ThreadRAII()
        {
            cout << "ThreadRAII destructor " << endl;
            
            // Check if thread is joinable then detach the thread
            if(m_thread.joinable())
            {
                m_thread.detach();
                //m_thread.join();
            }
        }
};
void thread_func()
{
    for(int i = 0; i < 10000; i++);
        std::cout<<"thread_function Executing"<<std::endl;
}
 
int main()  
{
    std::thread threadObj(thread_func);

    // If we comment this Line, then program will crash
    ThreadRAII wrapperObj(threadObj);
    return 0;
}


#include <bits/stdc++.h>
  
/* unary function */
int increment1(int &x) {x++;}

class increment
{
public:
    increment(int n): num(n) {}
    
    int operator () (int x)
    {
        num += x;
    }
private:
    int num;
};
  
int main_last()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    for_each(arr, arr+n, increment1);
    for_each(arr, arr+n, [](int &x){x++;});
  
    for (int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
  
    return 0;
}

















