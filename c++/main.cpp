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
using namespace std;

/*-------------------shared_ptr------------
 * 1. Each shared_ptr object internally points to two memory locations:
 *      1) pointer to the object
 *      2) pointer to control data that is used for reference counting 
 *
 * 2. Creating a shared_ptr object:
 *      1) std::shared_ptr<int> p1(new int()) allocates two memory on heap: 1)For int; 2) A 
 *      memory for reference counting that will be used to manage the count of shared_ptr 
 *      attached to this memory, initially this count will be 1. 
 *      2) Checking reference count of shared_ptr object: p1.use_count();
 *
 * 3. Best way to create a new shared_ptr object is using std::make_shared. 
 *      std::shared_ptr<int> p1 = std::make_shared<int>(42)
 *
 * 4. Detaching the associated Raw Pointer: call p1.reset() or p1 = nullptr;
 *      1) reset function without parameters: p1.reset() decreases its reference count by 1 
 *      and if reference count becomes 0 then it delete this pointer.
 *      2) reset() function with parameters: p1.reset(new int(32)), In this case, it will 
 *      point to new pointer internally, hence its Reference count will again become 1.
 *      3) reseting using nullptr: 
 * */

 
int shared_ptr_main()
{
	std::shared_ptr<int> p1 = std::make_shared<int>(42); //*p1 = 78;
	std::cout << "p1 = " << *p1 << std::endl;
	std::cout << "p1 Reference count = " << p1.use_count() << std::endl;
    cout << endl;
 
	// Second shared_ptr object will also point to same pointer internally
	// It will make the reference count to 2.
	std::shared_ptr<int> p2(p1);
    *p2 += 10; 
	std::cout << "p1 = " << *p1 << std::endl;
 
	// Shows the reference count
	std::cout << "p2 Reference count = " << p2.use_count() << std::endl;
	std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

    cout << endl;
 
	// Comparing smart pointers
	if (p1 == p2)
	{
		std::cout << "p1 and p2 are pointing to same pointer\n";
	}
 
    cout << endl;

	std::cout<<"Reset p1 "<<std::endl;
 
	p1.reset();
 
	// Reset the shared_ptr, in this case it will not point to any Pointer internally
	// hence its reference count will become 0.
 
	std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;
 
    cout << endl;

	// Reset the shared_ptr, in this case it will point to a new Pointer internally
	// hence its reference count will become 1.
 
	p1.reset(new int(11));
 
	std::cout << "p1 reference Count = " << p1.use_count() << std::endl;
 
	// Assigning nullptr will de-attach the associated pointer and make it to point null
	p1 = nullptr;
 
	std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;
 
	if (!p1)
	{
		std::cout << "p1 is NULL" << std::endl;
	}
	return 0;
}


/* shared_ptr deletor and custom deletor 
 * When a shared_ptr goes out of scope, its destructor is called. Inside its destructor
 * it decrements the reference count by 1 and if new value of reference count is 0 then 
 * it deletes the associated raw pointer. To delete the internal raw pointer in destructor,
 * by default shared_ptr calls the delete() function.
 *
 * But it is not always that we want to use delete function in destruction, there can be 
 * other requirements --> if shared_ptr object points to an array instead of a single pointer.
 *      std::shared_ptr<int> p(new int[12]);
 * In its destructor shared_ptr will try to delete the int array by calling delete function, 
 * whereas the correct way is using delete []. In this case, we add custom deleter. 
 *
* */
struct Sample
{
	Sample()
	{
		std::cout << "CONSTRUCTOR\n";
	}
	~Sample()
	{
		std::cout << "DESTRUCTOR\n";
	}
	
	void dummyFunction()
	{
		std::cout << "dummyFunction" << std::endl;
	}
};
 
// function that calls the delete [] on received pointer
void deleter(Sample * x)
{
	std::cout << "DELETER FUNCTION CALLED\n";
	delete[] x;
}
 
int main_custom_deleter()
{
	/* Creating a shared+ptr with custom deleter */
	std::shared_ptr<Sample> p3(new Sample[12], deleter);
	std::shared_ptr<Sample> p4(new Sample[12], [](Sample *ptr)
	    {
	        std::cout << "DELETER LAMBDA CALLED." << endl;
	        delete []ptr;
	    });
	return 0;
}


