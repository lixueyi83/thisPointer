/*************************************************************************
	> File Name: all_any_of.cpp
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

void print_vec(vector<string> &vec)
{
    cout << "--------------------------" << endl;
    for(auto s : vec)
        cout << s << " ";
    cout << "\n--------------------------" << endl;
}

/* all_of, any_of
* */
int main_all_of()
{
    cout << __func << endl;

	/* A vector of strings */
	std::vector<std::string> wordList =
	{ "Hi", "Hello", "Test", "First", "Second", "Third", "Fourth" };
 
	/* Check if all strings in vector are of same size i.e. 4. */
	bool result = std::all_of(wordList.begin(), wordList.end(), 
	                            [](const std::string & str){
									return str.size() == 4;
							});

    print_vec(wordList);
 
	std::cout << "Is Vector contains all string with size 4 ? | Result = " << result << std::endl;
 
	/* Check if all strings in vector starts with a Upper Case Letter */
	result = std::all_of(wordList.begin(), wordList.end(), 
	                                       [](const std::string & str) {
										   return str.size() > 0 && ::isupper(str[0]);
										});
 
	std::cout<< "Are all strings in vector starts with a Upper Case Letter ? | Result = " << result << std::endl;
 
	std::string str = "testString";
	
    /* Check if given string contains all lower case letters i.e. not a single upper case char */
	result = std::all_of(str.begin(), str.end(), ::islower);
 
	std::cout << "Does given string (" << str << ") contains all lower case letters ? | Result = " << result << std::endl;
 
	/* Using all_of() with array */
 
	int arr[] = {3,9,75,15,12};
 
	/* Check if all numbers in array are multiple of 3 i.e. */
	result = std::all_of(arr, arr + sizeof(arr)/ sizeof(int), [](const int & i){ return i%3 == 0; });
 
	std::cout << "Does all numbers in array are multiple of 3 | Result = " << result << std::endl << endl; 
	return 0;
}

int main_any_of()
{
	std::vector<std::string> vecOfStrs =
	{ "Hi", "Hello", "test", "first", "second", "third", "fourth" };
 
    print_vec(vecOfStrs);

	/* Check if vector contains any string with size 4. */
	bool result = std::any_of(vecOfStrs.begin(), vecOfStrs.end(), [](const std::string & str){
																	    return str.size() == 4;
																	});
 
	std::cout << "vector contains any string with size 4 | Result = " << result << std::endl;
 
	/* Check if vector contains any string that starts with char 'P' */
	result = std::any_of(vecOfStrs.begin(), vecOfStrs.end(), [](const std::string & str) {
															return str.size() > 0 && str[0] == 'P';
														});
 
	std::cout<< "vector contains any string that starts with char 'P' | Result = " 	<< result << std::endl;
 
	std::string str = "testString";
 
	/* Check if given string contains all lower case letters i.e. not a single upper case char */
 
	result = std::any_of(str.begin(), str.end(), ::isupper);
 
	std::cout << "str  = " << str << std::endl;
	std::cout<< "Check if given string (" << str << ") contains all lower case letters | Result = " << result << std::endl;
	return 0;
}

int main()
{
    main_all_of();
    main_any_of();
}









