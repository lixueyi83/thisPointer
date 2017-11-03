/*************************************************************************
	> File Name: multithreading.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <thread>
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


/*
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

/*
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

/*
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


#include <bits/stdc++.h>
using namespace std;
  
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
  
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
  
    for_each(arr, arr+n, increment(3));
  
    for (int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
  
    return 0;
}

















