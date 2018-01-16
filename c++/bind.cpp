/*************************************************************************
	> File Name: std_bind.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Jan 2018 12:32:11 PM PST
 ************************************************************************/

#include<iostream>
#include<memory>
#include<algorithm>
#include<functional>

using namespace std;
using namespace std::placeholders;

/****************************************************************************************
 *
* */

int add(int first, int second)
{
    return first + second;
}

int  divisible(int num, int den)
{
    return (num % den == 0);
}

int solution_1()
{
    int arr[10] = {1,20,13,4,5,6,10,28,19,15};
    int count = 0;

    for(int unsigned i=0; i<sizeof(arr)/sizeof(int); i++)
    {
        if(divisible(arr[i], 5));
            count++;
    }
    return count;
}

int solution_2()
{
    int arr[10] = {1,20,13,4,5,6,10,28,19,15};
    return std::count_if(arr, arr+sizeof(arr)/sizeof(int), std::bind(&divisible, _1, 5));
}

int main_1()
{
    int x = add(4,5);
    cout << x << endl;

    auto new_add_func = std::bind(&add, 12, _1);
    x = new_add_func(5);
    std::cout << x << std::endl;

    //auto mod_add_func = std::bind(&add, _2, _1);
    auto mod_add_func = std::bind(&add, _1, _2);
    x = mod_add_func(12,15);
    std::cout << x << std::endl;

    std::function<int (int)> mod_add_funcObj = std::bind(&add, 20, _1);
    x = mod_add_funcObj(15);
    std::cout << x << std::endl;

    std::cout << solution_1() << std::endl;
    std::cout << solution_2() << std::endl;

    return 0;
}


/*************************************************************************************
* The number of placeholders determine the number of arguments required to pass in.
* The position of placeholder determines the value position in function call statement.
*/
void func(int a, int b, int c)
{
    cout << a << " " << b << " " << c << ", ret = ";
    cout << (a-b-c) << endl << endl;
}

int main()
{
    using namespace std::placeholders;
    
    /* 1 place holder */
    auto fn1 = bind(func, _1, 2, 4);
    cout << "The value of function with 1 placeholder is : ";
    fn1(10);
        
    /* 2 placeholders */
    auto fn2 =  bind(func,_1,2,_2);
    cout << "The value of function with 2 placeholders is : ";
    fn2(13, 1);
        
    /* 3 placeholders */
    auto fn3 =  bind(func,_1, _3, _2);
    cout << "The value of function with 3 placeholders is : ";
    fn3(13, 1, 4);
    
    auto fn4 =  bind(func, _2, 2, _1);
    cout << "The value of function is : ";
    fn4(1, 13);
    
    auto fn5 =  bind(func, _1, 2, _2);
    cout << "The value of function is : ";
    fn5(1, 13);
    
    return 0;  
}



























