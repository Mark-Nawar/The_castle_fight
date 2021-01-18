#pragma once
#include "StackADT.h"

//Unless spesificed by the stack user, the default size is 100
template<typename T>
class stack : public StackADT<T>
{
private:
	T* items;		// Array of stack items
	int      top;                   // Index to top of stack
	const int STACK_SIZE =500;

public:

	stack()
	{
		//STACK_SIZE = 500;
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	//Function getCapacity() returns the stack max size
	//added for array implementaion only
	int getCapacity()
	{
		return STACK_SIZE;
	}

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek
	const T* Toarray(int& count)
	{
		count = top + 1;
		return items;
	}
	   //Destructor
	~stack()
	{
		delete[]items;
	}

	//Copy constructor
	stack(const stack<T>& S) :STACK_SIZE(S.STACK_SIZE)
	{
		items = new T[STACK_SIZE];
		for (int i = 0; i <= S.top; i++)
			items[i] = S.items[i];
		top = S.top;
	}

}; // end stack