/*************************************************************************
	> File Name: tuple.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <tuple>

using namespace std;


/*
 * 1. tuple is a type that can bind fixed size heterogenerous values together.
 * 2. we can return tuple from a function which helps return multiple values from function.
 * 3. by returning tuple from a function avoiding creating unnecessary structs.
 * 4. std::make_tuple helps in automatic deduction of tuple types.
* */


/*
 * Returning multiple values from a function by binding them in a single
 * tuple object.
 */
std::tuple<int, double, std::string> someFunction()
{
	std::tuple<int, double, std::string> result(7, 9.8, "text");
 
	return result;
}
 
int main()
{
 
	// Get tuple object from a function
	std::tuple<int, double, std::string> result = someFunction();
 
	// Get values from tuple
 
	// Get First int value from tuple
	int iVal = std::get < 0 > (result);
 
	// Get second double value from tuple
	double dVal = std::get < 1 > (result);
 
	// Get third string value from tuple
	std::string strVal = std::get < 2 > (result);
 
	// Print values
	std::cout << "int value = " << iVal << std::endl;
	std::cout << "double value = " << dVal << std::endl;
	std::cout << "string value = " << strVal << std::endl;
 
	// Get 4th int value from tuple
	// Will cause compile error because this tuple
	// has only 3 elements
 
	//int iVal2 = std::get<4>(result); // Compile error
 
	// Wrong cast will force compile time error
	// Get first value from tuple in a string
 
	//std::string strVal2 = std::get<0>(result); // Compile error
 
	int x = 1;
 
	// Get second double value from tuple
	// Compile error because x is not compile time contant
 
	//double dVal2 = std::get<x>(result);
 
	const int i = 1;
	// Get second double value from tuple
	double dVal3 = std::get < i > (result);
 
	return 0;
}

int main_2()
{
	// Creating and Initializing a tuple
	std::tuple<int, double, std::string> result1 { 22, 19.28, "text" };
 
	// Compile error, as no way to deduce the types of elements in tuple
	//auto result { 22, 19.28, "text" }; // Compile error
 
	// Creating a tuple using std::make_tuple
	auto result2 = std::make_tuple( 7, 9.8, "text" );
 
	// std::make_tuple automatically deduced the type and created tuple
 
	// Print values
	std::cout << "int value = " << std::get < 0 > (result2) << std::endl;
	std::cout << "double value = " << std::get < 1 > (result2) << std::endl;
	std::cout << "string value = " << std::get < 2 > (result2) << std::endl;
 
	return 0;
}

