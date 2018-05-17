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

/* A Function Object / Functor is a kind of Callback with State. */
class myFunctorClass
{
    public:
        myFunctorClass (int x) : _x( x ) {}
        int operator() (int y) 
        { 
            _x = _x + y;
            return _x; 
            cout << "***********" << endl;
        }
        
    private:
        int _x;
};
 
int main_4()
{
    myFunctorClass addFive( 5 );
    std::cout << addFive( 6 ) << endl;
    std::cout << addFive( 5 ) << endl;
 
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
            //cout << "ThreadRAII constructor " << endl;
        }
        ~ThreadRAII()
        {
            //cout << "ThreadRAII destructor " << endl;
            
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
    
    cout << "From main thread" << endl;
    sleep(2);
        
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
    DummyClass() {}
    
    DummyClass(const DummyClass & obj) {}
    
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
    
    cout << "x = " << x << "\ny = " << y << endl;
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
private:
	int m_money;
	std::mutex mutex;
	
public:
    Wallet() : m_money(0) {}
    int getMoney() {return m_money;}
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
			m_money++;
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
    //promiseObj.set_value(45);
    
    /* 4. get future value set in promise object, it will block until the value is set */
    std::cout<<futureObj.get()<<std::endl;
    
    //th.join();
    ThreadRAII wrapper(th);
    
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
    
    sleep(1);
    
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
    cout << "busing waiting 1..." << endl;
    sleep(1);
    prom.set_value(10);
    th1.join();

    prom = std::promise<int>();    // prom 被move赋值为一个新的 promise 对象.

    std::thread th2 (print_global_promise);
    cout << "busing waiting 2..." << endl;
    sleep(1);
    prom.set_value (20);
    th2.join();
    
    ThreadRAII wrapper1(th1);
    ThreadRAII wrapper2(th2);

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

/*  https://eli.thegreenplace.net/2016/the-promises-and-challenges-of-stdasync-task-based-parallelism-in-c11/
Conclusion and practical advice

This article started by expounding the virtues of std::async compared to plain std::threads, 
but finished by pointing out numerous problems with std::async that one needs to be aware of. 
So, what do we do?

I actually think that by being careful to stay within the well-defined limits of std::async, 
we can enjoy its benefits without running into the gotchas. Specifically:

    1. Prefer std::async to std::thread. Futures are just too useful to ignore; especially if 
       your code deals with exception handling, this is the only sane way to stay safe. Results 
       provided by different threads should be wrapped in futures.
    
    2. Always use the std::launch::async policy with std::async if you actually want multi-threading. 
       Do not rely on the default policy. Do not use deferred unless you have very special needs. 
       Remember that deferred is just syntactic sugar over holding a function pointer to call it later.
    
    3. If you need a real thread pool or some other higher-level concurrency construct, use a library 
       or roll your own. Standard objects like std::future, std::promise and std::packaged_task can be 
       very helpful.
*/

using namespace std::chrono;
 
std::string fetchDataFromDB(std::string recvdData)
{
	// Make sure that function takes 5 seconds to complete
	std::this_thread::sleep_for(seconds(1));
 
	//Do stuff like creating DB Connection and fetching Data
	return "DB_" + recvdData;
}
 
std::string fetchDataFromFile(std::string recvdData)
{
	// Make sure that function takes 5 seconds to complete
	std::this_thread::sleep_for(seconds(1));
 
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

int main_15()
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


/*  http://thispointer.com/c11-multithreading-part-10-packaged_task-example-and-tutorial/
*/

std::string getDataFromDB( std::string token)
{
	std::string data = "Data fetched from DB by Filter :: " + token;
	return data;
}
 
int main_16()
{
	/* Create a packaged_task<> that encapsulated the callback i.e. a function */
	std::packaged_task<std::string (std::string)> task(getDataFromDB);
 
	/* Fetch the associated future<> from packaged_task<> */
	std::future<std::string> result = task.get_future();
 
	/* Pass the packaged_task to thread to run asynchronously */
	std::thread th(std::move(task), "Arg");
 
	/* Join the thread. Its blocking and returns when thread is finished. */
	th.join();
 
	/* Fetch the result of packaged_task<> i.e. value returned by getDataFromDB() */
	std::string data =  result.get();
 
	std::cout <<  data << std::endl;
 
	return 0;
}

int main_17()
{
	/* Create a packaged_task<> that encapsulated a lambda function */
	std::packaged_task<std::string (std::string)> task([](std::string token)
	{
			std::string data = "Data From " + token;
			return data;
	});
 
	/* Fetch the associated future<> from packaged_task<> */
	std::future<std::string> result = task.get_future();
 
	/* Pass the packaged_task to thread to run asynchronously */
	std::thread th(std::move(task), "Arg");
 
	/* Join the thread. Its blocking and returns when thread is finished. */
	th.join();
 
	/* Fetch the result of packaged_task<> i.e. value returned by getDataFromDB() */
	std::string data =  result.get();
 
	std::cout <<  data << std::endl;
 
	return 0;
}

/*
 * Function Object to Fetch Data from DB
 */
struct DBDataFetcher
{
	std::string operator()(std::string token)
	{
		std::string data = "Data From " + token;
		return data;
	}
};
 
int main_18()
{
	/* Create a packaged_task<> that encapsulated a lambda function */
	std::packaged_task<std::string (std::string)> task(std::move(DBDataFetcher()));
 
	/* Fetch the associated future<> from packaged_task<> */
	std::future<std::string> result = task.get_future();
 
	/* Pass the packaged_task to thread to run asynchronously */
	std::thread th(std::move(task), "Arg");
 
	/* Join the thread. Its blocking and returns when thread is finished. */
	th.join();
 
	/* Fetch the result of packaged_task<> i.e. value returned by getDataFromDB() */
	std::string data =  result.get();
 
	std::cout <<  data << std::endl;
 
	return 0;
}
 
// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) 
{ 
    return std::pow(x,y); 
}
 
void task_lambda()
{
    std::packaged_task<int(int,int)> task([](int a, int b) {
        return std::pow(a, b); 
    });
    std::future<int> result = task.get_future();

    task(2, 9);
 
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
void task_bind()
{
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
 
    task();
 
    std::cout << "task_bind:\t" << result.get() << '\n';
}
 
void task_thread()
{
    std::packaged_task<int(int,int)> task(f);
    std::future<int> result = task.get_future();
 
    std::thread task_td(std::move(task), 2, 10);
    task_td.join();
 
    std::cout << "task_thread:\t" << result.get() << '\n';
}
 
int main_19()
{
    task_lambda();
    task_bind();
    task_thread();
    return 0;
}





















#include <bits/stdc++.h>
  
/* unary function */
int increment1(int &x) 
{
    return ++x;
}

class incrementConst
{
private:
    int num;
public:
    incrementConst(int n) : num(n) {}
 
    // This operator overloading enables calling operator function () on objects of increment
    int operator () (int x) const {
        return num + x;
    }
};
 
// Driver code
int main_20()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    incrementConst incr(5);
    for_each(arr, arr+n, [incr](int& x){x=incr(x);});
    //transform(arr, arr+n, arr, increment(5));
    for_each(arr, arr+n, [](int x){cout << x << " ";});
    cout << endl;
    return 0;
}

class increment
{
public:
    increment(int n): num(n) {}
    
    int operator () (int x)
    {
        num *= x;
        return num;
    }
private:
    int num;
};
  
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    for_each(arr, arr+n, [](int &x){x++;});
    for_each(arr, arr+n, [](int x){cout << x << " ";});
    cout << endl;

    increment incr(1); // init status
    for_each(arr, arr+n, [&incr](int& x){ x = incr(x);});
    for_each(arr, arr+n, [](int x){cout << x << " ";});
    cout << endl;
  
    return 0;
}

