/*
 * shared_ptr vs raw pointer
 * In comparision to a raw pointer, shared_ptr provides only these operators
 *      1) ->, *
 *      2) comparision operators
 * But shared_ptr does not provide,
 *      1) pointer arithmetic like +, -, ++, --
 *      2) operator []
 *
 * Do not create shared_ptr with raw pointers, use make_shared.
 *
 * NULL check:
 *      1) if(!ptr)
 *      2) if(ptr == NULL)
 *      3) if(ptr == nullptr)
* */

 
int main_use_make_shared()
{
 
	std::shared_ptr<Sample> ptr = std::make_shared<Sample>();
 
	(*ptr).dummyFunction(); /* Will Work */
 
	ptr->dummyFunction(); /* Will Work */
 
	// ptr[0]->dummyFunction(); // This line will not compile.
	// ptr++;  // This line will not compile.
	//ptr--;  // This line will not compile.
 
	std::shared_ptr<Sample> ptr2(ptr);
 
	if (ptr == ptr2) // Will work
		std::cout << "ptr and ptr2 are equal" << std::endl;
 
	return 0;
}


/*
 * unique_ptr 
 * 1. unique_ptr provides memory leak;
 * 2. wraps around a raw pointer and it is responsible for its lifetime.
 * 3. when object is destructed, its associated raw pointer is deleted.
 * 4. has -> and *, so it can be used as normal pointers 
 * 5. ownership: is always the unique owner of associated raw pointer, we cannot copy, only move.
 * 6. checking empty: if(!ptr); if(ptr == nullptr)
* */

struct Task
{
	int mId;
	Task(int id ) :mId(id)
	{
		std::cout<<"Task::Constructor"<<std::endl;
	}
	~Task()
	{
		std::cout<<"Task::Destructor"<<std::endl;
	}
};
 
int main()
{
	// Empty unique_ptr object
	std::unique_ptr<int> ptr1;
 
	// Check if unique pointer object is empty
	if(!ptr1)
		std::cout<<"ptr1 is empty"<<std::endl;
 
	// Check if unique pointer object is empty
	if(ptr1 == nullptr)
		std::cout<<"ptr1 is empty"<<std::endl;
 
	// can not create unique_ptr object by initializing through assignment
	// std::unique_ptr<Task> taskPtr2 = new Task(); // Compile Error
 
	// Create a unique_ptr object through raw pointer
	std::unique_ptr<Task> taskPtr(new Task(23));
 
	// Check if taskPtr is empty or it has an associated raw pointer
	if(taskPtr != nullptr)
		std::cout<<"taskPtr is  not empty"<<std::endl;
 
	//Access the element through unique_ptr
	std::cout<<taskPtr->mId<<std::endl;
 
	std::cout<<"Reset the taskPtr"<<std::endl;
	// Reseting the unique_ptr will delete the associated
	// raw pointer and make unique_ptr object empty
	taskPtr.reset();
 
	// Check if taskPtr is empty or it has an associated raw pointer
	if(taskPtr == nullptr)
		std::cout<<"taskPtr is  empty"<<std::endl;
 
 
	// Create a unique_ptr object through raw pointer
	std::unique_ptr<Task> taskPtr2(new Task(55));
 
	if(taskPtr2 != nullptr)
		std::cout<<"taskPtr2 is  not empty"<<std::endl;
 
	// unique_ptr object is Not copyable
	//taskPtr = taskPtr2; //compile error
 
	// unique_ptr object is Not copyable
	//std::unique_ptr<Task> taskPtr3 = taskPtr2;
 
	{
		// Transfer the ownership
 
		std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
 
 
		if(taskPtr2 == nullptr)
			std::cout<<"taskPtr2 is  empty"<<std::endl;
 
		// ownership of taskPtr2 is transfered to taskPtr4
		if(taskPtr4 != nullptr)
			std::cout<<"taskPtr4 is not empty"<<std::endl;
 
		std::cout<<taskPtr4->mId<<std::endl;
 
		//taskPtr4 goes out of scope and deletes the assocaited raw pointer
	}
 
	// Create a unique_ptr object through raw pointer
	std::unique_ptr<Task> taskPtr5(new Task(55));
 
	if(taskPtr5 != nullptr)
		std::cout<<"taskPtr5 is not empty"<<std::endl;
 
	// Release the ownership of object from raw pointer
	Task * ptr = taskPtr5.release();
 
	if(taskPtr5 == nullptr)
		std::cout<<"taskPtr5 is empty"<<std::endl;
 
	std::cout<<ptr->mId<<std::endl;
 
	delete ptr;
 
	return 0;
}


