/*************************************************************************
	> File Name: multithreading.cpp
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


/***************************************************************************************
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

/****************************************************************************************
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
 
int main_6()  
{
    std::thread threadObj(thread_func);

    // If we comment this Line, then program will crash
    ThreadRAII wrapperObj(threadObj);
    return 0;
}



/****************************************************************************************
*   Pass Arguments to Threads
*   1. To Pass arguments to thread’s associated callable object or function just passadditional 
*   arguments to the std::thread constructor.
*   2. By default all arguments are copied into the internal storage of new thread.
*   3. Don’t pass addresses of variables from local stack to thread’s callback function. 
*   4. Similarly be careful while passing pointer to memory located on heap to thread.
*/

/*   
*   Pass reference to thread's associated callable object with std:ref().
*/
void threadCallback(int const & x)
{
    int & y = const_cast<int &>(x);
    y++;
    std::cout<<"Inside Thread x = "<<x<<std::endl;
}
int main_7()
{
    int x = 9;
    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    //std::thread threadObj(threadCallback, x); /* x in the thread function threadCallback is reference to the temporary value copied at the new thread’s stack */
    std::thread threadObj(threadCallback, ref(x));
    threadObj.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;
    return 0;
}


/*
*   Pass argument to member function of a class as thread function. 
*/
class DummyClass 
{
public:
    DummyClass()
    {}
    DummyClass(const DummyClass & obj)
    {}
    void sampleMemberFunction(int x)
    {
        std::cout<<"Inside sampleMemberFunction "<<x++<<std::endl;
    }
    void sampleMemberFunctionRef(int &x)
    {
        std::cout<<"Inside sampleMemberFunction "<<x++<<std::endl;
    }
};
int main_8() 
{ 
    DummyClass dummyObj;
    int x = 10, y = 10;
    std::thread threadObj1(&DummyClass::sampleMemberFunction,&dummyObj, x);
    std::thread threadObj2(&DummyClass::sampleMemberFunctionRef,&dummyObj, ref(y));
    threadObj1.join();
    threadObj2.join();
    
    cout << "x = " << x << ", y = " << y << endl;
    return 0;
}


/*******************************************************************************************  
*   Data Sharing and Race Conditions: Lock Mechanism
*   
*   1. std::lock_guard :std::lock_guard is a class template, which implements the RAII for mutex.
*       It wraps the mutex inside it’s object and locks the attached mutex in its constructor. 
*       When it’s destructor is called it releases the mutex.
*   2. 
*/
class Wallet
{
	int mMoney;
	std::mutex mutex;
public:
    Wallet() :mMoney(0){}
    int getMoney()   { 	return mMoney; }
    void addMoney(int money)
    {
		std::lock_guard<std::mutex> lockGuard(mutex);
		// In constructor it locks the mutex
 
    	for(int i = 0; i < money; ++i)
		{
			// If some exception occurs at this
			// poin then destructor of lockGuard
			// will be called due to stack unwinding.
			//
			mMoney++;
		}
		// Once function exits, then destructor
		// of lockGuard Object will be called.
		// In destructor it unlocks the mutex.
    }
 };
 
 int main_9()
 {
    return 0;
 }

/*******************************************************************************************  
*   Need of Event Handling: http://thispointer.com/c11-multithreading-part-6-need-of-event-handling/ 
*   >>>> Conditional Variables is the solution. #include <condition_variable>
*        A mutex is required along with condition variable.
*   
*   1. Make a Boolean global variable with default value false. Set its value to true in Thread 2 
*   and Thread 1 will keep on checking its value in loop and as soon as it becomes true Thread 1 
*   will continue with processing of data. But as it’s a global variable shared by both of the 
*   Threads it needs synchronization with mutex. 
*   This mechanism has following disadvantages: 
*   Thread will keep on acquiring the lock and release it just to check the value, therefore it 
*   will consume CPU cycles and will also make Thread 1 slow, because it needs to acquire same 
*   lock to update the bool flag.
*   2. We can achieve this using Condition Variables.
*   Condition Variable is a kind Event used for signaling between 2 threads. One thread can wait
*   for it to get signaled, while other thread can signal this.
*   >>> Main member functions for condition variable are wait(), notify_one() and notify_all().
*/

#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std::placeholders;

class Application
{
  std::mutex m_mutex;
  std::condition_variable m_condVar;
  bool m_bDataLoaded;
  
public:
  Application()
  {
    m_bDataLoaded = false;
  }
  void loadData()
  {
   // Make This Thread sleep for 1 Second
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::cout<<"Loading Data from XML"<<std::endl;
   // Lock The Data structure
   std::lock_guard<std::mutex> guard(m_mutex);
   // Set the flag to true, means data is loaded
   m_bDataLoaded = true;
   // Notify the condition variable
   m_condVar.notify_one();
  }
  bool isDataLoaded()
  {
    return m_bDataLoaded;
  }
  void mainTask()
  {
    std::cout<<"Do Some Handshaking"<<std::endl;
    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);
    // Start waiting for the Condition Variable to get signaled
    // Wait() will internally release the lock and make the thread to block
    // As soon as condition variable get signaled, resume the thread and
    // again acquire the lock. Then check if condition is met or not
    // If condition is met then continue else again go in wait.
    m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
    std::cout<<"Do Processing On loaded Data"<<std::endl;
  }
};

int main()
{
   Application app;
   std::thread thread_1(&Application::mainTask, &app);
   std::thread thread_2(&Application::loadData, &app);
   thread_2.join();
   thread_1.join();
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

















