/*************************************************************************
	> File Name: stl_list.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <iterator>
#include <list>
#include <string>
#include "debug.h"

using namespace std;

/***********************************************************************
    Benefits of using std::map :
    1. It stores only unique keys and that too in sorted order based on its assigned sorting criteria.
    2. As keys are in sorted order therefore searching element in map through key is very fast i.e. it takes logarithmic time.
    3. In std::map there will be only one value attached with the every key.
    4. std::map can be used as associative arrays.
    5. It might be implemented using balanced binary trees.

*/
int main_basics()
{
    std::map<std::string, int> mapOfWords;
    
    /* Inserting data in std::map */
    mapOfWords.insert(std::make_pair("earth", 1));
    mapOfWords.insert(std::make_pair("moon", 2));
    mapOfWords["sun"] = 3;
    
    /* Will sliently change/replace the value of already added key i.e. earth */
    mapOfWords["earth"] = 4;
    
    /*  insert will not replace already added key instead it returns the information */
    mapOfWords.insert(std::make_pair("sun", 0));
    
    /* Iterate through all elements in std::map */
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        std::cout << it->first << " :: " << it->second <<std::endl;
        it++;
    }
    
    cout << "------------------------------------------------" << endl;
    
    /* Check if insertion is successful or not */
    if(mapOfWords.insert(std::make_pair("earth", 1)).second == false)
    {
        std::cout<<"Element with key 'earth' already existed"<<std::endl;
    }
    
    /* Searching element in std::map by key. */
    if(mapOfWords.find("sun") != mapOfWords.end())
        std::cout<<"word 'sun' found"<<std::endl;
        
    if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl;
        
    /* print map */
    for(auto x : mapOfWords)
        cout << x.first << " :: " << x.second <<std::endl;
        
    cout << "------------------------------------------------" << endl;
        
    /* Erasing By iterator */
    std::map<std::string, int>::iterator ite = mapOfWords.find("moon");
    mapOfWords.erase(ite);
 
     /* print map */
    for(auto x : mapOfWords)
        cout << x.first << " :: " << x.second <<std::endl;
 
    /* Erasing By Key */
    mapOfWords.erase("earth");
    
    cout << "------------------------------------------------" << endl;
    
    /* print map */
    for(auto x : mapOfWords)
        cout << x.first << " :: " << x.second <<std::endl;
        
    return 0;
}

/***********************************************************************
    Map and External Sorting Criteria / Comparator
    
*/



















