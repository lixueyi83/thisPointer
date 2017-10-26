/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <array>
using namespace std;


/*
 * Lambdas function does not have to capture static variables
 * Lambdas function is designed for capturing auto variables
 * Lambdas function access class member function by capture this pointer 
* */

void print(int a)
{
    cout << a << " ";;
}

void init(int& a)
{
    a = rand()%100;
}

class Counter
{
public:
    int get_counter(){cout <<"\nm_counter = " << m_counter << endl; return m_counter;}
    void update(vector<int> &vec)
    {
        for_each(vec.begin(), vec.end(), [this](int element)
                 {
                     if(element%2)
                        m_counter++;
                     cout << m_counter << " ";
                 });
    }

private:
    int m_counter;

};

Counter obj;

int main()
{
    srand(time(NULL));

    int counter = 0;
    std::array<int, 10> arr;

    for_each(arr.begin(), arr.end(), &init);
    for_each(arr.begin(), arr.end(), &print);
    cout << endl;

    for_each(arr.begin(), arr.end(), [](int &x){x = rand()%10;});
    for_each(arr.begin(), arr.end(), &print);
    cout << endl;

    for_each(arr.begin(), arr.end(), [counter](int x)mutable{cout << counter++ << " ";});
    cout << endl;
    cout << "counter = " << counter << endl;
    
    for_each(arr.begin(), arr.end(), [&counter](int x){cout << counter++ << " ";});
    cout << endl;
    cout << "counter = " << counter << endl;

    vector<int> vec = {9,8,7,6,5,4,3,2,1,0};
    obj.get_counter();
    obj.update(vec);
    obj.get_counter();
    cout << endl;

    auto f = [](){cout << "-------------" << endl; obj.get_counter();};
    f();

    return 0;
}
