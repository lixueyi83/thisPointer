/*************************************************************************
	> File Name: rvalue_referece.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Oct 2017 02:20:18 PM PDT
 ************************************************************************/
#include <iostream>
#include <vector>
using namespace std;


/* Every expression in C++ is either rvalue or lvalue. 
 *
 * What is lvaue?
 * lvalue is anything whose address is accessible. It means we can take 
 * address of lvaue using & operator.
 *
 * What is rvalue?
 * rvalue is anything that is not lvalue. It means we cannot take address
 * of rvalue and it also don't persist beyond the single expression. 
 *
 * is rvalue immutable in c++?
 * rvalue of builtin data type is immutable: (x+7) = 7 will result in compile error.
 * rvalue of user defined data type is not immutable: 
 */
 
class Person
{
	int m_age;
public:
	Person() 
	{
		m_age = 10;
	}
	int incr_age()
	{
		m_age = m_age + 1;
		return m_age;
	}
};

Person getPerson()
{
	return Person();
}

int main_1() 
{
    /*error: taking address of temporary [-fpermissive]*/
    //Person * personPtr = &getPerson(); 
	cout << getPerson().incr_age() << endl;
	return 0;
}

 /* what is rvalue reference in C++11? 
 * lvalue reference:
 * A reference variable is an alias that always points to an existing variable. 
 * In C++11 this reference is a lvalue reference and it can only refer to lvalues only. 
 *
 * rvalue reference:
 * introduced in C++11 and it can do what lvaue reference fails to do. 
 * int &&rvalueRef = (x+1); rvalueRef is rvalue reference which points to a rvalue (x+1)
 * Here is an example:
 *      int getData()
 *      {
 *          return 9;
 *      }
 *
 *      getData() is a rvalue, so only rvalue reference can refer to it. 
 *      int & lvalueRef = getData(); // Compile error - lvalueRef cannot point to rvalue 
 *      const int & lvalueRef = getData(); // Ok, but is const 
 *      int &&rvalueRef = getData();
 *
 * What is the need of rvalue reference?  
 *      http://thispointer.com/c11-move-contsructor-rvalue-references/
 * 
 * Solving Problem of Temporary Objects using rvalue references & Move Constructor.
 * Move constructor takes a rvalue reference as an argument and that makes it overloaded because 
 * Copy Constructor takes the const lvalue reference as an argument. In Move constructor we just 
 * move the member variables of passed object into the new object’s member variables, instead of 
 * allocating new memory for them.
 * 
 * In the move constructor, we just copied the pointer. Now member variable m_Data points to the 
 * same memory on heap. Then we set the m_Data of passed object to NULL. So, we didn’t allocated 
 * any memory on heap in move constructor, we just shifted the control of memory.
 * */

 
class Container 
{
	int * m_Data;
public:
	Container() 
	{
		/* Allocate an array of 20 int on heap */
		m_Data = new int[20];
		std::cout << "Constructor: Allocation 20 int" << std::endl;
	}
	
	~Container() 
	{
		if (m_Data) 
		{
			delete[] m_Data;
			m_Data = NULL;
		}
	}
	
	Container(const Container & obj) 
	{
		/* Allocate an array of 20 int on heap */
		m_Data = new int[20];
 
		/* Copy the data from passed object*/
		for (int i = 0; i < 20; i++)
			m_Data[i] = obj.m_Data[i];
 
		std::cout << "Copy Constructor: Allocation 20 int" << std::endl;
	}
 
	/* Move Constructor */
	Container(Container && obj)
	{
		/* Just copy the pointer */
		m_Data = obj.m_Data;
 
		/* Set the passed object's member to NULL */
		obj.m_Data = NULL;
 
		std::cout<<"Move Constructor"<<std::endl;
	}
 
	/* Move Assignment Operator */
	Container& operator=(Container && obj)
	{
		if(this != &obj)
		{
			/* Just copy the pointer */
			m_Data = obj.m_Data;
 
			/* Set the passed object's member to NULL */
			obj.m_Data = NULL;
			std::cout<<"Move Assignment Operator"<<std::endl;
		}
	}
	
	/* Assignment Operator */
	Container& operator=(const Container & obj) 
	{
		if(this != &obj)
		{
			/* Allocate an array of 20 int on heap */
			m_Data = new int[20];
 
			/* Copy the data from passed object */
			for (int i = 0; i < 20; i++)
				m_Data[i] = obj.m_Data[i];
 
			std::cout << "Assigment Operator: Allocation 20 int" << std::endl;
		}
	}
 
};
 
/* Create am object of Container and return */
Container getContainer()
{
	Container obj;
	return obj;
}

int main() 
{
	/* Create a vector of Container Type */
	std::vector<Container> vecOfContainers;
	
	cout << "----------------1----------------" << endl;
 
	/* Add object returned by function into the vector */
	vecOfContainers.push_back(getContainer());
	
	cout << "----------------2----------------" << endl;
 
	Container obj;
	obj = getContainer();
	
	cout << "----------------3----------------" << endl;
	
	Container obj1(obj);
	
	cout << "----------------4----------------" << endl;
 
	return 0;
}
  

















