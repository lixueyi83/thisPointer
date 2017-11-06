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

int main_10()
{
   Application app;
   std::thread thread_1(&Application::mainTask, &app);
   std::thread thread_2(&Application::loadData, &app);
   thread_2.join();
   thread_1.join();
   return 0;
}


/*******************************************************************************************  
*   std::future , std::promise and Returning values from Thread                
*   http://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread/
*   1. How thread can return 3 different values at different point of time? >>> std::future.
*   2. std::future is a class template and its object stores the future value.
*   3. std::promise is also a class template and its object promises to set the value in future.
*   4. A std::promise object shares data with its associated std::future object.
*   5. Every std::promise object has an associated std::future object, through which others can fetch the value set by promise.
*/
#include <iostream>
#include <thread>
#include <future>
 
/* practice 1 */
void initiazer(std::promise<int> *promObj)
{
    std::cout<<"Inside Thread"<<std::endl;     
    promObj->set_value(35);
}
 
/*
*   If you want your thread to return multiple values at different point of time then just pass multiple 
*   std::promise objects in thread and fetch multiple return values from thier associated multiple std::future objects.
*/
int main_11()
{
    /*1. create a promise object: As of now this promise object doesn’t have any associated value.
    *   But it gives a promise that somebody will surely set the value in it and once its set then
    *   you can get that value through associated std::future object.
    */
    std::promise<int> promiseObj;
    
    /*2. associate promise object to future object */
    std::future<int> futureObj = promiseObj.get_future();
    
    /* 3. assign promise object to thread function */
    std::thread th(initiazer, &promiseObj);
    
    /* 4. get future value set in promise object, it will block until the value is set */
    std::cout<<futureObj.get()<<std::endl;
    th.join();
    return 0;
}

/* practice 2 */
void print_int(std::future<int>& fut) 
{
    int x = fut.get();  /* block until the value is set or available */
    std::cout << "value: " << x << '\n'; 
}

int main_12()
{
    /* 1. create promise obj */
    std::promise<int> prom; 
    
    /* 2. associate promise obj to future obj */
    std::future<int> fut = prom.get_future(); 
    
    /* 3. assign future obj to thread function */
    std::thread t(print_int, std::ref(fut)); 
    
    /* 4. set future value in promise obj */
    prom.set_value(10); 
    
    t.join();
    return 0;
}

/* practice 3 */
std::promise<int> prom;

void print_global_promise () 
{
    std::future<int> fut = prom.get_future();
    int x = fut.get();
    std::cout << "value: " << x << '\n';
}

int main_13()
{
    std::thread th1(print_global_promise);
    prom.set_value(10);
    th1.join();

    prom = std::promise<int>();    // prom 被move赋值为一个新的 promise 对象.

    std::thread th2 (print_global_promise);
    prom.set_value (20);
    th2.join();

  return 0;
}

/*******************************************************************************************  
*   std::async 
*   http://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/
*   
*   emplate <class Fn, class... Args>
*   future<typename result_of<Fn(Args...)>::type> async(launch policy,
*                                                       Fn&& fn, 
*                                                       Args&&... args);
*   
*   1. std::async() is a function template that accepts a callback(i.e. function or
*   function object) as an argument and potentially executes them asynchronously.
*   
*   2. std::async returns a std::future<T>, that stores the value returned by function 
*   object executed by std::async(). Arguments expected by function can be passed to 
*   std::async() as arguments after the function pointer argument.
*   
*   3. First argument in std::async is launch policy,
*       - std::launch::async
*       - std::launch::deferred
*       - std::launch::async | std::launch::deferred (by default)
*
*   4. We can pass any callback in std::async i.e.
*       - Function Pointer
*       - Function Object
*       - Lambda Function
*/

using namespace std::chrono;
 
std::string fetchDataFromDB(std::string recvdData)
{
	// Make sure that function takes 5 seconds to complete
	std::this_thread::sleep_for(seconds(5));
 
	//Do stuff like creating DB Connection and fetching Data
	return "DB_" + recvdData;
}
 
std::string fetchDataFromFile(std::string recvdData)
{
	// Make sure that function takes 5 seconds to complete
	std::this_thread::sleep_for(seconds(5));
 
	//Do stuff like fetching Data File
	return "File_" + recvdData;
}
 
int main_14()
{
	// Get Start Time
	system_clock::time_point start = system_clock::now();
 
	//Fetch Data from DB
	std::string dbData = fetchDataFromDB("Data");
 
	//Fetch Data from File
	std::string fileData = fetchDataFromFile("Data");
 
	// Get End Time
	auto end = system_clock::now();
 
	auto diff = duration_cast < std::chrono::seconds > (end - start).count();
	std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;
 
	//Combine The Data
	std::string data = dbData + " :: " + fileData;
 
	//Printing the combined Data
	std::cout << "Data = " << data << std::endl;
 
	return 0;
}

int main()
{
	// Get Start Time
	system_clock::time_point start = system_clock::now();
 
	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
 
	//Fetch Data from File
	std::string fileData = fetchDataFromFile("Data");
 
	//Fetch Data from DB
	// Will block till data is available in future<std::string> object.
	std::string dbData = resultFromDB.get();
 
	// Get End Time
	auto end = system_clock::now();
 
	auto diff = duration_cast < std::chrono::seconds > (end - start).count();
	std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;
 
	//Combine The Data
	std::string data = dbData + " :: " + fileData;
 
	//Printing the combined Data
	std::cout << "Data = " << data << std::endl;
 
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

















