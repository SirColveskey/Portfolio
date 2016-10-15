/*===================================================*/
/*       WELCOME TO THE LINKED LIST.hpp              */
/*             BY: Benjamin Cooper                   */
/*          CLASS: COP4350 - Data Structures         */
/*           DATE: 10/2/2015                         */
/*        UPDATED: 10/3/2015                         */
/*===================================================*/
 
// Purpose: This file is the .h file linked with
//	    stack.hpp. Implmentation and improvements
//	    can be found in that file.

#include <list>
#include <iostream>

namespace cop4530{

template<typename T>
class Stack
{
	public:
		Stack();								//zero-arg constructor
		~Stack();								//destructor
		Stack(const Stack<T>&);					//copy constructor
		Stack(Stack<T>&&);						//move constructor
		Stack<T>& operator=(const Stack<T>&);	//copy assignment op.
		Stack<T>& operator=(Stack<T>&&);		//move assignment op.
		bool empty() const;
		void clear();
		void push(const T& x);					//adds x to the Stack, copy
		void push(T&& x);						//adds x to the Stack, move
		void pop();								//removes and discards top
		T& top();								//mutator that returns a ref.
		const T& top() const;					//accessor that returns top.
		int size() const;
		void print(std::ostream& os, char ofc = ' ') const;	//prints bottom 1st
	
	private:
		std::list<T> Data;

};
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Stack<T>& a);
	template<typename T>
	bool operator==(const Stack<T>&, const Stack<T>&);
	template<typename T>
	bool operator<(const Stack<T>& a, const Stack<T>& b);

	#include "stack.hpp"
	
} //end namespace

