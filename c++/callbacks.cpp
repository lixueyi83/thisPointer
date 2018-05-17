/*************************************************************************
	> File Name: callbacks.cpp
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

/* There are three types of CALLBACKs in C++: 
*       1) function pointer; 
*       2) function objects/functors; 
*       3) lambda functions; 
*
*   1. A function object or functor is a kind of callback with "state";
*   2. 
* */
class Encryptor 
{
    bool m_isIncremental;
    int m_count;
public:
    Encryptor() 
    {
        cout << "/t-----1------" << endl;
        m_isIncremental = 0;
        m_count = 1;
    }
    Encryptor(bool isInc, int count) 
    {
        cout << "-----2------" << endl;
        m_isIncremental = isInc;
        m_count = count;
    }
    std::string operator()(std::string data) 
    {
        cout << "-----3------" << endl;
        std::cout << data << std::endl;
        for (int i = 0; i < data.size(); i++)
            if ((data[i] >= 'a' && data[i] <= 'z')
                    || (data[i] >= 'A' && data[i] <= 'Z'))
                if (m_isIncremental)
                    data[i] += m_count;
                else
                    data[i] -= m_count;
        return data;
    }
 
};
 
std::string buildCompleteMessage(std::string rawData, Encryptor encyptorFuncObj) 
{
    // Add some header and footer to data to make it complete message
    rawData = "[HEADER]" + rawData + "[FooTER]";
 
    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encyptorFuncObj(rawData);
 
    return rawData;
}
 
int main() 
{
    std::string msgs = buildCompleteMessage("SampleString", Encryptor());
    std::cout << msgs << std::endl << std::endl;
    
    std::string msg = buildCompleteMessage("SampleString", Encryptor(true, 1));
    std::cout << msgs << std::endl << std::endl;
 
    msg = buildCompleteMessage("SampleString", Encryptor(true, 2));
    std::cout << msgs << std::endl << std::endl;
 
    msg = buildCompleteMessage("SampleString", Encryptor(false, 1));
    std::cout << msgs << std::endl << std::endl;
 
    return 0;
}












