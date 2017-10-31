/*************************************************************************
	> File Name: smartPointers.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <array>
#include  <memory> /* for smart pointers */
#include <string>

using namespace std;

int main()
{
    string str = "123456789";

    cout << str.substr(str.size()-5) << endl;
}
